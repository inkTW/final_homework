## Why

本專案旨在為 C++ 期末專題設計並開發一個「智慧家居設備模擬與自動化系統」。透過模擬真實智慧家居的設備控制與自動觸發規則，展示物件導向設計中的類別繼承與多型概念、標準樣版函式庫 (STL) 的活用、檔案輸入輸出 (File I/O) 的持久化儲存，以及終端機互動式介面的防呆設計。

## What Changes

- **建立智慧設備抽象體系**：設計 `SmartDevice` 基底類別，衍生出 `SmartLight`、`SmartThermostat` 與 `SmartCamera` 類別，透過虛擬解構子與純虛擬函數實作多型。
- **建立自動化規則抽象體系**：設計 `AutomationRule` 基底類別，衍生出 `TemperatureRule` 與 `TimeRule`，自動根據環境變化觸發對應設備。
- **實作 STL 多型容器管理**：使用 `std::vector<std::unique_ptr<SmartDevice>>` 與 `std::vector<std::unique_ptr<AutomationRule>>` 進行生命週期管理與多型呼叫。
- **持久化與日誌功能**：實作讀取 `config.txt` 載入家居配置，並提供儲存目前狀態與導出系統事件日誌至外部 CSV 檔案之功能。
- **終端機模擬互動 UI**：建置全中文化的終端機 UI，提供即時狀態儀表板、手動控制、環境模擬（調整時間/溫度）與防呆輸入驗證。

## Capabilities

### New Capabilities
- `device-management`: 處理智慧設備的基底定義、衍生屬性（亮度、設定溫度、錄影狀態）與多型狀態回報。
- `automation-rules`: 處理自動化觸發邏輯，能定時或根據室溫/動態感測狀態觸發對應設備之開關。
- `file-storage`: 處理載入/儲存家居設備與規則設定檔，以及寫出事件日誌檔案。
- `terminal-ui`: 提供豐富的終端機互動選單、即時狀態顯示與環境參數模擬（溫度、時間）。

### Modified Capabilities
*(無)*

## Impact

- 本專案為全新開發之 C++ 專案，無舊有程式碼或現存依賴庫之影響。將建立全新的類別架構與編譯配置。
