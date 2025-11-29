import tkinter as tk
from datetime import datetime, timedelta

# 기본 설정
default_life_expectancies = [30, 40, 50, 60, 70, 80, 90, 100]  # 다양한 기대 수명

# 시간 계산 및 업데이트 함수
def update_timer():
    birth_str = birth_entry.get()
    try:
        birth_date = datetime.strptime(birth_str, "%Y-%m-%d %H:%M")
        now = datetime.now()

        for i, entry in enumerate(life_entries):
            try:
                life_expectancy = int(entry.get())
                death_date = birth_date + timedelta(days=life_expectancy * 365.25)
                total_seconds = (death_date - birth_date).total_seconds()
                remaining_seconds = max(0, (death_date - now).total_seconds())

                # 남은 시간 계산
                days = int(remaining_seconds // (24 * 3600))
                hours = int((remaining_seconds % (24 * 3600)) // 3600)
                minutes = int((remaining_seconds % 3600) // 60)
                seconds = int(remaining_seconds % 60)

                # 배터리 잔량 계산
                battery_percentage = (remaining_seconds / total_seconds) * 100

                # UI 업데이트
                timer_labels[i].config(text=f"남은 시간 ({life_expectancy}세 기준): {days}일 {hours}시간 {minutes}분 {seconds}초")
                battery_labels[i].config(text=f"배터리 잔량: {battery_percentage:.2f}%")
            except ValueError:
                timer_labels[i].config(text="올바른 형식의 기대수명을 입력해 주세요.")
                battery_labels[i].config(text="")
    except ValueError:
        for i in range(len(default_life_expectancies)):
            timer_labels[i].config(text="올바른 형식의 생년월일을 입력해 주세요.")
            battery_labels[i].config(text="")

    # 1초마다 업데이트
    window.after(1000, update_timer)

# UI 설정
window = tk.Tk()
window.title("인생 배터리 시계 - 동적 입력 가능")
window.geometry("600x700")

# 생년월일 입력 필드
tk.Label(window, text="생년월일시를 'YYYY-MM-DD HH:MM' 형식으로 입력하세요:", font=("Helvetica", 12)).pack(pady=10)
birth_entry = tk.Entry(window, font=("Helvetica", 12), width=30)
birth_entry.pack(pady=5)
birth_entry.insert(0, "1995-11-05 13:27")  # 기본값

# 기대 수명 입력 필드 및 초기값 설정
life_entries = []
for life_expectancy in default_life_expectancies:
    frame = tk.Frame(window)
    frame.pack(pady=5)
    tk.Label(frame, text=f"{life_expectancy}세 기준 기대 수명:", font=("Helvetica", 12)).pack(side="left")
    entry = tk.Entry(frame, font=("Helvetica", 12), width=5)
    entry.insert(0, str(life_expectancy))
    entry.pack(side="left")
    life_entries.append(entry)

timer_labels = []
battery_labels = []

for i in range(len(default_life_expectancies)):
    timer_label = tk.Label(window, text="", font=("Helvetica", 14))
    timer_label.pack(pady=10)
    timer_labels.append(timer_label)

    battery_label = tk.Label(window, text="", font=("Helvetica", 12))
    battery_label.pack(pady=5)
    battery_labels.append(battery_label)

update_timer()
window.mainloop()
