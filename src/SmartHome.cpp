#include "SmartHome.h"
#include "SmartLight.h"
#include "SmartThermostat.h"
#include "SmartCamera.h"
#include "TemperatureRule.h"
#include "TimeRule.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

// ==========================================
// SmartHome 類別實作
// ==========================================

SmartHome::SmartHome()
    : ambientTemperature(25.0), currentHour(12), motionDetected(false) {
    logEvent("智慧家居控制系統初始化完成。");
}

void SmartHome::addDevice(std::unique_ptr<SmartDevice> device) {
    if (device) {
        logEvent("新增設備: " + device->getName() + " (ID: " + std::to_string(device->getId()) + ", 類型: " + device->getType() + ")");
        devices.push_back(std::move(device));
    }
}

SmartDevice* SmartHome::getDeviceById(int id) {
    for (const auto& dev : devices) {
        if (dev->getId() == id) {
            return dev.get();
        }
    }
    return nullptr;
}

bool SmartHome::removeDeviceById(int id) {
    auto it = std::remove_if(devices.begin(), devices.end(),
        [id](const std::unique_ptr<SmartDevice>& dev) { return dev->getId() == id; });
    if (it != devices.end()) {
        logEvent("移除設備 ID: " + std::to_string(id));
        devices.erase(it, devices.end());
        return true;
    }
    return false;
}

void SmartHome::addRule(std::unique_ptr<AutomationRule> rule) {
    if (rule) {
        logEvent("新增自動化規則: " + rule->getName() + " (ID: " + std::to_string(rule->getId()) + ", 類型: " + rule->getType() + ")");
        rules.push_back(std::move(rule));
    }
}

AutomationRule* SmartHome::getRuleById(int id) {
    for (const auto& rule : rules) {
        if (rule->getId() == id) {
            return rule.get();
        }
    }
    return nullptr;
}

bool SmartHome::removeRuleById(int id) {
    auto it = std::remove_if(rules.begin(), rules.end(),
        [id](const std::unique_ptr<AutomationRule>& rule) { return rule->getId() == id; });
    if (it != rules.end()) {
        logEvent("移除自動化規則 ID: " + std::to_string(id));
        rules.erase(it, rules.end());
        return true;
    }
    return false;
}

void SmartHome::logEvent(const std::string& message) {
    std::stringstream ss;
    ss << "[" << std::setw(2) << std::setfill('0') << currentHour << ":00] " << message;
    eventLogs.push_back(ss.str());
}

void SmartHome::runAutomation() {
    for (auto& rule : rules) {
        if (rule->getIsActive()) {
            rule->checkAndTrigger(*this);
        }
    }
}

// ==========================================
// TemperatureRule 類別實作
// ==========================================

bool TemperatureRule::checkAndTrigger(SmartHome& home) {
    double currentTemp = home.getAmbientTemperature();
    bool isTriggered = false;
    
    if (condition == ">" && currentTemp > tempThreshold) {
        isTriggered = true;
    } else if (condition == "<" && currentTemp < tempThreshold) {
        isTriggered = true;
    }

    if (isTriggered) {
        SmartDevice* dev = home.getDeviceById(targetDeviceId);
        if (dev) {
            if (actionState && !dev->getIsOn()) {
                dev->turnOn();
                home.logEvent("自動化規則 [" + name + "] 觸發: 環境溫度 " + 
                              std::to_string(currentTemp).substr(0, 4) + "°C " + condition + " 門檻 " +
                              std::to_string(tempThreshold).substr(0, 4) + "°C，自動開啟「" + dev->getName() + "」");
                return true;
            } else if (!actionState && dev->getIsOn()) {
                dev->turnOff();
                home.logEvent("自動化規則 [" + name + "] 觸發: 環境溫度 " + 
                              std::to_string(currentTemp).substr(0, 4) + "°C " + condition + " 門檻 " +
                              std::to_string(tempThreshold).substr(0, 4) + "°C，自動關閉「" + dev->getName() + "」");
                return true;
            }
        }
    }
    return false;
}

std::string TemperatureRule::getRuleDescription() const {
    std::stringstream ss;
    ss << "溫度觸發 (" << (isActive ? "已啟用" : "已停用") << "): 當室溫 " 
       << condition << " " << std::fixed << std::setprecision(1) << tempThreshold << "°C 時，"
       << (actionState ? "開啟" : "關閉") << "設備 ID " << targetDeviceId;
    return ss.str();
}

// ==========================================
// TimeRule 類別實作
// ==========================================

bool TimeRule::checkAndTrigger(SmartHome& home) {
    int currentHour = home.getCurrentHour();
    
    if (currentHour == triggerHour) {
        SmartDevice* dev = home.getDeviceById(targetDeviceId);
        if (dev) {
            if (actionState && !dev->getIsOn()) {
                dev->turnOn();
                home.logEvent("自動化規則 [" + name + "] 觸發: 時間到達 " + 
                              std::to_string(triggerHour) + ":00，自動開啟「" + dev->getName() + "」");
                return true;
            } else if (!actionState && dev->getIsOn()) {
                dev->turnOff();
                home.logEvent("自動化規則 [" + name + "] 觸發: 時間到達 " + 
                              std::to_string(triggerHour) + ":00，自動關閉「" + dev->getName() + "」");
                return true;
            }
        }
    }
    return false;
}

