## ADDED Requirements

### Requirement: Polymorphic Smart Devices
The system SHALL define a base class `SmartDevice` and derived classes `SmartLight`, `SmartThermostat`, and `SmartCamera`. The base class MUST define a virtual interface for turning the device on/off, adjusting its settings, and generating a string status report.

#### Scenario: Turn on smart light
- **WHEN** user issues command to turn on a SmartLight with ID 1
- **THEN** the system SHALL set the light's power state to true and print a status message

#### Scenario: Adjust smart thermostat temperature
- **WHEN** user issues command to set SmartThermostat ID 2 temperature to 24.5 degrees
- **THEN** the system SHALL update the target temperature to 24.5 and output the new setting

#### Scenario: Get status report from camera
- **WHEN** the system requests status report for SmartCamera ID 3
- **THEN** the system SHALL return a string specifying the recording and motion alert states
