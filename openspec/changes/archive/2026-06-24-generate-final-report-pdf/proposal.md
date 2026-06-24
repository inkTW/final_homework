## Why

The user needs to generate a final homework report PDF for their Smart Home project to upload to Flipclass. The report must contain:
1. Cover page (with Student ID, Name, Project Title).
2. Features and architecture description of the Smart Home project.
3. Screenshots of terminal execution with explanatory text.
4. GitHub repository URL.
The file should be named with the student's ID (e.g., `A0927011667.pdf`).

## What Changes

- Create a Python script `scripts/generate_report.py` in the workspace to automatically compile a PDF report.
- The script will read text/metadata, assemble a cover page, include the class diagrams, embed project screenshots, and export a formatted PDF file.
- Add a requirements file or setup virtual environment to support PDF library (`fpdf2` or `reportlab`).

## Capabilities

### New Capabilities
- `report-generation`: This capability introduces a automated report generation script using Python to compile the C++ Smart Home final report into a PDF document according to Flipclass requirements.

### Modified Capabilities
<!-- None -->

## Impact

This is a tooling and documentation change. It adds a Python script (`scripts/generate_report.py`) and a virtual environment. It does not affect the C++ Smart Home source files.
