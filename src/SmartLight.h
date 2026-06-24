#ifndef SMART_LIGHT_H
#define SMART_LIGHT_H

#include "SmartDevice.h"
#include <sstream>

class SmartLight : public SmartDevice {
private:
    int brightness; // 亮度範圍：0 ~ 100
    std::string color; // 顏色，例如 Warm White, Daylight, Blue 等

public:
    SmartLight(int deviceId, const std::string& deviceName, bool initialPower = false, int initialBrightness = 80, const std::string& initialColor = "暖白色")
        : SmartDevice(deviceId, deviceName, "Light", initialPower), brightness(initialBrightness), color(initialColor) {}

    int getBrightness() const { return brightness; }
    std::string getColor() const { return color; }

    std::string getStatusReport() const override {
        std::stringstream ss;
        ss << "燈光狀態: [" << (isOn ? "ON" : "OFF") << "] | 亮度: " << brightness << "% | 色溫: " << color;
        return ss.str();
    }

    void updateSetting(const std::string& key, double value) override {
        if (key == "brightness") {
            brightness = static_cast<int>(value);
            if (brightness < 0) brightness = 0;
            if (brightness > 100) brightness = 100;
        }
    }

    void updateSetting(const std::string& key, const std::string& value) override {
        if (key == "color") {
            color = value;
        }
    }
};

#endif // SMART_LIGHT_H
