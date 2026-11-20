#include "offset_dialog.h"
#include <string>

namespace offset_dialog {

namespace {
constexpr wchar_t kDialogClass[] = L"PeripheralBatteryOffsetDialog";

struct DialogState {
    int x;
    int y;
    bool accepted;
    HWND editX;
    HWND editY;
};

void SetControlFont(HWND control) {
    if (control) SendMessageW(control, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
}

LRESULT CALLBACK DialogProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_NCCREATE) {
        auto* cs = reinterpret_cast<CREATESTRUCTW*>(lp);
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);
        return TRUE;
    }
    auto* state = reinterpret_cast<DialogState*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    if (!state) return DefWindowProcW(hwnd, msg, wp, lp);

    switch (msg) {
        case WM_CREATE: {
            HINSTANCE inst = GetModuleHandleW(nullptr);
            const int dpi = GetDpiForWindow(hwnd);
            auto scale = [dpi](int v) { return MulDiv(v, dpi ? dpi : 96, 96); };

            HWND lblX = CreateWindowExW(0, L"STATIC", L"Horizontal Offset X (px, - Left / + Right):",
                                        WS_CHILD | WS_VISIBLE, scale(20), scale(15), scale(280), scale(20),
                                        hwnd, nullptr, inst, nullptr);
            state->editX = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", std::to_wstring(state->x).c_str(),
                                          WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL,
                                          scale(20), scale(38), scale(280), scale(24),
                                          hwnd, (HMENU)101, inst, nullptr);

            HWND lblY = CreateWindowExW(0, L"STATIC", L"Vertical Offset Y (px, - Up / + Down):",
                                        WS_CHILD | WS_VISIBLE, scale(20), scale(72), scale(280), scale(20),
                                        hwnd, nullptr, inst, nullptr);
            state->editY = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", std::to_wstring(state->y).c_str(),
                                          WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_AUTOHSCROLL,
                                          scale(20), scale(95), scale(280), scale(24),
                                          hwnd, (HMENU)102, inst, nullptr);

            HWND btnOk = CreateWindowExW(0, L"BUTTON", L"OK",
                                         WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
                                         scale(110), scale(135), scale(90), scale(28),
                                         hwnd, (HMENU)IDOK, inst, nullptr);
            HWND btnCancel = CreateWindowExW(0, L"BUTTON", L"Cancel",
                                             WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                             scale(210), scale(135), scale(90), scale(28),
                                             hwnd, (HMENU)IDCANCEL, inst, nullptr);

            SetControlFont(lblX);
            SetControlFont(state->editX);
            SetControlFont(lblY);
            SetControlFont(state->editY);
            SetControlFont(btnOk);
            SetControlFont(btnCancel);
            SetFocus(state->editX);
            SendMessageW(state->editX, EM_SETSEL, 0, -1);
            return 0;
        }
        case WM_COMMAND: {
            WORD cmd = LOWORD(wp);
            if (cmd == IDOK) {
                wchar_t bufX[64] = {}, bufY[64] = {};
                GetWindowTextW(state->editX, bufX, 63);
                GetWindowTextW(state->editY, bufY, 63);
                state->x = _wtoi(bufX);
                state->y = _wtoi(bufY);
                state->accepted = true;
                DestroyWindow(hwnd);
                return 0;
            } else if (cmd == IDCANCEL) {
                state->accepted = false;
                DestroyWindow(hwnd);
                return 0;
            }
            break;
        }
        case WM_CLOSE:
            state->accepted = false;
            DestroyWindow(hwnd);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

}  // namespace

bool Show(HWND parent, int curX, int curY, int& outX, int& outY) {
    HINSTANCE inst = GetModuleHandleW(nullptr);
    static bool registered = false;
    if (!registered) {
        WNDCLASSEXW wc{ sizeof(wc) };
        wc.lpfnWndProc = DialogProc;
        wc.hInstance = inst;
        wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
        wc.lpszClassName = kDialogClass;
        RegisterClassExW(&wc);
        registered = true;
    }

    DialogState state{ curX, curY, false, nullptr, nullptr };

    int scrW = GetSystemMetrics(SM_CXSCREEN);
    int scrH = GetSystemMetrics(SM_CYSCREEN);
    int dlgW = 340;
    int dlgH = 220;
    int x = (scrW - dlgW) / 2;
    int y = (scrH - dlgH) / 2;

    HWND hwnd = CreateWindowExW(
        WS_EX_DLGMODALFRAME | WS_EX_TOPMOST,
        kDialogClass,
        L"Peripheral Wireless Battery - Custom Offset",
        WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
        x, y, dlgW, dlgH,
        parent, nullptr, inst, &state
    );

    if (!hwnd) return false;

    if (parent) EnableWindow(parent, FALSE);

    MSG msg;
    while (IsWindow(hwnd) && GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (!IsDialogMessageW(hwnd, &msg)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    if (parent) {
        EnableWindow(parent, TRUE);
        SetForegroundWindow(parent);
    }

    if (state.accepted) {
        outX = state.x;
        outY = state.y;
        return true;
    }
    return false;
}

}  // namespace offset_dialog
