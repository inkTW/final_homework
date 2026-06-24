## Context

The Smart Home automation project is built with C++ and uses OOP features like class inheritance and polymorphism. It has a command-line interface to interact with smart devices (Lights, Thermostats, Cameras) and automation rules (based on time and temperature thresholds). The project currently does not have a top-level README.md, nor does it have visual flow diagrams depicting class hierarchies and execution loops. We need to create these to improve project clarity.

## Goals / Non-Goals

**Goals:**
- Create a comprehensive `README.md` at the project root directory.
- Provide a class diagram in Mermaid syntax displaying relationships between `SmartDevice` (and its sub-classes) and `AutomationRule` (and its sub-classes).
- Provide a sequence/flow chart in Mermaid syntax outlining the main loop inside `src/main.cpp` (dashboard display, selection menu, control options, environmental parameters simulation, and automated rule check).
- Outline building steps and input validation strategies in the documentation.

**Non-Goals:**
- Modifying the actual C++ source files or logic.
- Adding unit test frameworks or code changes.

## Decisions

1. **Use Mermaid Diagrams in README.md**:
   - *Alternative Considered*: External image files (e.g. PNG).
   - *Rationale*: Mermaid diagrams are text-based, easily version-controlled, and natively rendered by GitHub, Gitlab, and VS Code. They avoid bloating the repository with binary image files.

2. **README Structure**:
   - Provide Sections: Introduction, Project Structure, Architecture Diagram, Execution/Data Flow, Getting Started (g++ / Make commands), and Features.
   - *Rationale*: A standard, descriptive layout makes the repository highly professional and easy for grading or developer contribution.

## Risks / Trade-offs

- **Risk**: GitHub markdown renderers might show raw Mermaid text if rendering fails.
  - *Mitigation*: Write clean, valid Mermaid syntax using simple blocks and ensure no HTML entities or complex parentheses break parsing.