std::string TimeRule::getRuleDescription() const {
    std::stringstream ss;
    ss << "時間觸發 (" << (isActive ? "已啟用" : "已停用") << "): 當時間到達 " 
       << std::setw(2) << std::setfill('0') << triggerHour << ":00 時，"
       << (actionState ? "開啟" : "關閉") << "設備 ID " << targetDeviceId;
    return ss.str();
}

// ==========================================
// 檔案持久化讀寫實作 (File I/O)
// ==========================================

bool SmartHome::loadConfig(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        logEvent("載入設定檔失敗: 無法開啟檔案 " + filepath);
        return false;
    }

    devices.clear();
    rules.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string tag;
        ss >> tag;

        if (tag == "DEVICE") {
            int id;
            std::string type, name;
            bool isOn;
            ss >> id >> type >> name >> isOn;
            
            if (type == "Light") {
                int brightness;
                std::string color;
                ss >> brightness >> color;
                addDevice(std::make_unique<SmartLight>(id, name, isOn, brightness, color));
            } else if (type == "Thermostat") {
                double targetTemp;
                std::string mode;
                ss >> targetTemp >> mode;
                addDevice(std::make_unique<SmartThermostat>(id, name, isOn, targetTemp, mode));
            } else if (type == "Camera") {
                bool recording, motionAlert;
                ss >> recording >> motionAlert;
                addDevice(std::make_unique<SmartCamera>(id, name, isOn, recording, motionAlert));
            }
        } else if (tag == "RULE") {
            int id;
            std::string type, name;
            ss >> id >> type >> name;
            if (type == "TEMP") {
                double threshold;
                std::string cond;
                int targetId;
                bool action;
                ss >> threshold >> cond >> targetId >> action;
                addRule(std::make_unique<TemperatureRule>(id, name, threshold, cond, targetId, action));
            } else if (type == "TIME") {
                int hour, targetId;
                bool action;
                ss >> hour >> targetId >> action;
                addRule(std::make_unique<TimeRule>(id, name, hour, targetId, action));
            }
        }
    }
    
    file.close();
    logEvent("設定檔載入成功: " + filepath);
    return true;
}

bool SmartHome::saveConfig(const std::string& filepath) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        logEvent("儲存設定檔失敗: 無法開啟檔案 " + filepath);
        return false;
    }

    file << "# 智慧家居系統存檔設定檔\n";
    file << "# DEVICE [ID] [Type] [Name] [isOn] [屬性1] [屬性2]\n";
    file << "# RULE [ID] [Type] [Name] [觸發條件...]\n\n";

    for (const auto& dev : devices) {
        file << "DEVICE " << dev->getId() << " " << dev->getType() << " " << dev->getName() << " " << dev->getIsOn();
        if (dev->getType() == "Light") {
            auto light = static_cast<SmartLight*>(dev.get());
            file << " " << light->getBrightness() << " " << light->getColor();
        } else if (dev->getType() == "Thermostat") {
            auto thermo = static_cast<SmartThermostat*>(dev.get());
            file << " " << thermo->getTargetTemperature() << " " << thermo->getMode();
        } else if (dev->getType() == "Camera") {
            auto cam = static_cast<SmartCamera*>(dev.get());
            file << " " << cam->getIsRecording() << " " << cam->getMotionDetectionEnabled();
        }
        file << "\n";
    }

    file << "\n";

    for (const auto& rule : rules) {
        file << "RULE " << rule->getId() << " " << (rule->getType() == "Temperature" ? "TEMP" : "TIME") << " " << rule->getName();
        if (rule->getType() == "Temperature") {
            auto tempRule = static_cast<TemperatureRule*>(rule.get());
            file << " " << tempRule->getThreshold() << " " << tempRule->getCondition() << " " << tempRule->getTargetDeviceId() << " " << tempRule->getActionState();
        } else if (rule->getType() == "Time") {
            auto timeRule = static_cast<TimeRule*>(rule.get());
            file << " " << timeRule->getTriggerHour() << " " << timeRule->getTargetDeviceId() << " " << timeRule->getActionState();
        }
        file << "\n";
    }

    file.close();
    logEvent("系統設定已儲存至 " + filepath);
    return true;
}

bool SmartHome::exportLogs(const std::string& filepath) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        logEvent("導出事件日誌失敗: 無法開啟檔案 " + filepath);
        return false;
    }

    file << "時間,事件說明\n";
    for (const auto& log : eventLogs) {
        // 解析格式 "[12:00] 事件內容" -> CSV "12:00,事件內容"
        if (log.size() > 8 && log[0] == '[' && log[6] == ']' && log[7] == ' ') {
            std::string time = log.substr(1, 5);
            std::string desc = log.substr(8);
            file << time << "," << desc << "\n";
        } else {
            file << "," << log << "\n";
        }
    }

    file.close();
    logEvent("事件日誌成功匯出至 " + filepath);
    return true;
}
