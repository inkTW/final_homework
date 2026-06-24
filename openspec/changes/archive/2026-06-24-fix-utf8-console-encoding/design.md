## Context

Windows 作業系統內建的主控台（CMD / PowerShell）歷史上預設使用特定的 OEM 字碼頁（例如繁體中文 Windows 預設是 CP950，簡體中文預設是 CP936，英文預設是 CP437）。當 C++ 專案程式碼直接輸出以 UTF-8 編碼儲存的中文中文字串時，會被主控台以預設的 CP950 進行解碼，進而出現大面積的中文字亂碼。

## Goals / Non-Goals

**Goals:**
- **執行期動態修正字碼頁**：在程式進入 `main()` 時，自動將 Windows 控制台的輸入與輸出字碼頁切換至 UTF-8（代碼 65001）。
- **跨平台安全性**：所有平台相關 API 調用必須以 `#ifdef _WIN32` 進行條件編譯防護，以防止在 Linux 或 macOS 環境下發生編譯錯誤。

**Non-Goals:**
- **強制更改終端機字型**：如果使用者目前的終端機使用不支援中文的點陣字型，我們無法單靠程式碼本身強行安裝新字型，僅能提示其切換至支援中文的字型（如細明體、微軟正黑體、Cascadia Code、Consolas 等）。

## Decisions

### 決定一：使用 Windows API `SetConsoleOutputCP(CP_UTF8)` 及 `SetConsoleCP(CP_UTF8)`
- **選擇方案**：
  ```cpp
  #ifdef _WIN32
  #include <Windows.h>
  #endif
  ```
  並在 `main` 頂端執行：
  ```cpp
  #ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  #endif
  ```
- **考慮過的替代方案**：呼叫 `system("chcp 65001 > NUL")`。
- **決策理由**：
  - `system()` 會生成一個額外的 cmd shell 子程序去執行指令，效率較低，且會受到系統權限與防毒軟體的額外審查。
  - 直接調用 `SetConsoleOutputCP(CP_UTF8)` 是更原生的 Windows API，速度快且不會跳出子視窗。

## Risks / Trade-offs

- **[Risk] 非 Windows 平台編譯失敗**
  - **Mitigation**：務必在引入標頭檔與呼叫 API 時都用 `#ifdef _WIN32` 進行完全包裝，使 Linux/macOS 編譯器能直接無視該段程式碼。
