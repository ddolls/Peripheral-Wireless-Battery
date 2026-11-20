# Generate version.h and languages.txt
$ErrorActionPreference = "Stop"
$root = $PSScriptRoot | Split-Path -Parent
$buildDir = Join-Path $root "build"
if (-not (Test-Path $buildDir)) {
    New-Item -ItemType Directory -Force -Path $buildDir | Out-Null
}

& (Join-Path $root "scripts\generate-version.ps1") -Version "1.0.0" -Channel "dev"

$langFiles = Get-ChildItem -Path (Join-Path $root "lang\*.txt")
$outLines = [System.Collections.Generic.List[string]]::new()
foreach ($f in $langFiles) {
    $outLines.Add("@file " + $f.BaseName)
    $lines = [System.IO.File]::ReadAllLines($f.FullName, [System.Text.Encoding]::UTF8)
    foreach ($line in $lines) {
        $outLines.Add($line)
    }
    $outLines.Add("")
}

$destLang = Join-Path $buildDir "languages.txt"
[System.IO.File]::WriteAllLines($destLang, $outLines, [System.Text.Encoding]::UTF8)
Write-Host "Generated build/version.h and build/languages.txt" -ForegroundColor Green
