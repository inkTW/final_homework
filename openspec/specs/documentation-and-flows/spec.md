# documentation-and-flows Specification

## Purpose
TBD - created by archiving change generate-flowchart-and-readme. Update Purpose after archive.
## Requirements
### Requirement: README Document and Setup Guide
The system SHALL provide a README.md file in the project root directory containing setup guides, installation instructions, usage manuals, and basic concepts of the Smart Home Automation System.

#### Scenario: User opens README.md
- **WHEN** the user opens the README.md file
- **THEN** the system SHALL show the project title, features, building instruction using g++ or make, and explanation of devices/rules.

### Requirement: Architecture and Process Flowcharts
The system README.md SHALL include visual representation (in Mermaid syntax) of the system architecture (class relations/hierarchy) and the main execution/event loop of the application (sensor polling, rule evaluation, action triggering).

#### Scenario: Developer reads architecture flowchart
- **WHEN** a developer views the Mermaid flowcharts in README.md
- **THEN** the system SHALL clearly depict the Polymorphic SmartDevice hierarchy, AutomationRule evaluation logic, and command flow.

