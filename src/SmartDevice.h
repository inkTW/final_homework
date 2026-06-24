#ifndef SMART_DEVICE_H
#define SMART_DEVICE_H

#include <string>

class SmartDevice {
protected:
    int id;
    std::string name;
    bool isOn;
    std::string type;

public:
    SmartDevice(int deviceId, const std::string& deviceName, const std::string& deviceType, bool initialPower = false)
        : id(deviceId), name(deviceName), type(deviceType), isOn(initialPower) {}

    virtual ~SmartDevice() = default; // 虛擬解構子，確保多型釋放時衍生類別記憶體能正確釋放

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getType() const { return type; }
    bool getIsOn() const { return isOn; }

    virtual void turnOn() {
        isOn = true;
    }

    virtual void turnOff() {
        isOn = false;
    }

    // 純虛擬函數：子類別必須實作以回報詳細狀態
    virtual std::string getStatusReport() const = 0;

    // 虛擬函數：更新設定（如亮度、溫度），子類別可覆寫
    virtual void updateSetting(const std::string& key, double value) {}
    virtual void updateSetting(const std::string& key, const std::string& value) {}
};

#endif // SMART_DEVICE_H
