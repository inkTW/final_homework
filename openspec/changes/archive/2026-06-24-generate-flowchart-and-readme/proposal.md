## Why

The Smart Home automation project currently lacks unified system documentation and a visual flow representation. Developers and users cannot easily understand how the polymorphic smart devices, the automation engine, and the terminal UI interact. To improve onboarding, system transparency, and overall codebase readability, we need a comprehensive `README.md` and an interactive/visual flow diagram detailing the execution loop and rule evaluation logic.

## What Changes

- Add a top-level `README.md` containing project introduction, architecture summary, installation/building steps, and system usage guidelines.
- Add an architectural and execution flow chart (using Mermaid or static assets) within the `README.md` explaining the main execution loop, polymorphic device hierarchy, and rule checking process.
- Create a dedicated spec/documentation artifact or capability for this documentation.

## Capabilities

### New Capabilities
- `documentation-and-flows`: This capability introduces comprehensive project-level documentation, including a system architecture flowchart and a detailed developer manual.

### Modified Capabilities
<!-- None -->

## Impact

This is a pure documentation and illustration change. It does not affect any existing compiled binaries, libraries, or execution logic of the Smart Home system. It only improves developers' understanding and guides building/running of the application.
