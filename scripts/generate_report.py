import os
import argparse
from datetime import datetime
from fpdf import FPDF

class FinalReportPDF(FPDF):
    def header(self):
        if self.page_no() > 1:
            self.set_font("msjh", size=9)
            self.set_text_color(128, 128, 128)
            self.cell(0, 10, "物件導向程式設計期末專題報告 —— 智慧家居自動化系統", align="R", new_x="LMARGIN", new_y="NEXT")
            self.line(20, 18, 190, 18)
            self.ln(5)

    def footer(self):
        if self.page_no() > 1:
            self.set_y(-15)
            self.set_font("msjh", size=9)
            self.set_text_color(128, 128, 128)
            self.cell(0, 10, f"第 {self.page_no()} 頁", align="C")

def draw_section_header(pdf, title):
    pdf.set_font("msjh", style="B", size=14)
    pdf.set_text_color(26, 54, 93) # Deep Blue
    pdf.cell(0, 10, title, new_x="LMARGIN", new_y="NEXT")
    pdf.set_draw_color(26, 54, 93)
    pdf.set_line_width(0.5)
    pdf.line(pdf.get_x(), pdf.get_y(), pdf.get_x() + 170, pdf.get_y())
    pdf.ln(5)

def draw_bullet_point(pdf, bold_txt, normal_txt):
    pdf.set_font("msjh", style="B", size=10)
    pdf.set_text_color(45, 55, 72)
    pdf.write(6, "• " + bold_txt + "：")
    pdf.set_font("msjh", size=10)
    pdf.set_text_color(74, 85, 104)
    pdf.write(6, normal_txt + "\n")
    pdf.ln(1)

