## MODIFIED Requirements

### Requirement: Terminal UI and Environment Simulation
The system SHALL provide an interactive text-based dashboard and menu interface in the terminal, including environment simulation controls and robust input validation. On Windows systems, the system MUST configure the active console input and output code pages to UTF-8 (CP_UTF8) on startup to prevent text corruption (garbage characters).

#### Scenario: Display main dashboard
- **WHEN** the user runs the application or returns to the main menu
- **THEN** the system SHALL display current ambient environment status, a list of all devices and their states, active automation rules, and a selection menu

#### Scenario: Input validation for menu selection
- **WHEN** the user inputs non-numeric characters or out-of-range choices for menu options
- **THEN** the system SHALL clear the error state, clear the input buffer, and prompt the user to input a valid number

#### Scenario: Windows console UTF-8 initialization
- **WHEN** the application starts on a Windows platform
- **THEN** the system SHALL invoke SetConsoleOutputCP(CP_UTF8) and SetConsoleCP(CP_UTF8) before printing any text to standard output
