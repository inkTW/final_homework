#ifndef TIME_RULE_H
#define TIME_RULE_H

#include "AutomationRule.h"

class TimeRule : public AutomationRule {
private:
    int triggerHour; // 觸發時間（0 ~ 23 小時）
    int targetDeviceId;
    bool actionState; // true = 開啟, false = 關閉

public:
    TimeRule(int ruleId, const std::string& ruleName, int hour, int targetId, bool action)
        : AutomationRule(ruleId, ruleName, "Time"), triggerHour(hour), targetDeviceId(targetId), actionState(action) {}

    int getTriggerHour() const { return triggerHour; }
    int getTargetDeviceId() const { return targetDeviceId; }
    bool getActionState() const { return actionState; }

    bool checkAndTrigger(SmartHome& home) override;
    std::string getRuleDescription() const override;
};

#endif // TIME_RULE_H
