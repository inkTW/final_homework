## Context

本專案旨在以 C++ 標準庫（STL）與物件導向程式設計（OOP）建立一個「智慧家居設備模擬與自動化系統」的單機模擬器。我們需要為此模擬器設計可擴充的設備樹與自動化規則樹，並利用檔案系統進行狀態保存與日誌導出，同時確保在終端機介面中提供防呆的互動體驗。

## Goals / Non-Goals

**Goals:**
- **物件導向設計**：設計 `SmartDevice` 與 `AutomationRule` 兩個獨立的繼承體系，利用純虛擬函數與多型（Polymorphism）實現程式的擴充性。
- **記憶體安全性**：使用智慧指標（如 `std::unique_ptr`）管理動態配置的物件，防止記憶體洩漏並落實 RAII 原則。
- **資料持久化**：實作簡單文字格式的讀檔/寫檔，不依賴外部資料庫。
- **互動防呆**：在終端機 UI 實作輸入驗證，防止非預期輸入（如字串輸入至數字欄位）造成無窮迴圈或當機。

**Non-Goals:**
- **網路通信與真實 IoT 整合**：不使用套接字（Sockets）、MQTT 或 HTTP API 與真實物聯網設備通訊，純屬單機記憶體狀態模擬。
- **圖形化使用者介面 (GUI)**：不使用 Qt、wxWidgets 或 ImGui 等 GUI 框架，專注於完成「終端機文字模擬 UI」。
- **高階資料庫**：不使用 SQLite、MySQL 等外部資料庫，以純文字/CSV 檔案進行存檔。

## Decisions

### 決定一：使用智慧指標 `std::unique_ptr` 進行多型物件生命週期管理
- **選擇方案**：`std::vector<std::unique_ptr<SmartDevice>>`
- **考慮過的替代方案**：使用原始指標 `std::vector<SmartDevice*>` 或共用智慧指標 `std::vector<std::shared_ptr<SmartDevice>>`。
- **決策理由**：
  - 原始指標需要手動 `delete`，容易忘記釋放導致記憶體洩漏（尤其在拋出異常時）。
  - `shared_ptr` 會有額外的引用計數（Reference Count）開銷。由於本專案中設備的擁有權僅屬於 `SmartHome` 控制中心，不需要多個地方共享擁有權，因此選擇獨佔式的 `std::unique_ptr` 最符合語意且效能最優。

### 決定二：將「設備」與「自動化規則」解耦為兩個獨立的繼承體系
- **選擇方案**：設備類別繼承自 `SmartDevice`；自動化規則繼承自 `AutomationRule`。
- **決策理由**：
  - 這遵循了單一職責原則（Single Responsibility Principle）。設備專注於維護自己的運作狀態（如亮度、開關），而規則專注於判斷觸發條件並執行行為。
  - 當未來需要增加新的設備（如智能插座）或新的觸發邏輯（如定時重複規則）時，可以獨立擴充，互不干擾。

### 決定三：使用 `std::stringstream` 進行自訂純文字檔案解析
- **選擇方案**：設計自訂語法並以 `<sstream>` 解析設定檔。
- **考慮過的替代方案**：使用外部 JSON/XML 函式庫（如 `nlohmann/json`）。
- **決策理由**：
  - 為了保持期末專題的獨立性與編譯便利度，避免因安裝第三方庫導致評分老師編譯失敗。
  - 使用自訂格式（例如以空格分隔的行），利用 C++ 標準庫的 `getline` 和 `stringstream` 即可進行安全、高效的解析，並能在此過程中充分展現對 C++ 串流控制的掌握。

## Risks / Trade-offs

- **[Risk] 多型解構不完全造成的記憶體洩漏**
  - **Mitigation**：基底類別 `SmartDevice` 與 `AutomationRule` 必須宣告 `virtual ~Base() = default;`。若忘記宣告虛擬解構子，在釋放 `unique_ptr` 時將無法正確呼叫衍生類別的解構子，導致額外成員變數未被正確回收。
- **[Risk] 終端機 UI 的輸入溢位或崩潰**
  - **Mitigation**：每次使用 `std::cin >> choice` 之後，若偵測到 `std::cin.fail()`，立即進行 `std::cin.clear()` 及 `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')` 重設串流，並顯示友善錯誤提示，確保程式不會死結。
