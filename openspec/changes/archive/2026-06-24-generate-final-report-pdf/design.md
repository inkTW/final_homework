## Context

The C++ final project requires a PDF report named with the student's ID containing:
1. Cover page
2. Features description
3. Terminal execution screenshots/screens with text explanation
4. GitHub repo link

Since we are on a Windows platform with Node and Python installed, we can automate this report compilation using a Python script in a local virtual environment.

## Goals / Non-Goals

**Goals:**
- Create a Python script `scripts/generate_report.py` to compile a professional final report PDF.
- Use `fpdf2` or `reportlab` to design the PDF layout.
- Embed the Mermaid class and workflow diagrams (rendered or styled).
- Include terminal execution screen mockups (rendered as vector text blocks or captured images).
- Support custom CLI arguments: `--id` (Student ID), `--name` (Student Name), `--repo` (GitHub URL).

**Non-Goals:**
- Creating a GUI wizard to edit the report.

## Decisions

1. **Use `fpdf2` for PDF compilation**:
   - *Rationale*: `fpdf2` is lightweight, easy to install in a virtual environment, and supports basic styling (headers, footers, page numbers, text wrapping, and image embedding).

2. **Render Terminal Output in a styled Box**:
   - *Rationale*: A real PNG screenshot can be blurry and hard to capture in headless CI/CD. Rendering the actual console text inside a styled grey vector block with a monospaced font in the PDF looks extremely professional, maintains 100% vector sharpness, and satisfies the "程式執行檔畫面" (program execution screen) requirement.

3. **Incorporate Class and Workflow Diagrams**:
   - Explain the class hierarchy and process loop inside the text, and render/style the flows.

## Risks / Trade-offs

- **Risk**: Chinese characters (Traditional Chinese) might fail to render in standard FPDF fonts (which only support Latin-1 by default).
  - *Mitigation*: The Python script must load a TrueType Unicode font (e.g. Microsoft JhengHei `msjh.ttc` or another font installed on the system, such as `fireflysung` or generic Windows Chinese fonts like `kaiu.ttf`, `simsun.ttc`, or we can download/bundle a free Chinese font or use local Windows fonts path `C:\Windows\Fonts\msjh.ttc`).
