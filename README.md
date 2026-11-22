# Peripheral Wireless Battery

A clean, native Windows 11 taskbar battery monitor and widget for wireless and wired gaming peripherals, featuring custom positioning, fine-grained pixel nudge offsets, and dedicated support for the **Leobog Hi75C Pro** keyboard and **Vortex Series Oni R1** mouse.

[![Support me on Sociabuzz](https://img.shields.io/badge/Sociabuzz-Buy%20me%20a%20coffee-orange?logo=coffeescript&logoColor=white)](https://sociabuzz.com/itsmickeymontana/tribe)
[![GitHub release](https://img.shields.io/github/v/release/ddolls/Peripheral-Wireless-Battery?color=blue)](https://github.com/ddolls/Peripheral-Wireless-Battery/releases)
[![Platform](https://img.shields.io/badge/Platform-Windows%2011%20%7C%2010-0078D6?logo=windows)](https://github.com/ddolls/Peripheral-Wireless-Battery)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)

---

## Highlights

- **Native Windows 11 Taskbar Integration:** Sits directly on your taskbar as a seamless Fluent widget.
- **Customizable Taskbar Placements:**
  - *Far Right Edge*
  - *Left of System Tray*
  - *Next to Clock*
  - *Center Taskbar*
  - *Next to Running App Icons*
  - *Far Left Edge*
- **Flexible Text Layout & Styling:**
  - **Text Placement:** Position percentage text to the *Right of icon (Default)*, *Left of icon*, or *Below icon (Vertical stack)*.
  - **Custom Font Size:** Pick from presets (10px, 11px, 13px, 15px, 17px, 20px) or set custom font pixel sizes.
  - **Per-Device Custom Colors:** Tint any connected peripheral icon with quick presets or the native Windows Color Picker (clean, glow-free tinting).
- **Precision Nudge & Custom Offset:** Fine-tune widget placement with $\pm 1\text{px}$, $\pm 5\text{px}$, $\pm 20\text{px}$ shortcuts or define custom X / Y coordinates.
- **Dedicated Device Support:**
  - **Leobog Hi75C Pro:** 2.4 GHz wireless receiver & USB-C wired charging mode.
  - **Vortex Series Oni R1:** 2.4 GHz wireless receiver & USB-C wired cable mode (`1D57:FA60` / `1D57:FA61`).
  - Broad support for Logitech, Razer, SteelSeries, Corsair, HyperX, and other major gaming peripherals.
- **Crisp Visuals & Dark/Light Themes:**
  - Pure white lightning bolt indicator (`⚡`) matching Windows dark theme.
  - Non-dimmed status when plugged into USB cable.
  - Fully supports dynamic Windows Light and Dark mode switching.
- **Battery History & Insights:**
  - Built-in local graphing viewer to track battery percentage trends over 24 hours, 7 days, or 30 days.
- **Ultra Lightweight:**
  - Standalone single native binary (~1.6 MB).
  - No Electron, no background services, no heavy manufacturer bloatware required.

---

## Getting Started

1. Download the latest **[Peripheral-Wireless-Battery.exe](https://github.com/ddolls/Peripheral-Wireless-Battery/releases/latest)** from GitHub Releases.
2. Place it in any directory of your choice and run it.
3. Your connected devices will automatically be detected and appear on the taskbar.
4. Right-click the widget or its tray icon to adjust position, nudge offsets, view version changelogs, or open battery history.

---

## Changelog

### v1.1.0
- **Percentage Text Placement:** Added options to place percentage text to the *Right of icon (Default)*, *Left of icon*, or *Below icon (Vertical stack)*.
- **Custom Percentage Font Size:** Preset sizes (10px, 11px, 13px, 15px, 17px, 20px) and custom pixel input dialog.
- **Per-Device Custom Colors:** Added per-peripheral custom color presets and full Windows Color Picker support (clean icon tinting without glow or thin level bars).
- **Startup Reliability:** Fixed context menu auto-appearing on Windows boot / login.
- **Dedicated Hardware Support:** Support for **Leobog Hi75C Pro** and **Vortex Series Oni R1** in both 2.4 GHz wireless and USB-C wired charging modes.
- **Taskbar Positioning & Nudge:** 6 preset taskbar positions and precision nudge offsets ($\pm 1\text{px}$, $\pm 5\text{px}$, $\pm 20\text{px}$) + custom offset dialog.

---

## Build from Source

### Prerequisites
- Windows 10 / 11 (64-bit)
- Visual Studio 2022 (with "Desktop development with C++" workload installed)

### Compilation
Run the provided build script from a developer command prompt:
```cmd
build-msvc.bat
```
The compiled binary `Peripheral-Wireless-Battery.exe` will be generated in the root folder.

---

## Credits & Acknowledgments

This project is built upon the foundation of [Wireless-Device-Battery-Monitor](https://github.com/krisgfx9/Wireless-Device-Battery-Monitor) by [krisgfx9](https://github.com/krisgfx9), licensed under GPL-3.0.

Customized, maintained, and extended by **[ddolls](https://github.com/ddolls)** with:
- Windows 11 Taskbar placement modes (*Far Right Edge, Left of Tray, Next to Clock, Center, Next to Running Apps, Far Left Edge*)
- Pixel nudge shortcuts and custom X/Y positioning dialog
- Dedicated hardware driver & battery decoding for **Leobog Hi75C Pro** (2.4 GHz & wired USB-C)
- Dedicated hardware driver & battery decoding for **Vortex Series Oni R1** (2.4 GHz & wired USB-C)
- Visual styling enhancements (pure white charging bolt, non-dimmed charging indicators, clean history viewer)

---

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).
Special thanks to the open-source community for protocol research and hardware telemetry documentation.
