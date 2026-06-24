# Purpose
設定檔讀取寫入與日誌持久化規格定義。

# Requirements

### Requirement: File Storage and Configuration Loading
The system SHALL be able to read device lists and automation rules from a configuration file at startup, write the current configuration back to a file upon saving, and export system event logs to a CSV file.

#### Scenario: Load configuration on startup
- **WHEN** the system starts and a valid config file exists with defined devices and rules
- **THEN** the system SHALL parse the file and initialize corresponding SmartDevice and AutomationRule objects in memory

#### Scenario: Save current state
- **WHEN** the user selects the save option from the menu
- **THEN** the system SHALL serialize all devices and rules to a configuration file

#### Scenario: Export event logs
- **WHEN** the user selects the option to export logs
- **THEN** the system SHALL write all buffered event logs to a CSV file with timestamped columns
