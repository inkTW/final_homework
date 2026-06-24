#ifndef SMART_THERMOSTAT_H
#define SMART_THERMOSTAT_H

#include "SmartDevice.h"
#include <sstream>
#include <iomanip>

class SmartThermostat : public SmartDevice {
private:
    double targetTemperature; // 目標溫度，如 26.0
    std::string mode; // 模式，例如 制冷 (Cooling), 制熱 (Heating), 送風 (Fan)

public:
    SmartThermostat(int deviceId, const std::string& deviceName, bool initialPower = false, double initialTemp = 26.0, const std::string& initialMode = "制冷")
        : SmartDevice(deviceId, deviceName, "Thermostat", initialPower), targetTemperature(initialTemp), mode(initialMode) {}

    double getTargetTemperature() const { return targetTemperature; }
    std::string getMode() const { return mode; }

    std::string getStatusReport() const override {
        std::stringstream ss;
        ss << "溫控狀態: [" << (isOn ? "ON" : "OFF") << "] | 設定溫度: " 
           << std::fixed << std::setprecision(1) << targetTemperature << "°C | 模式: " << mode;
        return ss.str();
    }

    void updateSetting(const std::string& key, double value) override {
        if (key == "temperature") {
            targetTemperature = value;
            if (targetTemperature < 16.0) targetTemperature = 16.0;
            if (targetTemperature > 30.0) targetTemperature = 30.0;
        }
    }

    void updateSetting(const std::string& key, const std::string& value) override {
        if (key == "mode") {
            mode = value;
        }
    }
};

#endif // SMART_THERMOSTAT_H
