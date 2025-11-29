# 다국어 지원 및 마우스 휠 줌 인/아웃 기능을 포함한 최종 통합 코드
# 클래스 기반 구조로 재구성
import tkinter as tk
from tkinter import ttk
from datetime import datetime, timedelta, MAXYEAR
import math


class LifeBatteryClock:
    """인생 배터리 시계 메인 클래스"""
    
    def __init__(self):
        # 다국어 지원
        self.languages = {
            "한국어": {
                "title": "인생 배터리 시계 - 다국어 지원",
                "birth_label": "생년월일시를 'YYYY-MM-DD HH:MM' 형식으로 입력하세요:",
                "life_label_prefix": "기대 수명",
                "life_label_suffix": "세 기준:",
                "time_left": "남은 시간 ({0}세 기준): {1}일 {2}시간 {3}분 {4}초",
                "battery_left": "배터리 잔량: {0:.2f}%",
                "invalid_date": "올바른 형식의 생년월일을 입력해 주세요.",
                "invalid_life": "올바른 형식의 기대수명을 입력해 주세요.",
                "now_time": "현재 시간: {}",
                "language_label": "언어"
            },
            "English": {
                "title": "Life Battery Clock - Multilingual Support",
                "birth_label": "Enter your birth date and time in 'YYYY-MM-DD HH:MM' format:",
                "life_label_prefix": "Life expectancy at",
                "life_label_suffix": "years:",
                "time_left": "Time left ({0} years): {1} days {2} hours {3} minutes {4} seconds",
                "battery_left": "Battery level: {0:.2f}%",
                "invalid_date": "Please enter a valid date format.",
                "invalid_life": "Please enter a valid life expectancy.",
                "now_time": "Current time: {}",
                "language_label": "Language"
            },
            "Deutsch": {
                "title": "Lebensbatterie-Uhr - Mehrsprachige Unterstützung",
                "birth_label": "Geben Sie Ihr Geburtsdatum und Ihre Zeit im Format 'YYYY-MM-DD HH:MM' ein:",
                "life_label_prefix": "Lebenserwartung bei",
                "life_label_suffix": "Jahren:",
                "time_left": "Verbleibende Zeit ({} Jahre): {} Tage {} Stunden {} Minuten {} Sekunden",
                "battery_left": "Batteriestand: {:.2f}%",
                "invalid_date": "Bitte geben Sie ein gültiges Datumsformat ein.",
                "invalid_life": "Bitte geben Sie eine gültige Lebenserwartung ein.",
                "now_time": "Aktuelle Zeit: {}",
                "language_label": "Sprache"
            },
            "日本語": {
                "title": "人生バッテリー時計 - 多言語対応",
                "birth_label": "'YYYY-MM-DD HH:MM' 形式で生年月日を入力してください:",
                "life_label_prefix": "寿命",
                "life_label_suffix": "歳:",
                "time_left": "残り時間 ({}歳基準): {}日 {}時間 {}分 {}秒",
                "battery_left": "バッテリー残量: {:.2f}%",
                "invalid_date": "有効な日付形式を入力してください。",
                "invalid_life": "有効な寿命を入力してください。",
                "now_time": "現在時刻: {}",
                "language_label": "言語"
            },
            "简体中文": {
                "title": "人生电池时钟 - 多语言支持",
                "birth_label": "请输入出生日期和时间 (格式: 'YYYY-MM-DD HH:MM'):",
                "life_label_prefix": "预期寿命",
                "life_label_suffix": "岁:",
                "time_left": "剩余时间 ({}岁标准): {}天 {}小时 {}分 {}秒",
                "battery_left": "电池剩余: {:.2f}%",
                "invalid_date": "请输入有效的日期格式。",
                "invalid_life": "请输入有效的预期寿命。",
                "now_time": "当前时间: {}",
                "language_label": "语言"
            },
            "繁體中文": {
                "title": "人生電池時鐘 - 多語言支持",
                "birth_label": "請輸入出生日期和時間 (格式: 'YYYY-MM-DD HH:MM'):",
                "life_label_prefix": "預期壽命",
                "life_label_suffix": "歲:",
                "time_left": "剩餘時間 ({}歲標準): {}天 {}小時 {}分 {}秒",
                "battery_left": "電池剩餘: {:.2f}%",
                "invalid_date": "請輸入有效的日期格式。",
                "invalid_life": "請輸入有效的預期壽命。",
                "now_time": "當前時間: {}",
                "language_label": "語言"
            },
            "Русский": {
                "title": "Часы Жизни - Многоязычная поддержка",
                "birth_label": "Введите дату рождения в формате 'YYYY-MM-DD HH:MM':",
                "life_label_prefix": "Ожидаемая продолжительность жизни",
                "life_label_suffix": "лет:",
                "time_left": "Оставшееся время ({} лет): {} дней {} часов {} минут {} секунд",
                "battery_left": "Уровень заряда: {:.2f}%",
                "invalid_date": "Пожалуйста, введите корректную дату.",
                "invalid_life": "Пожалуйста, введите корректную продолжительность жизни.",
                "now_time": "Текущее время: {}",
                "language_label": "Язык"
            },
            "Français": {
                "title": "Horloge de Vie - Support multilingue",
                "birth_label": "Entrez votre date et heure de naissance au format 'YYYY-MM-DD HH:MM':",
                "life_label_prefix": "Espérance de vie à",
                "life_label_suffix": "ans:",
                "time_left": "Temps restant ({} ans): {} jours {} heures {} minutes {} secondes",
                "battery_left": "Niveau de batterie: {:.2f}%",
                "invalid_date": "Veuillez entrer un format de date valide.",
                "invalid_life": "Veuillez entrer une espérance de vie valide.",
                "now_time": "Heure actuelle: {}",
                "language_label": "Langue"
            },
            "Italiano": {
                "title": "Orologio della Vita - Supporto multilingue",
                "birth_label": "Inserisci la tua data e ora di nascita nel formato 'YYYY-MM-DD HH:MM':",
                "life_label_prefix": "Aspettativa di vita a",
                "life_label_suffix": "anni:",
                "time_left": "Tempo rimanente ({} anni): {} giorni {} ore {} minuti {} secondi",
                "battery_left": "Livello batteria: {:.2f}%",
                "invalid_date": "Inserisci un formato data valido.",
                "invalid_life": "Inserisci un'aspettativa di vita valida.",
                "now_time": "Ora attuale: {}",
                "language_label": "Lingua"
            },
            "Português": {
                "title": "Relógio da Vida - Suporte multilíngue",
                "birth_label": "Digite sua data e hora de nascimento no formato 'YYYY-MM-DD HH:MM':",
                "life_label_prefix": "Expectativa de vida aos",
                "life_label_suffix": "anos:",
                "time_left": "Tempo restante ({} anos): {} dias {} horas {} minutos {} segundos",
                "battery_left": "Nível da bateria: {:.2f}%",
                "invalid_date": "Digite um formato de data válido.",
                "invalid_life": "Digite uma expectativa de vida válida.",
                "now_time": "Hora atual: {}",
                "language_label": "Idioma"
            },
            "Español": {
                "title": "Reloj de Vida - Soporte multilingüe",
                "birth_label": "Ingrese su fecha y hora de nacimiento en formato 'YYYY-MM-DD HH:MM':",
                "life_label_prefix": "Expectativa de vida a",
                "life_label_suffix": "años:",
                "time_left": "Tiempo restante ({} años): {} días {} horas {} minutos {} segundos",
                "battery_left": "Nivel de batería: {:.2f}%",
                "invalid_date": "Ingrese un formato de fecha válido.",
                "invalid_life": "Ingrese una expectativa de vida válida.",
                "now_time": "Hora actual: {}",
                "language_label": "Idioma"
            },
            "Українська": {
                "title": "Годинник Життя - Багатомовна підтримка",
                "birth_label": "Введіть дату та час народження у форматі 'YYYY-MM-DD HH:MM':",
                "life_label_prefix": "Очікувана тривалість життя",
                "life_label_suffix": "років:",
                "time_left": "Залишилося часу ({} років): {} днів {} годин {} хвилин {} секунд",
                "battery_left": "Рівень заряду: {:.2f}%",
                "invalid_date": "Будь ласка, введіть коректну дату.",
                "invalid_life": "Будь ласка, введіть коректну тривалість життя.",
                "now_time": "Поточний час: {}",
                "language_label": "Мова"
            },
            "Nederlands": {
                "title": "Levensbatterij Klok - Meertalige ondersteuning",
                "birth_label": "Voer uw geboortedatum en tijd in het formaat 'YYYY-MM-DD HH:MM' in:",
                "life_label_prefix": "Levensverwachting op",
                "life_label_suffix": "jaar:",
                "time_left": "Resterende tijd ({} jaar): {} dagen {} uren {} minuten {} seconden",
                "battery_left": "Batterijniveau: {:.2f}%",
                "invalid_date": "Voer een geldig datumformaat in.",
                "invalid_life": "Voer een geldige levensverwachting in.",
                "now_time": "Huidige tijd: {}",
                "language_label": "Taal"
            }
        }
        
        # 기본 설정
        self.default_life_expectancies = [30, 40, 50, 60, 70, 80, 90, 1000]
        self.current_language = "한국어"
        self.font_size = 12
        
        # UI 초기화
        self.window = tk.Tk()
        self.window.title(self.languages[self.current_language]["title"])
        self.window.geometry("600x750")  # 적절한 초기 크기 (너비 x 높이)
        self.window.bind("<MouseWheel>", self.zoom)
        self.window.bind("<Control-MouseWheel>", self.zoom_font)  # Ctrl+Wheel로 폰트 크기 조정
        self.font_scale = 1.0  # 폰트 스케일
        
        # UI 컴포넌트
        self.language_label = None
        self.language_combo = None
        self.now_label = None
        self.birth_label = None
        self.birth_year = None
        self.birth_month = None
        self.birth_day = None
        self.birth_time = None
        self.life_entries = []
        self.life_label_prefixes = []
        self.life_label_suffixes = []
        self.timer_labels = []
        self.battery_labels = []  # 배터리 퍼센트 텍스트용
        self.clock_canvases = []  # 시계 그리드 Canvas
        self.suggestion_labels = []
        
        self._create_ui()
        self.update_labels()
        self.update_timer()
    
    def _create_ui(self):
        """UI 컴포넌트 생성"""
        # 언어 선택 라벨
        self.language_label = tk.Label(
            self.window, 
            text=self.languages[self.current_language]["language_label"], 
            font=("Helvetica", self.font_size)
        )
        self.language_label.pack(pady=5)
        
        # 언어 드롭다운 (wider to show all languages)
        self.language_combo = ttk.Combobox(
            self.window, 
            values=list(self.languages.keys()), 
            state="readonly",
            width=20
        )
        self.language_combo.set(self.current_language)
        self.language_combo.pack(pady=5)
        self.language_combo.bind("<<ComboboxSelected>>", self.change_language)
        
        # 계산 시점 표시 라벨
        self.now_label = tk.Label(
            self.window, 
            text="", 
            font=("Helvetica", self.font_size)
        )
        self.now_label.pack(pady=5)
        
        # 생년월일 (separate fields)
        self.birth_label = tk.Label(
            self.window, 
            text=self.languages[self.current_language]["birth_label"], 
            font=("Helvetica", self.font_size)
        )
        self.birth_label.pack(pady=10)
        
        # Birth date input frame
        birth_frame = tk.Frame(self.window)
        birth_frame.pack(pady=5)
        
        # Year
        tk.Label(birth_frame, text="Year:", font=("Helvetica", self.font_size)).pack(side="left", padx=2)
        self.birth_year = tk.Entry(birth_frame, font=("Helvetica", self.font_size), width=6)
        self.birth_year.pack(side="left", padx=2)
        self.birth_year.insert(0, "1995")
        
        # Month
        tk.Label(birth_frame, text="Month:", font=("Helvetica", self.font_size)).pack(side="left", padx=2)
        self.birth_month = tk.Entry(birth_frame, font=("Helvetica", self.font_size), width=4)
        self.birth_month.pack(side="left", padx=2)
        self.birth_month.insert(0, "11")
        
        # Day
        tk.Label(birth_frame, text="Day:", font=("Helvetica", self.font_size)).pack(side="left", padx=2)
        self.birth_day = tk.Entry(birth_frame, font=("Helvetica", self.font_size), width=4)
        self.birth_day.pack(side="left", padx=2)
        self.birth_day.insert(0, "05")
        
        # Time
        tk.Label(birth_frame, text="Time (HH:MM):", font=("Helvetica", self.font_size)).pack(side="left", padx=2)
        self.birth_time = tk.Entry(birth_frame, font=("Helvetica", self.font_size), width=8)
        self.birth_time.pack(side="left", padx=2)
        self.birth_time.insert(0, "00:00")
        
        # 기대 수명 필드
        for life_expectancy in self.default_life_expectancies:
            frame = tk.Frame(self.window)
            frame.pack(pady=5)
            life_label_prefix = tk.Label(
                frame, 
                text="", 
                font=("Helvetica", self.font_size)
            )
            life_label_prefix.pack(side="left")
            self.life_label_prefixes.append(life_label_prefix)
            
            entry = tk.Entry(frame, font=("Helvetica", self.font_size), width=5)
            entry.insert(0, str(life_expectancy))
            entry.pack(side="left")
            self.life_entries.append(entry)
            
            life_label_suffix = tk.Label(
                frame, 
                text="", 
                font=("Helvetica", self.font_size)
            )
            life_label_suffix.pack(side="left")
            self.life_label_suffixes.append(life_label_suffix)
        
        # 출력 필드
        for _ in range(len(self.default_life_expectancies)):
            timer_label = tk.Label(
                self.window, 
                text="", 
                font=("Helvetica", self.font_size)
            )
            timer_label.pack(pady=10)
            self.timer_labels.append(timer_label)
            
            # 시계 그리드 Canvas
            clock_canvas = tk.Canvas(
                self.window,
                width=320,
                height=50,
                bg="white",
                highlightthickness=1,
                highlightbackground="#ccc"
            )
            clock_canvas.pack(pady=5)
            self.clock_canvases.append(clock_canvas)
            
            # 배터리 퍼센트 텍스트 라벨
            battery_label = tk.Label(
                self.window, 
                text="", 
                font=("Helvetica", self.font_size)
            )
            battery_label.pack(pady=2)
            self.battery_labels.append(battery_label)
            
            suggestion_label = tk.Label(
                self.window,
                text="",
                font=("Helvetica", self.font_size - 1),
                fg="#666666",
                wraplength=550
            )
            suggestion_label.pack(pady=2)
            self.suggestion_labels.append(suggestion_label)
    
    def draw_clock_grid(self, canvas, percentage, clock_count=8, columns=8):
        """시계 그리드를 Canvas에 그리기 (물이 차는 효과)"""
        canvas.delete("all")  # 기존 그림 삭제
        
        percentage = max(0.0, min(100.0, percentage))
        # 전체 시계 개수에 대한 비율 계산 (소수점 포함)
        filled_clocks = (percentage / 100.0) * clock_count
        if percentage > 0.0 and filled_clocks < 0.01:
            filled_clocks = 0.01  # 최소 0.01 표시
        
        rows = math.ceil(clock_count / columns)
        width = canvas.winfo_width() or 350
        height = canvas.winfo_height() or 60
        
        # 시계 크기 계산 (위쪽이 잘리지 않도록 충분한 여백 확보)
        clock_size = min(width // columns, height // rows) - 6  # 6px 여백 (위아래)
        clock_size = max(30, clock_size)  # 최소 30px (시계 디테일을 위해)
        
        # 중앙 정렬을 위한 오프셋 (위쪽이 잘리지 않도록 여백 확보)
        spacing = 4
        total_width = columns * (clock_size + spacing)
        total_height = rows * (clock_size + spacing)
        offset_x = (width - total_width) // 2
        offset_y = max(3, (height - total_height) // 2)  # 최소 3px 위쪽 여백
        
        clock_index = 0
        for row in range(rows):
            for col in range(columns):
                if clock_index >= clock_count:
                    break
                
                x = offset_x + col * (clock_size + 4)
                y = offset_y + row * (clock_size + 4)
                
                center_x = x + clock_size // 2
                center_y = y + clock_size // 2
                radius = clock_size // 2
                
                # 배경 원 (흰색) - 먼저 그리기
                canvas.create_oval(
                    x, y, x + clock_size, y + clock_size,
                    outline="", fill="white"
                )
                
                # 채워진 비율 계산 (0.0 ~ 1.0)
                clock_fill = 0.0
                if clock_index < int(filled_clocks):
                    # 완전히 채워진 시계
                    clock_fill = 1.0
                elif clock_index < int(filled_clocks) + 1:
                    # 부분적으로 채워진 시계
                    clock_fill = filled_clocks - int(filled_clocks)
                
                # 물이 차는 효과: 아래에서 위로 채워지는 원형 물
                if clock_fill > 0.0:
                    # 물의 높이 계산 (아래에서 위로)
                    water_height = clock_fill  # 0.0 ~ 1.0
                    
                    # 물의 색상 (초록빛 물 효과) - PowerPoint asset과 유사하게
                    water_color = "#90EE90"  # lightgreen
                    water_highlight = "#ADFFAD"  # 더 밝은 초록색
                    
                    # 물의 높이에 따라 그리기
                    water_top = y + clock_size - int(clock_size * water_height)
                    water_bottom = y + clock_size - 2  # 2px 여백
                    
                    # 원형 영역 내에서만 물을 그리기
                    if water_height > 0.0:
                        # 원형 경계를 정확하게 계산하여 물 영역 그리기
                        # 원의 하단부(6시, 270도)에서 시작하여 물의 높이만큼 채우기
                        # tkinter의 create_arc는 각도를 사용: start=0은 3시, extent는 시계방향
                        
                        # 물의 높이에 따른 각도 계산
                        # 하단(270도)에서 시작하여 시계방향으로 물의 높이만큼
                        # start=270 (하단), extent는 양수(시계방향) 또는 음수(반시계방향)
                        # 물이 아래에서 위로 차므로, 하단에서 시작하여 반시계방향으로 올라감
                        arc_start = 90  # 12시 방향 (tkinter는 3시가 0도이므로 12시는 90도)
                        arc_extent = 180 * water_height  # 물의 높이에 비례한 각도
                        
                        # 원형 영역 내에서만 물을 채우기 (원호 사용)
                        # 하단에서 시작하여 위로 올라가는 원호
                        canvas.create_arc(
                            x + 2, y + 2, x + clock_size - 2, y + clock_size - 2,
                            start=arc_start - arc_extent,  # 하단에서 시작
                            extent=arc_extent,  # 물의 높이만큼
                            outline="", fill=water_color, style=tk.PIESLICE
                        )
                        
                        # 그라데이션 효과를 위해 위쪽에 밝은 색상 추가
                        if water_height > 0.1:
                            gradient_height = water_height * 0.3  # 위쪽 30%
                            gradient_extent = 180 * gradient_height
                            canvas.create_arc(
                                x + 2, y + 2, x + clock_size - 2, y + clock_size - 2,
                                start=arc_start - gradient_extent,
                                extent=gradient_extent,
                                outline="", fill=water_highlight, style=tk.PIESLICE
                            )
                        
                        # 물 표면에 하이라이트 추가 (물결 효과)
                        if water_height > 0.05:
                            surface_y = water_top
                            # 약간의 곡선으로 물결 표현
                            points = []
                            for i in range(2, clock_size - 2, 2):
                                # 원형 경계 내에 있는지 확인
                                dx = i - radius
                                dy = surface_y - center_y
                                if dx * dx + dy * dy <= (radius - 2) * (radius - 2):
                                    wave = 1.5 * math.sin(i * 0.4)
                                    points.extend([x + i, surface_y + int(wave)])
                            if len(points) >= 4:
                                canvas.create_line(
                                    points, fill=water_highlight, width=1.5, smooth=True
                                )
                
                # 시계 외곽선 (원형) - 마지막에 그리기
                canvas.create_oval(
                    x, y, x + clock_size, y + clock_size,
                    outline="black", width=2, fill=""
                )
                
                # 시계 내부 점 (12시, 3시, 6시, 9시 위치) - PowerPoint asset처럼
                dot_size = max(2, clock_size // 20)
                dot_radius = radius - dot_size - 4
                
                # 12시 위치
                canvas.create_oval(
                    center_x - dot_size//2, y + dot_size + 2,
                    center_x + dot_size//2, y + dot_size + 2 + dot_size,
                    fill="black", outline="black"
                )
                # 3시 위치
                canvas.create_oval(
                    center_x + dot_radius - dot_size//2, center_y - dot_size//2,
                    center_x + dot_radius + dot_size//2, center_y + dot_size//2,
                    fill="black", outline="black"
                )
                # 6시 위치
                canvas.create_oval(
                    center_x - dot_size//2, y + clock_size - dot_size - 2,
                    center_x + dot_size//2, y + clock_size - 2,
                    fill="black", outline="black"
                )
                # 9시 위치
                canvas.create_oval(
                    center_x - dot_radius - dot_size//2, center_y - dot_size//2,
                    center_x - dot_radius + dot_size//2, center_y + dot_size//2,
                    fill="black", outline="black"
                )
                
                # 시계 바늘 (3시간 간격으로 배치: 0, 3, 6, 9, 12, 15, 18, 21시)
                hour = (clock_index % 8) * 3  # 0, 3, 6, 9, 12, 15, 18, 21
                hour_angle = math.radians(hour * 30.0 - 90.0)  # -90도부터 시작 (12시가 위)
                hand_length = radius - dot_size - 6
                hand_end_x = center_x + int(hand_length * math.cos(hour_angle))
                hand_end_y = center_y + int(hand_length * math.sin(hour_angle))
                
                line_width = max(2, clock_size // 18)
                canvas.create_line(
                    center_x, center_y, hand_end_x, hand_end_y,
                    width=line_width, fill="black"
                )
                
                clock_index += 1
    
    def generate_battery_bar(self, percentage, bar_length=20):
        """배터리 바 시각화 생성 (사용 안 함, draw_clock_grid 사용)"""
        # Use rounding instead of truncation, and ensure at least 1 box if percentage > 0
        filled = int((percentage / 100.0) * bar_length + 0.5)  # Round to nearest
        if percentage > 0.0 and filled == 0:
            filled = 1  # Show at least 1 box if any percentage
        filled = max(0, min(filled, bar_length))
        bar = "["
        for i in range(bar_length):
            if i < filled:
                bar += "■"
            else:
                bar += "□"
        bar += "]"
        return bar
    
    def generate_suggestions(self, days):
        """활동 제안 생성"""
        if days <= 0:
            return ""
        
        suggestions = []
        
        # Books (assuming 6 hours per book, 8 hours reading per day = 0.75 books/day)
        books = int(days * 0.75)
        if books > 0:
            suggestions.append(f"~{books} books")
        
        # Movies (assuming 2 hours per movie)
        movies = int(days * 4)  # 4 movies per day if watching 8 hours
        if movies > 0 and movies < 10000:
            suggestions.append(f"~{movies} movies")
        
        # Travel (assuming 7 days per trip)
        trips = int(days / 7)
        if trips > 0 and trips < 1000:
            suggestions.append(f"~{trips} week-long trips")
        
        # Languages (assuming 6 months = 180 days per language)
        languages = int(days / 180)
        if languages > 0 and languages < 50:
            suggestions.append(f"~{languages} new languages")
        
        # Skills (assuming 3 months = 90 days per skill)
        skills = int(days / 90)
        if skills > 0 and skills < 100:
            suggestions.append(f"~{skills} new skills")
        
        if not suggestions:
            return ""
        return "With this time, you could: " + ", ".join(suggestions)
    
    def change_language(self, event):
        """언어 변경"""
        self.current_language = self.language_combo.get()
        self.update_labels()
    
    def update_labels(self):
        """라벨 업데이트"""
        lang = self.languages[self.current_language]
        self.window.title(lang["title"])
        self.birth_label.config(text=lang["birth_label"])
        now_str = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        self.now_label.config(text=lang["now_time"].format(now_str))
        self.language_label.config(text=lang["language_label"])
        for i in range(len(self.life_entries)):
            self.life_label_prefixes[i].config(text=lang["life_label_prefix"])
            self.life_label_suffixes[i].config(text=lang["life_label_suffix"])
    
    def update_timer(self):
        """타이머 업데이트"""
        lang = self.languages[self.current_language]
        
        # Get birth date from separate fields
        try:
            year = self.birth_year.get().strip()
            month = self.birth_month.get().strip()
            day = self.birth_day.get().strip()
            time_str = self.birth_time.get().strip()
            
            # Default time to 00:00 if empty
            if not time_str:
                time_str = "00:00"
            
            # Combine into datetime string
            birth_str = f"{year}-{month.zfill(2)}-{day.zfill(2)} {time_str}"
            birth_date = datetime.strptime(birth_str, "%Y-%m-%d %H:%M")
            now = datetime.now()
            latest_allowed = datetime(MAXYEAR, 12, 31, 23, 59, 59)
            
            # 계산 시점 라벨 갱신
            self.now_label.config(
                text=lang["now_time"].format(now.strftime("%Y-%m-%d %H:%M:%S"))
            )
            
            for i, entry in enumerate(self.life_entries):
                try:
                    life_expectancy = int(entry.get())
                    estimated_death = birth_date + timedelta(days=life_expectancy * 365.25)
                    death_date = min(estimated_death, latest_allowed)
                    
                    total_seconds = (death_date - birth_date).total_seconds()
                    remaining_seconds = max(0, (death_date - now).total_seconds())
                    
                    days = int(remaining_seconds // (24 * 3600))
                    hours = int((remaining_seconds % (24 * 3600)) // 3600)
                    minutes = int((remaining_seconds % 3600) // 60)
                    seconds = int(remaining_seconds % 60)
                    
                    battery_percentage = (remaining_seconds / total_seconds) * 100
                    
                    # 시계 그리드 업데이트 (10개 시계, 일렬)
                    self.draw_clock_grid(self.clock_canvases[i], battery_percentage, clock_count=8, columns=8)
                    
                    self.timer_labels[i].config(
                        text=lang["time_left"].format(
                            life_expectancy, days, hours, minutes, seconds
                        )
                    )
                    self.battery_labels[i].config(
                        text=lang['battery_left'].format(battery_percentage)
                    )
                    self.suggestion_labels[i].config(
                        text=self.generate_suggestions(days)
                    )
                except (ValueError, OverflowError):
                    self.timer_labels[i].config(text=lang["invalid_life"])
                    self.clock_canvases[i].delete("all")
                    self.battery_labels[i].config(text="")
                    self.suggestion_labels[i].config(text="")
        except ValueError:
            for i in range(len(self.default_life_expectancies)):
                self.timer_labels[i].config(text=lang["invalid_date"])
                self.clock_canvases[i].delete("all")
                self.battery_labels[i].config(text="")
                self.suggestion_labels[i].config(text="")
        
        # 1초마다 업데이트
        self.window.after(1000, self.update_timer)
    
    def zoom(self, event):
        """마우스 휠 줌 인/아웃 (기존 기능 유지)"""
        self.font_size = min(max(self.font_size + (1 if event.delta > 0 else -1), 8), 20)
        self.apply_font_size()
    
    def zoom_font(self, event):
        """Ctrl+Wheel로 폰트 크기 조정"""
        delta = event.delta / 120.0  # 일반적으로 120 = 1단계
        self.font_scale += delta * 0.1
        self.font_scale = max(0.5, min(3.0, self.font_scale))  # 0.5배 ~ 3배 사이로 제한
        self.apply_font_size()
    
    def apply_font_size(self):
        """폰트 크기 적용"""
        scaled_size = int(self.font_size * self.font_scale)
        scaled_size = max(6, min(60, scaled_size))  # 최소 6, 최대 60
        
        small_size = max(5, int(scaled_size * 0.9))
        
        self.birth_label.config(font=("Helvetica", scaled_size))
        self.birth_year.config(font=("Helvetica", small_size))
        self.birth_month.config(font=("Helvetica", small_size))
        self.birth_day.config(font=("Helvetica", small_size))
        self.birth_time.config(font=("Helvetica", small_size))
        self.now_label.config(font=("Helvetica", scaled_size))
        self.language_label.config(font=("Helvetica", scaled_size))
        
        for label in self.life_label_prefixes + self.life_label_suffixes + self.timer_labels + self.battery_labels:
            label.config(font=("Helvetica", scaled_size))
        for label in self.suggestion_labels:
            label.config(font=("Helvetica", small_size))
    
    def run(self):
        """애플리케이션 실행"""
        self.window.mainloop()


if __name__ == "__main__":
    app = LifeBatteryClock()
    app.run()
