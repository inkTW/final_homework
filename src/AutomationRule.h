#ifndef AUTOMATION_RULE_H
#define AUTOMATION_RULE_H

#include <string>

// 向前宣告 SmartHome 類別，避免循環包含
class SmartHome;

class AutomationRule {
protected:
    int id;
    std::string name;
    bool isActive;
    std::string type;

public:
    AutomationRule(int ruleId, const std::string& ruleName, const std::string& ruleType, bool initialActive = true)
        : id(ruleId), name(ruleName), type(ruleType), isActive(initialActive) {}

    virtual ~AutomationRule() = default; // 虛擬解構子，確保生命週期釋放安全

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getType() const { return type; }
    bool getIsActive() const { return isActive; }
    void setIsActive(bool active) { isActive = active; }

    // 純虛擬函數：輪詢檢查環境變數並觸發控制，回傳是否觸發成功
    virtual bool checkAndTrigger(SmartHome& home) = 0;

    // 純虛擬函數：取得規則的詳細規則描述
    virtual std::string getRuleDescription() const = 0;
};

#endif // AUTOMATION_RULE_H
