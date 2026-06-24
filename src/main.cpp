#include <iostream>
#include <limits>
#include <string>
#include <memory>
#include "SmartHome.h"
#include "SmartLight.h"
#include "SmartThermostat.h"
#include "SmartCamera.h"
#include "TemperatureRule.h"
#include "TimeRule.h"

// ==========================================
// 輸入驗證防呆輔助函式
// ==========================================

int getIntegerInput(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            return val;
        } else {
            std::cout << "⚠️ 無效輸入，請重新輸入一個整數數字！\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

double getDoubleInput(const std::string& prompt) {
    double val;
    while (true) {
        std::cout << prompt;
        if (std::cin >> val) {
            return val;
        } else {
            std::cout << "⚠️ 無效輸入，請重新輸入一個浮點數數字！\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string val;
    std::cout << prompt;
    std::cin >> val;
    return val;
}

// ==========================================
// 選單處理與顯示
// ==========================================

void printDashboard(const SmartHome& home) {
    std::cout << "\n============================================================\n";
    std::cout << "🏠 智慧家居自動化系統中控面板 (Smart Home Panel)\n";
    std::cout << "============================================================\n";
    std::cout << "🕒 [模擬時間] " << (home.getCurrentHour() < 10 ? "0" : "") << home.getCurrentHour() << ":00  | "
              << "🌡️ [環境溫度] " << home.getAmbientTemperature() << " °C  | "
              << "🚨 [動態偵測] " << (home.getMotionDetected() ? "🔥 偵測到動態！" : "無") << "\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "【 智慧設備狀態列表 】\n";
    
    const auto& devices = home.getDevices();
    if (devices.empty()) {
        std::cout << "  (目前無任何智慧設備)\n";
    } else {
        for (const auto& dev : devices) {
            std::cout << "  [ID: " << dev->getId() << "] " << dev->getName() 
                      << " -> " << dev->getStatusReport() << "\n";
        }
    }

    std::cout << "------------------------------------------------------------\n";
    std::cout << "【 自動化規則列表 】\n";
    const auto& rules = home.getRules();
    if (rules.empty()) {
        std::cout << "  (目前無任何自動化規則)\n";
    } else {
        for (const auto& rule : rules) {
            std::cout << "  [ID: " << rule->getId() << "] " << rule->getName() 
                      << " -> " << rule->getRuleDescription() << "\n";
        }
    }
    std::cout << "============================================================\n";
}

void handleControlDevice(SmartHome& home) {
    int id = getIntegerInput("請輸入要控制的設備 ID: ");
    SmartDevice* dev = home.getDeviceById(id);
    if (!dev) {
        std::cout << "❌ 找不到 ID 為 " << id << " 的設備！\n";
        return;
    }

    std::cout << "\n正在控制: " << dev->getName() << " (" << dev->getType() << ")\n";
    if (dev->getType() == "Light") {
        std::cout << "1. 開啟/關閉\n2. 調整亮度\n3. 更改燈色\n";
        int choice = getIntegerInput("請選擇操作選項 (1-3): ");
        if (choice == 1) {
            if (dev->getIsOn()) {
                dev->turnOff();
                std::cout << "已關閉燈光。\n";
                home.logEvent("手動操作: 關閉「" + dev->getName() + "」");
            } else {
                dev->turnOn();
                std::cout << "已開啟燈光。\n";
                home.logEvent("手動操作: 開啟「" + dev->getName() + "」");
            }
        } else if (choice == 2) {
            int bright = getIntegerInput("請輸入亮度 (0-100): ");
            dev->updateSetting("brightness", bright);
            std::cout << "亮度已設定為 " << bright << "%。\n";
            home.logEvent("手動操作: 將「" + dev->getName() + "」亮度調整為 " + std::to_string(bright) + "%");
        } else if (choice == 3) {
            std::string color = getStringInput("請輸入顏色名稱: ");
            dev->updateSetting("color", color);
            std::cout << "燈光顏色已變更為 " << color << "。\n";
            home.logEvent("手動操作: 將「" + dev->getName() + "」顏色變更為 " + color);
        }
    } else if (dev->getType() == "Thermostat") {
        std::cout << "1. 開啟/關閉\n2. 設定溫度\n3. 更改運作模式\n";
        int choice = getIntegerInput("請選擇操作選項 (1-3): ");
        if (choice == 1) {
            if (dev->getIsOn()) {
                dev->turnOff();
                std::cout << "已關閉溫控器。\n";
                home.logEvent("手動操作: 關閉「" + dev->getName() + "」");
            } else {
                dev->turnOn();
                std::cout << "已開啟溫控器。\n";
                home.logEvent("手動操作: 開啟「" + dev->getName() + "」");
            }
        } else if (choice == 2) {
            double temp = getDoubleInput("請輸入目標溫度 (16.0 - 30.0): ");
            dev->updateSetting("temperature", temp);
            std::cout << "設定溫度已變更為 " << temp << " °C。\n";
            home.logEvent("手動操作: 將「" + dev->getName() + "」目標溫度調整為 " + std::to_string(temp).substr(0, 4) + "°C");
        } else if (choice == 3) {
            std::cout << "模式選項: 制冷, 制熱, 送風, 節能\n";
            std::string mode = getStringInput("請輸入新模式: ");
            dev->updateSetting("mode", mode);
            std::cout << "運作模式已變更為 " << mode << "。\n";
            home.logEvent("手動操作: 將「" + dev->getName() + "」運作模式變更為 " + mode);
        }
    } else if (dev->getType() == "Camera") {
        std::cout << "1. 開啟/關閉監視器\n2. 開始/停止錄影\n3. 啟用/停用動態監測\n";
        int choice = getIntegerInput("請選擇操作選項 (1-3): ");
        if (choice == 1) {
            if (dev->getIsOn()) {
                dev->turnOff();
                std::cout << "已關閉監視器與錄影。\n";
                home.logEvent("手動操作: 關閉「" + dev->getName() + "」");
            } else {
                dev->turnOn();
                std::cout << "已開啟監視器。\n";
                home.logEvent("手動操作: 開啟「" + dev->getName() + "」");
            }
        } else if (choice == 2) {
            if (!dev->getIsOn()) {
                std::cout << "⚠️ 請先開啟監視器設備電源！\n";
                return;
            }
            auto cam = static_cast<SmartCamera*>(dev);
            if (cam->getIsRecording()) {
                cam->setRecording(false);
                std::cout << "已停止錄影。\n";
                home.logEvent("手動操作: 停止「" + dev->getName() + "」錄影");
            } else {
                cam->setRecording(true);
                std::cout << "已開始錄影。\n";
                home.logEvent("手動操作: 開始「" + dev->getName() + "」錄影");
            }
        } else if (choice == 3) {
            auto cam = static_cast<SmartCamera*>(dev);
            bool alert = cam->getMotionDetectionEnabled();
            cam->setMotionDetectionEnabled(!alert);
            std::cout << "動態監測已" << (!alert ? "啟用" : "停用") << "。\n";
            home.logEvent("手動操作: 將「" + dev->getName() + "」動態監測設為 " + (!alert ? "啟用" : "停用"));
        }
    }
    
    // 操作完後執行一次自動化規則輪詢，確認是否有關聯觸發
    home.runAutomation();
}

void handleSimulateEnvironment(SmartHome& home) {
    std::cout << "\n------------------------------------------------------------\n";
    std::cout << "🌍 環境參數模擬選單\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "1. 模擬調整溫度\n2. 模擬調整系統時間 (0-23)\n3. 觸發動態感應狀況\n4. 返回主選單\n";
    int choice = getIntegerInput("請輸入選項 (1-4): ");

    if (choice == 1) {
        double temp = getDoubleInput("請輸入新的模擬室溫 (°C): ");
        home.setAmbientTemperature(temp);
        home.logEvent("環境模擬: 室溫調整為 " + std::to_string(temp).substr(0, 4) + "°C");
        std::cout << "室溫已調整。正在評估自動化規則...\n";
        home.runAutomation();
    } else if (choice == 2) {
        int hour = getIntegerInput("請輸入新的模擬時間 (0-23): ");
        if (hour < 0 || hour > 23) {
            std::cout << "⚠️ 時間必須在 0 到 23 之間！\n";
            return;
        }
        home.setCurrentHour(hour);
        home.logEvent("環境模擬: 時間調整為 " + std::to_string(hour) + ":00");
        std::cout << "系統時間已調整。正在評估自動化規則...\n";
        home.runAutomation();
    } else if (choice == 3) {
        std::cout << "1. 觸發有人經過 (動態偵測發送)\n2. 清除動態狀態\n";
        int sub = getIntegerInput("請輸入子選項: ");
        if (sub == 1) {
            home.setMotionDetected(true);
            home.logEvent("環境模擬: 感應器偵測到門口動態");
            std::cout << "動態警報已觸發！\n";
            
            // 特殊邏輯：如果有開啟動態偵測的攝影機，觸發自動錄影
            for (const auto& dev : home.getDevices()) {
                if (dev->getType() == "Camera" && dev->getIsOn()) {
                    auto cam = static_cast<SmartCamera*>(dev.get());
                    if (cam->getMotionDetectionEnabled() && !cam->getIsRecording()) {
                        cam->setRecording(true);
                        home.logEvent("安全連動: 監視器「" + cam->getName() + "」偵測到動態，啟動錄影");
                    }
                }
            }
        } else {
            home.setMotionDetected(false);
            home.logEvent("環境模擬: 門口動態回復正常");
            std::cout << "動態警報已清除。\n";
        }
        home.runAutomation();
    }
}

void handleRuleManagement(SmartHome& home) {
    std::cout << "\n------------------------------------------------------------\n";
    std::cout << "⚙️ 自動化規則管理選單\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << "1. 新增溫度觸發規則\n2. 新增時間觸發規則\n3. 啟用/停用特定規則\n4. 刪除特定規則\n5. 返回主選單\n";
    int choice = getIntegerInput("請輸入選項 (1-5): ");

    if (choice == 1) {
        int id = getIntegerInput("請輸入新規則 ID: ");
        if (home.getRuleById(id)) {
            std::cout << "❌ 此規則 ID 已存在！\n";
            return;
        }
        std::string name = getStringInput("請輸入規則名稱: ");
        double threshold = getDoubleInput("請輸入溫度門檻 (°C): ");
        std::string cond = getStringInput("請輸入判斷條件 (輸入 > 或 <): ");
        if (cond != ">" && cond != "<") {
            std::cout << "❌ 無效的判斷條件！必須是 > 或 <\n";
            return;
        }
        int targetId = getIntegerInput("請輸入目標觸發設備 ID: ");
        if (!home.getDeviceById(targetId)) {
            std::cout << "⚠️ 目標設備不存在，仍會建立規則，但請在觸發前確認設備存在。\n";
        }
        int actionInt = getIntegerInput("請輸入觸發行為 (1=開啟, 0=關閉): ");
        bool action = (actionInt != 0);

        home.addRule(std::make_unique<TemperatureRule>(id, name, threshold, cond, targetId, action));
        std::cout << "✅ 成功建立溫度自動化規則。\n";
    } else if (choice == 2) {
        int id = getIntegerInput("請輸入新規則 ID: ");
        if (home.getRuleById(id)) {
            std::cout << "❌ 此規則 ID 已存在！\n";
            return;
        }
        std::string name = getStringInput("請輸入規則名稱: ");
        int hour = getIntegerInput("請輸入觸發小時 (0-23): ");
        if (hour < 0 || hour > 23) {
            std::cout << "❌ 時間無效！\n";
            return;
        }
        int targetId = getIntegerInput("請輸入目標觸發設備 ID: ");
        if (!home.getDeviceById(targetId)) {
            std::cout << "⚠️ 目標設備不存在。\n";
        }
        int actionInt = getIntegerInput("請輸入觸發行為 (1=開啟, 0=關閉): ");
        bool action = (actionInt != 0);

        home.addRule(std::make_unique<TimeRule>(id, name, hour, targetId, action));
        std::cout << "✅ 成功建立時間自動化規則。\n";
    } else if (choice == 3) {
        int id = getIntegerInput("請輸入規則 ID: ");
        AutomationRule* rule = home.getRuleById(id);
        if (!rule) {
            std::cout << "❌ 找不到此規則！\n";
            return;
        }
        bool state = rule->getIsActive();
        rule->setIsActive(!state);
        std::cout << "規則「" << rule->getName() << "」已變更為 " << (!state ? "啟用" : "停用") << "。\n";
        home.logEvent("規則變更: 將規則 ID " + std::to_string(id) + " 設定為 " + (!state ? "啟用" : "停用"));
    } else if (choice == 4) {
        int id = getIntegerInput("請輸入要刪除的規則 ID: ");
        if (home.removeRuleById(id)) {
            std::cout << "✅ 已刪除規則 ID: " << id << "\n";
        } else {
            std::cout << "❌ 找不到規則 ID: " << id << "\n";
        }
    }
}

// ==========================================
// 主程式進入點 (main)
// ==========================================

int main() {
    std::cout << "============================================================\n";
    std::cout << "        🌟 歡迎使用智慧家居設備模擬與自動化系統 🌟\n";
    std::cout << "============================================================\n";
    
    SmartHome home;
    std::string configPath = "config.txt";

    // 嘗試從 config.txt 載入，如果沒有則初始化預設數據
    std::cout << "正在載入配置檔案 [" << configPath << "]...\n";
    if (!home.loadConfig(configPath)) {
        std::cout << "⚠️ 未能讀取設定檔，初始化預設智慧家居配置數據...\n";
        
        // 預設設備
        home.addDevice(std::make_unique<SmartLight>(1, "客廳吸頂燈", false, 80, "暖色"));
        home.addDevice(std::make_unique<SmartThermostat>(2, "客廳冷氣機", false, 26.0, "制冷"));
        home.addDevice(std::make_unique<SmartCamera>(3, "玄關監視器", true, false, true));
        
        // 預設規則
        home.addRule(std::make_unique<TemperatureRule>(1, "高溫自動開啟冷氣", 28.0, ">", 2, true));
        home.addRule(std::make_unique<TimeRule>(2, "深夜自動關閉客廳燈", 23, 1, false));
        
        // 第一次儲存
        home.saveConfig(configPath);
    }

    bool running = true;
    while (running) {
        printDashboard(home);
        std::cout << "📋 主操作選單:\n";
        std::cout << "  1. 📱 手動控制設備\n";
        std::cout << "  2. 🌍 模擬環境參數變化 (時間/溫度/警報)\n";
        std::cout << "  3. ⚙️ 自動化規則管理\n";
        std::cout << "  4. 📜 查看系統事件日誌\n";
        std::cout << "  5. 📥 重新載入設定檔\n";
        std::cout << "  6. 💾 儲存目前配置\n";
        std::cout << "  7. 📊 導出事件日誌 (CSV)\n";
        std::cout << "  8. ❌ 結束程式\n";
        std::cout << "------------------------------------------------------------\n";
        
        int choice = getIntegerInput("請輸入選項 (1-8): ");
        switch (choice) {
            case 1:
                handleControlDevice(home);
                break;
            case 2:
                handleSimulateEnvironment(home);
                break;
            case 3:
                handleRuleManagement(home);
                break;
            case 4: {
                std::cout << "\n📋 系統歷史日誌列表:\n";
                const auto& logs = home.getEventLogs();
                if (logs.empty()) {
                    std::cout << "  (目前無日誌記錄)\n";
                } else {
                    for (const auto& log : logs) {
                        std::cout << "  " << log << "\n";
                    }
                }
                break;
            }
            case 5:
                home.loadConfig(configPath);
                break;
            case 6:
                home.saveConfig(configPath);
                std::cout << "💾 設定存檔成功！\n";
                break;
            case 7: {
                std::string logPath = "system_log.csv";
                if (home.exportLogs(logPath)) {
                    std::cout << "📊 事件日誌成功匯出至 " << logPath << "！\n";
                }
                break;
            }
            case 8:
                // 自動存檔後離開
                home.saveConfig(configPath);
                std::cout << "💾 配置已自動儲存。謝謝使用，程式即將結束。\n";
                running = false;
                break;
            default:
                std::cout << "❌ 選項無效，請重新輸入 1 至 8 之間的數字！\n";
                break;
        }
    }

    return 0;
}
