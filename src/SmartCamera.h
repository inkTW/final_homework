#ifndef SMART_CAMERA_H
#define SMART_CAMERA_H

#include "SmartDevice.h"
#include <sstream>

class SmartCamera : public SmartDevice {
private:
    bool isRecording; // 是否正在錄影
    bool motionDetectionEnabled; // 是否啟用動態感應

public:
    SmartCamera(int deviceId, const std::string& deviceName, bool initialPower = false, bool recordingState = false, bool motionAlert = true)
        : SmartDevice(deviceId, deviceName, "Camera", initialPower), isRecording(recordingState), motionDetectionEnabled(motionAlert) {}

    bool getIsRecording() const { return isRecording; }
    bool getMotionDetectionEnabled() const { return motionDetectionEnabled; }

    void setRecording(bool rec) { isRecording = rec; }
    void setMotionDetectionEnabled(bool alert) { motionDetectionEnabled = alert; }

    std::string getStatusReport() const override {
        std::stringstream ss;
        ss << "相機狀態: [" << (isOn ? "ON" : "OFF") << "] | 錄影: " 
           << (isRecording ? "正在錄影" : "未錄影") << " | 動態監測: " << (motionDetectionEnabled ? "已啟用" : "已停用");
        return ss.str();
    }

    void turnOff() override {
        SmartDevice::turnOff();
        isRecording = false; // 設備關閉時自動停止錄影
    }

    void updateSetting(const std::string& key, double value) override {
        if (key == "recording") {
            isRecording = (value != 0.0);
        } else if (key == "motion_alert") {
            motionDetectionEnabled = (value != 0.0);
        }
    }
};

#endif // SMART_CAMERA_H
