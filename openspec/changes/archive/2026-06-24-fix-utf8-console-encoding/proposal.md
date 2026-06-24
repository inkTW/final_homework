## Why

在 Windows 作業系統的終端機環境中（例如 PowerShell 與 CMD），預設採用區域性的 OEM 編碼（如繁體中文系統預設為 CP950/Big5）。當我們的 C++ 應用程式輸出 UTF-8 編碼的中文文字時，會導致終端機解碼錯誤，進而產生中文亂碼（Garbage Characters）。此變更旨在解決終端機編碼衝突，確保中文介面能正確顯示。

## What Changes

- **設定控制台編碼**：在 `src/main.cpp` 的 `main()` 進入點，使用條件編譯（`#ifdef _WIN32`）針對 Windows 平台呼叫系統 API `SetConsoleOutputCP(CP_UTF8)` 與 `SetConsoleCP(CP_UTF8)`，將控制台的主動代碼頁切換至 UTF-8。
- **跨平台支援**：確保上述 Windows API 僅在 `_WIN32` 平台上編譯，以維持程式碼在 Linux 或 macOS 平台上的編譯相容性。

## Capabilities

### New Capabilities
*(無)*

### Modified Capabilities
- `terminal-ui`: 修改終端機輸出要求，確保在 Windows 控制台環境下，中文輸出能正確解碼，不出現亂碼。

## Impact

- 影響檔案：`src/main.cpp`
- 無新增外部庫或依賴，使用 Windows 內建之系統標頭檔 `<Windows.h>`。
