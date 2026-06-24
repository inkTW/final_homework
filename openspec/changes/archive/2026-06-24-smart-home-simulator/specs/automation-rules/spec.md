## ADDED Requirements

### Requirement: Automation Rules Triggering
The system SHALL support an automation engine with rules that trigger device actions based on environmental state variables (current hour, ambient temperature, motion detection). Rules MUST be modeled using inheritance from a base `AutomationRule` class.

#### Scenario: Temperature exceeds threshold trigger
- **WHEN** the ambient temperature rises to 29.0 degrees and there is a rule to turn on the air conditioner at >28.0 degrees
- **THEN** the system SHALL turn on the air conditioner device and log the trigger event

#### Scenario: Time matching rule trigger
- **WHEN** the simulation clock advances to 22:00 and there is a rule to turn off the lights at 22:00
- **THEN** the system SHALL turn off the lights and log the trigger event
