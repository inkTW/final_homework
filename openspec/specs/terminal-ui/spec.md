# Purpose
終端機選單與環境模擬規格定義。

# Requirements

### Requirement: Terminal UI and Environment Simulation
The system SHALL provide an interactive text-based dashboard and menu interface in the terminal, including environment simulation controls and robust input validation.

#### Scenario: Display main dashboard
- **WHEN** the user runs the application or returns to the main menu
- **THEN** the system SHALL display current ambient environment status, a list of all devices and their states, active automation rules, and a selection menu

#### Scenario: Input validation for menu selection
- **WHEN** the user inputs non-numeric characters or out-of-range choices for menu options
- **THEN** the system SHALL clear the error state, clear the input buffer, and prompt the user to input a valid number