def draw_terminal_screen(pdf, title, lines):
    pdf.set_font("msjh", style="B", size=10)
    pdf.set_text_color(45, 55, 72)
    pdf.cell(0, 8, title, new_x="LMARGIN", new_y="NEXT")
    
    # Save current position
    start_x = pdf.get_x()
    start_y = pdf.get_y()
    
    pdf.set_font("msjh", size=9)
    pdf.set_text_color(240, 240, 240)
    
    # Calculate box height
    lh = 5
    box_height = len(lines) * lh + 6
    
    # Draw terminal background
    pdf.set_fill_color(30, 30, 30) # Dark Charcoal
    pdf.rect(start_x, start_y, 170, box_height, style="F")
    
    pdf.set_x(start_x + 5)
    pdf.set_y(start_y + 3)
    for line in lines:
        pdf.cell(0, lh, line, new_x="LMARGIN", new_y="NEXT")
        pdf.set_x(start_x + 5)
        
    pdf.set_y(start_y + box_height)
    pdf.ln(4)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--id", default="4B4G0104")
    parser.add_argument("--name", default="洪鼎揚")
    parser.add_argument("--repo", default="https://github.com/inkTW/final_homework")
    args = parser.parse_args()

    pdf = FinalReportPDF(orientation="P", unit="mm", format="A4")
    pdf.set_margins(20, 20, 20)
    
    # Load Unicode Font (Microsoft JhengHei)
    font_path = "C:/Windows/Fonts/msjh.ttc"
    pdf.add_font("msjh", "", font_path)
    pdf.add_font("msjh", "B", font_path)

    # ----------------------------------------------------
    # COVER PAGE
    # ----------------------------------------------------
    pdf.add_page()
    
    # Course Title
    pdf.set_font("msjh", style="B", size=18)
    pdf.set_text_color(74, 85, 104)
    pdf.cell(0, 20, "南臺科技大學資訊工程系", align="C", new_x="LMARGIN", new_y="NEXT")
    pdf.cell(0, 10, "物件導向程式設計期末專題報告", align="C", new_x="LMARGIN", new_y="NEXT")
    pdf.ln(25)
    
    # Project Title
    pdf.set_font("msjh", style="B", size=26)
    pdf.set_text_color(26, 54, 93) # Deep Blue
    pdf.cell(0, 15, "🏠 智慧家居自動化系統", align="C", new_x="LMARGIN", new_y="NEXT")
    pdf.set_font("msjh", style="B", size=16)
    pdf.set_text_color(102, 102, 102)
    pdf.cell(0, 10, "Smart Home Automation System Simulator", align="C", new_x="LMARGIN", new_y="NEXT")
    
    # Decorative line
    pdf.ln(10)
    pdf.set_draw_color(26, 54, 93)
    pdf.set_line_width(1.5)
    pdf.line(40, pdf.get_y(), 170, pdf.get_y())
    pdf.ln(35)
    
    # Student Info Table
    pdf.set_font("msjh", style="B", size=12)
    pdf.set_text_color(45, 55, 72)
    
    info_x = 60
    pdf.set_x(info_x)
    pdf.cell(30, 10, "學生姓名：", align="L")
    pdf.set_font("msjh", size=12)
    pdf.cell(60, 10, args.name, align="L", new_x="LMARGIN", new_y="NEXT")
    
    pdf.set_x(info_x)
    pdf.set_font("msjh", style="B", size=12)
    pdf.cell(30, 10, "學生學號：", align="L")
    pdf.set_font("msjh", size=12)
    pdf.cell(60, 10, args.id, align="L", new_x="LMARGIN", new_y="NEXT")
    
    pdf.set_x(info_x)
    pdf.set_font("msjh", style="B", size=12)
    pdf.cell(30, 10, "指導教授：", align="L")
    pdf.set_font("msjh", size=12)
    pdf.cell(60, 10, "謝智能 教授", align="L", new_x="LMARGIN", new_y="NEXT")
    
    pdf.set_x(info_x)
    pdf.set_font("msjh", style="B", size=12)
    pdf.cell(30, 10, "繳交日期：", align="L")
    pdf.set_font("msjh", size=12)
    pdf.cell(60, 10, datetime.now().strftime("%Y 年 %m 月 %d 日"), align="L", new_x="LMARGIN", new_y="NEXT")

    # ----------------------------------------------------
    # SECTION 1: 功能說明
    # ----------------------------------------------------
    pdf.add_page()
    draw_section_header(pdf, "一、 專題系統功能說明")
    
    pdf.set_font("msjh", size=10)
    pdf.set_text_color(74, 85, 104)
    pdf.multi_cell(0, 6, "本專案實作了一套互動式智慧家居自動化系統模擬器，藉由 C++ 的強大物件導向特性建構而成，完美切合了期末專題的五大核心要求：", new_x="LMARGIN", new_y="NEXT")
    pdf.ln(3)

    draw_bullet_point(pdf, "C++ 類別繼承與多型 (Polymorphism)", 
                      "定義了 SmartDevice 設備基底類別，並衍生出 SmartLight (燈光)、SmartThermostat (溫控器) 與 SmartCamera (安全相機) 三個子類別。同樣地，自動化規則基於 AutomationRule 類別，衍生出 TemperatureRule (環境溫度觸發) 與 TimeRule (模擬時間觸發) 規則類別。核心邏輯皆透過虛擬介面（如 turnOn、updateSetting、checkAndTrigger 等）實現多型控制。")
    
    draw_bullet_point(pdf, "讀檔與寫檔功能 (File I/O)", 
                      "支援配置持久化儲存。系統啟動時會自動解析 config.txt 載入先前儲存的智慧設備與自動化規則狀態；使用者亦可在終端機中選擇將目前最新狀態寫入 config.txt 存檔，甚至可將系統事件日誌（Event Logs）導出為標準 CSV 格式檔案，方便後續稽核與分析。")
                      
    draw_bullet_point(pdf, "STL 類別庫之使用", 
                      "中控核心 SmartHome 類別大量運用了標準模板庫（STL）容器，包括以 std::vector<std::unique_ptr<SmartDevice>> 與 std::vector<std::unique_ptr<AutomationRule>> 管理動態生成的智慧設備與自動化規則，保證記憶體安全；並以 std::vector<std::string> 快取事件日誌。此外，還結合了 <algorithm> 庫的 std::remove_if 與 Lambda 表達式來完成設備及規則的動態刪除。")
                      
    draw_bullet_point(pdf, "終端機 UI 模擬介面與防呆驗證", 
                      "提供流暢且資訊豐富的文字介面中控面板，實時顯示模擬時間、環境溫度、動態感測狀況以及各項設備與規則的狀態。使用者可輸入選項進行控制，所有輸入均經過極限與類型防呆驗證（若輸入非數字字元，系統會自動清除錯誤標記並清空緩衝區，提示重新輸入），避免程式崩潰。")

    draw_bullet_point(pdf, "跨平台中文字元相容性", 
                      "針對 Windows 終端機常見的 UTF-8 中文亂碼問題，程式在啟動時會主動調用 Windows API (SetConsoleOutputCP(CP_UTF8) 及 SetConsoleCP(CP_UTF8)) 初始化控制台，確保中文字元完美顯示，大幅提昇終端機 UI 的美觀度與可讀性。")

    # ----------------------------------------------------
    # SECTION 2: 系統架構設計
    # ----------------------------------------------------
    pdf.ln(5)
    draw_section_header(pdf, "二、 系統架構設計與類別關係")
    
    pdf.set_font("msjh", size=10)
    pdf.set_text_color(74, 85, 104)
    pdf.multi_cell(0, 6, "系統採用高凝聚力、低耦合力的物件導向架構設計。中控中心 (SmartHome) 負責集中管理所有設備與自動化規則的生命週期，並維護模擬環境參數（溫度、時間、動態偵測狀態）。", new_x="LMARGIN", new_y="NEXT")
    pdf.ln(3)

    # Text-based architecture diagram
    pdf.set_font("msjh", style="B", size=10)
    pdf.cell(0, 6, "[類別關係架構示意圖]", new_x="LMARGIN", new_y="NEXT")
    pdf.set_font("msjh", size=9)
    pdf.set_text_color(45, 55, 72)
    
    arch_lines = [
        "   +-------------------------------------------------------------+",
        "   |                         SmartHome                           |",
        "   |  - devices: vector<unique_ptr<SmartDevice>>                 |",
        "   |  - rules: vector<unique_ptr<AutomationRule>>                 |",
        "   +------------------------------+------------------------------+",
        "                                  | (組合關係)",
        "         +------------------------+------------------------+",
        "         |                                                 |",
        "  [智慧設備階層]                                    [自動化規則階層]",
        "  +------------------------------+                  +------------------------------+",
        "  |    SmartDevice (抽象基底)     |                  |    AutomationRule (抽象基底)  |",
        "  |  - id, name, isOn, type      |                  |  - id, name, isActive, type  |",
        "  +--------------+---------------+                  +--------------+---------------+",
        "                 |                                                 |",
        "      +----------+----------+                           +----------+----------+",
        "      |          |          |                           |                     |",
        "  SmartLight SmartThermost SmartCamera             TemperatureRule         TimeRule",
        "  (燈光)     (溫控器)      (相機)                  (溫度觸發)              (時間觸發)"
    ]
    
    start_x = pdf.get_x()
    start_y = pdf.get_y()
    pdf.set_fill_color(245, 247, 250)
    pdf.rect(start_x, start_y, 170, len(arch_lines) * 4.5 + 4, style="F")
    pdf.set_x(start_x + 5)
    pdf.set_y(start_y + 2)
    for line in arch_lines:
        pdf.cell(0, 4.5, line, new_x="LMARGIN", new_y="NEXT")
        pdf.set_x(start_x + 5)
    pdf.set_y(start_y + len(arch_lines) * 4.5 + 4)
    pdf.ln(5)

    # ----------------------------------------------------
    # SECTION 3: 開發迭代流程
    # ----------------------------------------------------
    draw_section_header(pdf, "三、 開發與軟體迭代流程 (OpenSpec)")
    pdf.set_font("msjh", size=10)
    pdf.set_text_color(74, 85, 104)
    pdf.multi_cell(0, 6, "專案在開發過程中嚴格遵循現代軟體工程規範，採用 OpenSpec 規格驅動開發流程 (Spec-driven Development)，實現了兩次主要功能迭代：", new_x="LMARGIN", new_y="NEXT")
    pdf.ln(2)
    
    draw_bullet_point(pdf, "第一階段 (v1.0 - 核心架構建立)", "制定了系統基本規格 (spec.md)，規範了 Polymorphic Smart Devices 和 File Storage 邏輯。在此階段完成了設備類別設計、環境模擬與 config.txt 存檔功能的實作。")
    draw_bullet_point(pdf, "第二階段 (v2.0 - 自動化規則引擎與文件生成)", "建立 `generate-flowchart-and-readme` 分支與規格提案。規劃並生成系統類別架構與流程 Mermaid 圖，編寫了專案完整的 README.md 文件。最後透過 `openspec archive` 進行主規格同步與分支封存，保證變更紀錄完整。")

    # ----------------------------------------------------
    # SECTION 4: 程式執行畫面截圖與說明
    # ----------------------------------------------------
    pdf.add_page()
    draw_section_header(pdf, "四、 程式執行檔畫面與說明")
    
    # Screenshot 1
    screen1 = [
        "============================================================",
        "🏠 智慧家居自動化系統中控面板 (Smart Home Panel)",
        "============================================================",
        "🕒 [模擬時間] 12:00  | 🌡️ [環境溫度] 25.0 °C  | 🚨 [動態偵測] 無",
        "------------------------------------------------------------",
        "【 智慧設備狀態列表 】",
        "  [ID: 1] 客廳吸頂燈 -> 燈光狀態: [OFF] | 亮度: 80% | 色溫: 暖色",
        "  [ID: 2] 客廳冷氣機 -> 溫控狀態: [OFF] | 設定溫度: 26.0°C | 模式: 制冷",
        "  [ID: 3] 玄關監視器 -> 相機狀態: [ON] | 錄影: 未錄影 | 動態監測: 已啟用",
        "------------------------------------------------------------",
        "【 自動化規則列表 】",
        "  [ID: 1] 高溫自動開啟冷氣 -> 溫度觸發 (已啟用): 當室溫 > 28.0°C 時，開啟設備 ID 2",
        "  [ID: 2] 深夜自動關閉客廳燈 -> 時間觸發 (已啟用): 當時間到達 23:00 時，關閉設備 ID 1",
        "============================================================",
        "1. 控制智慧設備           2. 模擬環境參數",
        "3. 管理智慧設備 (新增/移除)  4. 管理自動化規則 (新增/啟停)",
        "5. 儲存目前配置           6. 重新載入配置",
        "7. 匯出系統日誌 (CSV)     8. 結束程式",
        "------------------------------------------------------------",
        "請選擇操作選項 (1-8): "
    ]
    draw_terminal_screen(pdf, "畫面一：主控面板儀表板 (Dashboard) 畫面", screen1)
    pdf.set_font("msjh", size=9.5)
    pdf.set_text_color(100, 100, 100)
    pdf.multi_cell(0, 5, "說明：程式啟動時會主動搜尋並解析 config.txt 載入預設之智慧設備（燈光、冷氣、相機）以及自動化規則，並於終端機印出精美的中控面板。頂部清晰顯示當前模擬的時間、環境溫度與動態偵測狀態。", new_x="LMARGIN", new_y="NEXT")
    pdf.ln(5)

    # Screenshot 2
    screen2 = [
        "🌍 環境參數模擬選單",
        "------------------------------------------------------------",
        "1. 模擬調整溫度",
        "2. 模擬調整系統時間 (0-23)",
        "3. 觸發動態感應狀況",
        "4. 返回主選單",
        "請輸入選項 (1-4): 1",
        "請輸入新的模擬室溫 (°C): 29.5",
        "",
        "[自動化事件觸發]：環境溫度由 25.0°C 上升至 29.5°C",
        "自動化規則 [高溫自動開啟冷氣] 觸發: 環境溫度 29.5°C > 門檻 28.0°C，自動開啟「客廳冷氣機」"
    ]
    draw_terminal_screen(pdf, "畫面二：環境參數模擬與自動化規則引擎聯動觸發", screen2)
    pdf.set_font("msjh", size=9.5)
    pdf.set_text_color(100, 100, 100)
    pdf.multi_cell(0, 5, "說明：進入模擬環境參數選單後，將模擬溫度調高至 29.5°C。由於該溫度高於自動化規則「高溫自動開啟冷氣」所設定之 28.0°C 閥值，規則引擎立即動態觸發，自動開啟冷氣機並於系統日誌中記錄此一連動事件，完全符合多型規則檢查邏輯。", new_x="LMARGIN", new_y="NEXT")

    # ----------------------------------------------------
    # SECTION 5: GitHub Repo Link
    # ----------------------------------------------------
    pdf.add_page()
    draw_section_header(pdf, "五、 開源程式碼倉庫 (GitHub Repository)")
    
    pdf.set_font("msjh", size=10)
    pdf.set_text_color(74, 85, 104)
    pdf.multi_cell(0, 6, "本專案之完整程式碼、Git 提交歷史紀錄、開發規格文件、與 Mermaid 系統架構流程圖已全部上傳至 GitHub 開源平台。你可以點擊下方網址查看詳細專案內容：", new_x="LMARGIN", new_y="NEXT")
    pdf.ln(4)
    
    # Center GitHub link with high visibility
    pdf.set_x(30)
    pdf.set_font("msjh", style="B", size=11)
    pdf.set_text_color(26, 54, 93)
    pdf.cell(150, 10, f"GitHub 專案網址: {args.repo}", align="L", new_x="LMARGIN", new_y="NEXT")
    pdf.ln(50)
    
    # Signature
    pdf.set_font("msjh", style="B", size=12)
    pdf.set_text_color(102, 102, 102)
    pdf.cell(0, 6, "報告完成，特此陳報。", align="R", new_x="LMARGIN", new_y="NEXT")
    pdf.cell(0, 6, f"學生：{args.name} ({args.id})", align="R", new_x="LMARGIN", new_y="NEXT")
    
    output_filename = f"{args.id}.pdf"
    pdf.output(output_filename)
    print(f"Report PDF generated successfully: {output_filename}")

if __name__ == "__main__":
    main()
