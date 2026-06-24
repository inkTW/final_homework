#ifndef TEMPERATURE_RULE_H
#define TEMPERATURE_RULE_H

#include "AutomationRule.h"

class TemperatureRule : public AutomationRule {
private:
    double tempThreshold;
    std::string condition; // ">" 或 "<"
    int targetDeviceId;
    bool actionState; // true = 開啟, false = 關閉

public:
    TemperatureRule(int ruleId, const std::string& ruleName, double threshold, const std::string& cond, int targetId, bool action)
        : AutomationRule(ruleId, ruleName, "Temperature"), tempThreshold(threshold), condition(cond), targetDeviceId(targetId), actionState(action) {}

    double getThreshold() const { return tempThreshold; }
    std::string getCondition() const { return condition; }
    int getTargetDeviceId() const { return targetDeviceId; }
    bool getActionState() const { return actionState; }

    bool checkAndTrigger(SmartHome& home) override;
    std::string getRuleDescription() const override;
};

#endif // TEMPERATURE_RULE_H
