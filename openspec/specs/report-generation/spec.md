# report-generation Specification

## Purpose
TBD - created by archiving change generate-final-report-pdf. Update Purpose after archive.
## Requirements
### Requirement: Cover Page Generation
The report generation tool SHALL compile a cover page for the PDF document containing the Course Title ("物件導向程式設計期末專題"), Project Title ("智慧家居自動化系統"), Student Name, Student ID, and the Date.

#### Scenario: Verify cover page elements
- **WHEN** the PDF is generated
- **THEN** the first page of the PDF SHALL display the Course Title, Project Title, Student Name, Student ID, and Date in centered, clearly readable text.

### Requirement: Content Layout and Sections
The PDF report SHALL contain distinct sections including:
1. Feature Description (呈現 C++ 類別繼承、讀寫檔、STL 容器、終端機 UI)
2. Architecture Diagram (Class diagram and Main loop flow)
3. Terminal Screenshots with explanations
4. GitHub Repository Link

#### Scenario: Verify sections in generated PDF
- **WHEN** the PDF is compiled
- **THEN** it SHALL include feature descriptions, class structure illustrations, and a working GitHub link.

### Requirement: Screenshot Integration
The report generation tool SHALL render and insert screenshots of the running C++ application in the PDF report, together with caption texts explaining the illustrated system actions.

#### Scenario: Verify screenshot display
- **WHEN** the report is generated
- **THEN** the PDF SHALL display at least one image showing the terminal UI executing with descriptive text beneath it.

### Requirement: Dynamic Student ID Naming
The generated PDF file MUST be named using the user's student ID (e.g. `<student_id>.pdf`).

#### Scenario: Verify output filename
- **WHEN** the tool completes generation with student ID "A0927011667"
- **THEN** the output file in the workspace root SHALL be named "A0927011667.pdf".

