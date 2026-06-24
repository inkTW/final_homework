## 1. 終端機編碼修正實作

- [x] 1.1 在 `src/main.cpp` 引入 Windows 平台專用的 `<Windows.h>` 標頭檔，並以 `#ifdef _WIN32` 包裹
- [x] 1.2 在 `src/main.cpp` 的 `main()` 進入點開頭呼叫 `SetConsoleOutputCP(CP_UTF8)` 與 `SetConsoleCP(CP_UTF8)` 設定 UTF-8 編碼，並以 `#ifdef _WIN32` 包裹
- [x] 1.3 重新編譯專案並進行終端機編碼輸出測試，驗證中文是否能正常顯示不出現亂碼
