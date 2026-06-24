#ifndef SMART_HOME_H
#define SMART_HOME_H

#include <vector>
#include <memory>
#include <string>
#include "SmartDevice.h"
#include "AutomationRule.h"

class SmartHome {
private:
    std::vector<std::unique_ptr<SmartDevice>> devices;       // 管理所有智慧設備的 STL 多型容器
    std::vector<std::unique_ptr<AutomationRule>> rules;     // 管理所有自動化規則的 STL 多型容器
    std::vector<std::string> eventLogs;                      // 快取系統事件日誌的 STL 容器

    // 環境變數
    double ambientTemperature;
    int currentHour;
    bool motionDetected;

public:
    SmartHome();
    ~SmartHome() = default;

    // 設備管理
    void addDevice(std::unique_ptr<SmartDevice> device);
    const std::vector<std::unique_ptr<SmartDevice>>& getDevices() const { return devices; }
    SmartDevice* getDeviceById(int id);
    bool removeDeviceById(int id);

    // 規則管理
    void addRule(std::unique_ptr<AutomationRule> rule);
    const std::vector<std::unique_ptr<AutomationRule>>& getRules() const { return rules; }
    AutomationRule* getRuleById(int id);
    bool removeRuleById(int id);

    // 環境參數管理
    double getAmbientTemperature() const { return ambientTemperature; }
    int getCurrentHour() const { return currentHour; }
    bool getMotionDetected() const { return motionDetected; }
    void setAmbientTemperature(double temp) { ambientTemperature = temp; }
    void setCurrentHour(int hour) { currentHour = hour; }
    void setMotionDetected(bool motion) { motionDetected = motion; }

    // 日誌管理
    void logEvent(const std::string& message);
    const std::vector<std::string>& getEventLogs() const { return eventLogs; }
    void clearEventLogs() { eventLogs.clear(); }

    // 自動化運作
    void runAutomation();

    // 檔案讀寫
    bool loadConfig(const std::string& filepath);
    bool saveConfig(const std::string& filepath);
    bool exportLogs(const std::string& filepath);
};

#endif // SMART_HOME_H
