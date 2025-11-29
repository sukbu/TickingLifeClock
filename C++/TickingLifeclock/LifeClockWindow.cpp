// LifeClockWindow.cpp
#include "LifeClockWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QStringList>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QFont>
#include <QLinearGradient>
#include <QPainterPath>
#include <cmath>

// ClockGridWidget 구현
ClockGridWidget::ClockGridWidget(QWidget* parent)
    : QWidget(parent), percentage(0.0), clockCount(8), columns(8), filledClocks(0.0)
{
    setMinimumSize(320, 50);
    setMaximumHeight(60);
}

void ClockGridWidget::setPercentage(double pct) {
    percentage = qBound(0.0, pct, 100.0);
    // 전체 시계 개수에 대한 비율 계산 (소수점 포함)
    filledClocks = (percentage / 100.0) * clockCount;
    if (percentage > 0.0 && filledClocks < 0.01) filledClocks = 0.01;  // 최소 0.01 표시
    update();
}

void ClockGridWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    int rows = (clockCount + columns - 1) / columns;  // 올림 계산
    int width = this->width();
    int height = this->height();
    
    // 시계 크기 계산 (여백 고려) - 위쪽이 잘리지 않도록 충분한 여백 확보
    int clockSize = qMin(width / columns, height / rows) - 6;  // 6px 여백 (위아래)
    clockSize = qMax(30, clockSize);  // 최소 30px (시계 디테일을 위해)
    
    // 중앙 정렬을 위한 오프셋 계산 (위쪽이 잘리지 않도록 여백 확보)
    int spacing = 4;
    int totalWidth = columns * (clockSize + spacing);
    int totalHeight = rows * (clockSize + spacing);
    int offsetX = (width - totalWidth) / 2;
    int offsetY = qMax(3, (height - totalHeight) / 2);  // 최소 3px 위쪽 여백
    
    int clockIndex = 0;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            if (clockIndex >= clockCount) break;
            
            int x = offsetX + col * (clockSize + 4);
            int y = offsetY + row * (clockSize + 4);
            
            // 시계 원 그리기
            QRect clockRect(x, y, clockSize, clockSize);
            
            int centerX = x + clockSize / 2;
            int centerY = y + clockSize / 2;
            int radius = clockSize / 2;
            
            // 배경 (흰색) - 먼저 그리기
            painter.setBrush(QBrush(Qt::white));
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(clockRect);
            
            // 채워진 비율 계산 (0.0 ~ 1.0)
            double clockFill = 0.0;
            if (clockIndex < static_cast<int>(filledClocks)) {
                // 완전히 채워진 시계
                clockFill = 1.0;
            } else if (clockIndex < static_cast<int>(filledClocks) + 1) {
                // 부분적으로 채워진 시계
                clockFill = filledClocks - static_cast<int>(filledClocks);
            }
            
            // 물이 차는 효과: 아래에서 위로 채워지는 원형 물
            if (clockFill > 0.0) {
                // 원형 클리핑 영역 설정 (물이 원형 안에만 그려지도록)
                QPainterPath clipPath;
                clipPath.addEllipse(clockRect);
                painter.setClipPath(clipPath);
                
                // 물의 높이 계산 (아래에서 위로)
                double waterHeight = clockFill;  // 0.0 ~ 1.0
                
                // 물의 색상 (초록빛 물 효과) - PowerPoint asset과 유사하게
                QColor waterColor(144, 238, 144);  // 연한 초록색 (lightgreen)
                QColor waterHighlight(173, 255, 173);  // 더 밝은 초록색
                
                // 물의 높이에 따라 그리기
                int waterTop = y + clockSize - static_cast<int>(clockSize * waterHeight);
                
                // 물의 그라데이션 효과
                QLinearGradient waterGradient(centerX, waterTop, centerX, y + clockSize);
                waterGradient.setColorAt(0.0, waterHighlight);  // 위쪽은 밝게
                waterGradient.setColorAt(1.0, waterColor);      // 아래쪽은 진하게
                
                painter.setBrush(QBrush(waterGradient));
                painter.setPen(Qt::NoPen);
                
                // 물이 차는 영역 그리기 (원형 클리핑 적용됨)
                QRect waterRect(x, waterTop, clockSize, static_cast<int>(clockSize * waterHeight));
                painter.drawRect(waterRect);
                
                // 물의 표면에 하이라이트 추가 (물결 효과)
                if (waterHeight > 0.05) {
                    painter.setPen(QPen(waterHighlight, 1.5));
                    painter.setBrush(Qt::NoBrush);
                    int surfaceY = waterTop;
                    // 약간의 곡선으로 물결 표현
                    QPainterPath surfacePath;
                    surfacePath.moveTo(x + 2, surfaceY);
                    for (int i = 2; i < clockSize - 2; i += 2) {
                        double wave = 1.5 * sin(i * 0.4);
                        surfacePath.lineTo(x + i, surfaceY + static_cast<int>(wave));
                    }
                    surfacePath.lineTo(x + clockSize - 2, surfaceY);
                    painter.drawPath(surfacePath);
                }
                
                // 클리핑 해제
                painter.setClipping(false);
            }
            
            // 시계 외곽선 (원형) - 마지막에 그리기
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(QColor(0, 0, 0), 2));
            painter.drawEllipse(clockRect);
            
            // 시계 내부 점 (12시, 3시, 6시, 9시 위치) - PowerPoint asset처럼
            int dotSize = qMax(2, clockSize / 20);
            int dotRadius = radius - dotSize - 4;
            
            painter.setBrush(QBrush(QColor(0, 0, 0)));
            painter.setPen(Qt::NoPen);
            
            // 12시 위치
            painter.drawEllipse(centerX - dotSize/2, y + dotSize + 2, dotSize, dotSize);
            // 3시 위치
            painter.drawEllipse(centerX + dotRadius - dotSize/2, centerY - dotSize/2, dotSize, dotSize);
            // 6시 위치
            painter.drawEllipse(centerX - dotSize/2, y + clockSize - dotSize - 2, dotSize, dotSize);
            // 9시 위치
            painter.drawEllipse(centerX - dotRadius - dotSize/2, centerY - dotSize/2, dotSize, dotSize);
            
            // 시계 바늘 (3시간 간격으로 배치: 0, 3, 6, 9, 12, 15, 18, 21시)
            int hour = (clockIndex % 8) * 3;  // 0, 3, 6, 9, 12, 15, 18, 21
            double hourAngle = (hour * 30.0 - 90.0) * M_PI / 180.0;  // -90도부터 시작 (12시가 위)
            int handLength = radius - dotSize - 6;
            int handEndX = centerX + static_cast<int>(handLength * cos(hourAngle));
            int handEndY = centerY + static_cast<int>(handLength * sin(hourAngle));
            
            painter.setPen(QPen(QColor(0, 0, 0), qMax(2, clockSize / 18)));
            painter.drawLine(centerX, centerY, handEndX, handEndY);
            
            clockIndex++;
        }
    }
}

LifeClockWindow::LifeClockWindow(QWidget* parent)
    : QWidget(parent)
{
    // Initialize translations
    translations["Deutsch"] = {
        {"title", "Lebensbatterie-Uhr - Mehrsprachige Unterstützung"},
        {"birth_label", "Geben Sie Ihr Geburtsdatum und Ihre Zeit im Format 'YYYY-MM-DD HH:MM' ein:"},
        {"life_label_prefix", "Lebenserwartung bei"},
        {"life_label_suffix", "Jahren:"},
        {"time_left", "Verbleibende Zeit (%1 Jahre): %2 Tage %3 Stunden %4 Minuten %5 Sekunden"},
        {"battery_left", "Batteriestand: %1%"},
        {"now_time", "Aktuelle Zeit: %1"},
        {"language_label", "Sprache"}
    };
    translations["English"] = {
        {"title", "Life Battery Clock - Multilingual Support"},
        {"birth_label", "Enter your birth date and time in 'YYYY-MM-DD HH:MM' format:"},
        {"life_label_prefix", "Life expectancy at"},
        {"life_label_suffix", "years:"},
        {"time_left", "Time left (%1 years): %2 days %3 hours %4 minutes %5 seconds"},
        {"battery_left", "Battery level: %1%"},
        {"now_time", "Current time: %1"},
        {"language_label", "Language"}
    };
    translations["한국어"] = {
        {"title", "인생 배터리 시계 - 다국어 지원"},
        {"birth_label", "생년월일시를 'YYYY-MM-DD HH:MM' 형식으로 입력하세요:"},
        {"life_label_prefix", "기대 수명"},
        {"life_label_suffix", "세 기준:"},
        {"time_left", "남은 시간 (%1세 기준): %2일 %3시간 %4분 %5초"},
        {"battery_left", "배터리 잔량: %1%"},
        {"now_time", "현재 시간: %1"},
        {"language_label", "언어"}
    };
    translations["日本語"] = {
        {"title", "人生バッテリー時計 - 多言語対応"},
        {"birth_label", "'YYYY-MM-DD HH:MM' 形式で生年月日を入力してください:"},
        {"life_label_prefix", "寿命"},
        {"life_label_suffix", "歳:"},
        {"time_left", "残り時間 (%1歳基準): %2日 %3時間 %4分 %5秒"},
        {"battery_left", "バッテリー残量: %1%"},
        {"now_time", "現在時刻: %1"},
        {"language_label", "言語"}
    };
    translations["简体中文"] = {
        {"title", "人生电池时钟 - 多语言支持"},
        {"birth_label", "请输入出生日期和时间 (格式: 'YYYY-MM-DD HH:MM'):"},
        {"life_label_prefix", "预期寿命"},
        {"life_label_suffix", "岁:"},
        {"time_left", "剩余时间 (%1岁标准): %2天 %3小时 %4分 %5秒"},
        {"battery_left", "电池剩余: %1%"},
        {"now_time", "当前时间: %1"},
        {"language_label", "语言"}
    };
    translations["繁體中文"] = {
        {"title", "人生電池時鐘 - 多語言支持"},
        {"birth_label", "請輸入出生日期和時間 (格式: 'YYYY-MM-DD HH:MM'):"},
        {"life_label_prefix", "預期壽命"},
        {"life_label_suffix", "歲:"},
        {"time_left", "剩餘時間 (%1歲標準): %2天 %3小時 %4分 %5秒"},
        {"battery_left", "電池剩餘: %1%"},
        {"now_time", "當前時間: %1"},
        {"language_label", "語言"}
    };
    translations["Русский"] = {
        {"title", "Часы Жизни - Многоязычная поддержка"},
        {"birth_label", "Введите дату рождения в формате 'YYYY-MM-DD HH:MM':"},
        {"life_label_prefix", "Ожидаемая продолжительность жизни"},
        {"life_label_suffix", "лет:"},
        {"time_left", "Оставшееся время (%1 лет): %2 дней %3 часов %4 минут %5 секунд"},
        {"battery_left", "Уровень заряда: %1%"},
        {"now_time", "Текущее время: %1"},
        {"language_label", "Язык"}
    };
    translations["Français"] = {
        {"title", "Horloge de Vie - Support multilingue"},
        {"birth_label", "Entrez votre date et heure de naissance au format 'YYYY-MM-DD HH:MM':"},
        {"life_label_prefix", "Espérance de vie à"},
        {"life_label_suffix", "ans:"},
        {"time_left", "Temps restant (%1 ans): %2 jours %3 heures %4 minutes %5 secondes"},
        {"battery_left", "Niveau de batterie: %1%"},
        {"now_time", "Heure actuelle: %1"},
        {"language_label", "Langue"}
    };
    translations["Italiano"] = {
        {"title", "Orologio della Vita - Supporto multilingue"},
        {"birth_label", "Inserisci la tua data e ora di nascita nel formato 'YYYY-MM-DD HH:MM':"},
        {"life_label_prefix", "Aspettativa di vita a"},
        {"life_label_suffix", "anni:"},
        {"time_left", "Tempo rimanente (%1 anni): %2 giorni %3 ore %4 minuti %5 secondi"},
        {"battery_left", "Livello batteria: %1%"},
        {"now_time", "Ora attuale: %1"},
        {"language_label", "Lingua"}
    };
    translations["Português"] = {
        {"title", "Relógio da Vida - Suporte multilíngue"},
        {"birth_label", "Digite sua data e hora de nascimento no formato 'YYYY-MM-DD HH:MM':"},
        {"life_label_prefix", "Expectativa de vida aos"},
        {"life_label_suffix", "anos:"},
        {"time_left", "Tempo restante (%1 anos): %2 dias %3 horas %4 minutos %5 segundos"},
        {"battery_left", "Nível da bateria: %1%"},
        {"now_time", "Hora atual: %1"},
        {"language_label", "Idioma"}
    };
    translations["Español"] = {
        {"title", "Reloj de Vida - Soporte multilingüe"},
        {"birth_label", "Ingrese su fecha y hora de nacimiento en formato 'YYYY-MM-DD HH:MM':"},
        {"life_label_prefix", "Expectativa de vida a"},
        {"life_label_suffix", "años:"},
        {"time_left", "Tiempo restante (%1 años): %2 días %3 horas %4 minutos %5 segundos"},
        {"battery_left", "Nivel de batería: %1%"},
        {"now_time", "Hora actual: %1"},
        {"language_label", "Idioma"}
    };
    translations["Українська"] = {
        {"title", "Годинник Життя - Багатомовна підтримка"},
        {"birth_label", "Введіть дату та час народження у форматі 'YYYY-MM-DD HH:MM':"},
        {"life_label_prefix", "Очікувана тривалість життя"},
        {"life_label_suffix", "років:"},
        {"time_left", "Залишилося часу (%1 років): %2 днів %3 годин %4 хвилин %5 секунд"},
        {"battery_left", "Рівень заряду: %1%"},
        {"now_time", "Поточний час: %1"},
        {"language_label", "Мова"}
    };
    translations["Nederlands"] = {
        {"title", "Levensbatterij Klok - Meertalige ondersteuning"},
        {"birth_label", "Voer uw geboortedatum en tijd in het formaat 'YYYY-MM-DD HH:MM' in:"},
        {"life_label_prefix", "Levensverwachting op"},
        {"life_label_suffix", "jaar:"},
        {"time_left", "Resterende tijd (%1 jaar): %2 dagen %3 uren %4 minuten %5 seconden"},
        {"battery_left", "Batterijniveau: %1%"},
        {"now_time", "Huidige tijd: %1"},
        {"language_label", "Taal"}
    };
    // Set default language
    currentLang = "한국어";
    baseFontSize = 9;
    fontScale = 1.0;

    // ScrollArea setup for proper resizing
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    
    scrollContent = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(scrollContent);
    scrollArea->setWidget(scrollContent);
    
    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scrollArea);

    // Language selector
    QHBoxLayout* langLayout = new QHBoxLayout();
    langLabel = new QLabel(scrollContent);
    langComboBox = new QComboBox(scrollContent);
    langComboBox->addItems(translations.keys());
    langComboBox->setCurrentText(currentLang);
    langComboBox->setMinimumWidth(200);  // Make wider to show all languages
    langLayout->addWidget(langLabel);
    langLayout->addWidget(langComboBox);
    mainLayout->addLayout(langLayout);

    // Current time display
    currentTimeLabel = new QLabel(scrollContent);
    mainLayout->addWidget(currentTimeLabel);

    // Birthdate input (separate fields)
    birthLabel = new QLabel(scrollContent);
    mainLayout->addWidget(birthLabel);
    
    QHBoxLayout* birthLayout = new QHBoxLayout();
    
    QLabel* yearLabel = new QLabel("Year:", scrollContent);
    birthYear = new QLineEdit(scrollContent);
    birthYear->setText("1995");
    birthYear->setMaximumWidth(60);
    
    QLabel* monthLabel = new QLabel("Month:", scrollContent);
    birthMonth = new QLineEdit(scrollContent);
    birthMonth->setText("11");
    birthMonth->setMaximumWidth(50);
    
    QLabel* dayLabel = new QLabel("Day:", scrollContent);
    birthDay = new QLineEdit(scrollContent);
    birthDay->setText("05");
    birthDay->setMaximumWidth(50);
    
    QLabel* timeLabel = new QLabel("Time (HH:MM):", scrollContent);
    birthTime = new QLineEdit(scrollContent);
    birthTime->setText("00:00");
    birthTime->setMaximumWidth(70);
    
    birthLayout->addWidget(yearLabel);
    birthLayout->addWidget(birthYear);
    birthLayout->addWidget(monthLabel);
    birthLayout->addWidget(birthMonth);
    birthLayout->addWidget(dayLabel);
    birthLayout->addWidget(birthDay);
    birthLayout->addWidget(timeLabel);
    birthLayout->addWidget(birthTime);
    birthLayout->addStretch();
    
    mainLayout->addLayout(birthLayout);

    // Life expectancy rows
    QList<int> defaultAges = { 30, 40, 50, 60, 70, 80, 90, 1000 };
    for (int age : defaultAges) {
        QLabel* lLabelPrefix = new QLabel(scrollContent);
        QLineEdit* aInput = new QLineEdit(QString::number(age), scrollContent);
        aInput->setMaximumWidth(60);  // Limit input field width
        aInput->setMinimumWidth(50);
        QLabel* lLabelSuffix = new QLabel(scrollContent);
        QLabel* resLabel = new QLabel(scrollContent);
        ClockGridWidget* clockGrid = new ClockGridWidget(scrollContent);
        clockGrid->setClockCount(8);  // 8개의 시계
        clockGrid->setColumns(8);      // 일렬로 배치
        QLabel* batLabel = new QLabel(scrollContent);  // 배터리 퍼센트 텍스트만 표시
        QLabel* sugLabel = new QLabel(scrollContent);
        sugLabel->setWordWrap(true);
        sugLabel->setStyleSheet("color: #666; font-style: italic;");

        LifeRow row{ lLabelPrefix, aInput, lLabelSuffix, resLabel, clockGrid, batLabel, sugLabel };
        lifeLayout.append(row);

        QHBoxLayout* rowLayout = new QHBoxLayout();
        rowLayout->addWidget(lLabelPrefix);
        rowLayout->addWidget(aInput);
        rowLayout->addWidget(lLabelSuffix);
        mainLayout->addLayout(rowLayout);
        mainLayout->addWidget(resLabel);
        mainLayout->addWidget(clockGrid);  // 시계 그리드 추가
        mainLayout->addWidget(batLabel);
        mainLayout->addWidget(sugLabel);
    }

    // Connections
    connect(langComboBox, &QComboBox::currentTextChanged,
        this, &LifeClockWindow::onLanguageChanged);
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LifeClockWindow::updateClock);
    timer->start(1000);

    // Initial update
    onLanguageChanged(currentLang);
    updateClock();
    applyFontScale();
}

void LifeClockWindow::wheelEvent(QWheelEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) {
        // Ctrl + Wheel로 폰트 크기 조정
        double delta = event->angleDelta().y() / 120.0;  // 일반적으로 120 = 1단계
        fontScale += delta * 0.1;
        fontScale = qBound(0.5, fontScale, 3.0);  // 0.5배 ~ 3배 사이로 제한
        applyFontScale();
        event->accept();
    } else {
        QWidget::wheelEvent(event);
    }
}

void LifeClockWindow::applyFontScale() {
    QFont baseFont;
    baseFont.setPointSize(baseFontSize);
    
    // 모든 위젯에 폰트 스케일 적용
    QFont scaledFont = baseFont;
    scaledFont.setPointSizeF(baseFontSize * fontScale);
    
    langLabel->setFont(scaledFont);
    currentTimeLabel->setFont(scaledFont);
    birthLabel->setFont(scaledFont);
    
    QFont smallFont = scaledFont;
    smallFont.setPointSizeF(baseFontSize * fontScale * 0.9);
    
    birthYear->setFont(smallFont);
    birthMonth->setFont(smallFont);
    birthDay->setFont(smallFont);
    birthTime->setFont(smallFont);
    
    for (const auto& entry : lifeLayout) {
        entry.lifeLabelPrefix->setFont(scaledFont);
        entry.ageInput->setFont(smallFont);
        entry.lifeLabelSuffix->setFont(scaledFont);
        entry.resultLabel->setFont(scaledFont);
        entry.batteryLabel->setFont(scaledFont);
        entry.suggestionLabel->setFont(smallFont);
    }
}

void LifeClockWindow::onLanguageChanged(const QString& lang) {
    currentLang = lang;
    updateLabels();
    updateClock();
}

void LifeClockWindow::updateLabels() {
    const auto& tr = translations[currentLang];
    this->setWindowTitle(tr["title"]);
    langLabel->setText(tr["language_label"] + ":");
    birthLabel->setText(tr["birth_label"]);
    langComboBox->setToolTip(tr["language_label"]);

    for (int i = 0; i < lifeLayout.size(); ++i) {
        lifeLayout[i].lifeLabelPrefix->setText(tr["life_label_prefix"]);
        lifeLayout[i].lifeLabelSuffix->setText(tr["life_label_suffix"]);
    }
}

static QString generateBatteryBar(double percentage, int barLength = 20) {
    // Use rounding instead of truncation, and ensure at least 1 box if percentage > 0
    int filled = static_cast<int>((percentage / 100.0) * barLength + 0.5);  // Round to nearest
    if (percentage > 0.0 && filled == 0) filled = 1;  // Show at least 1 box if any percentage
    if (filled < 0) filled = 0;
    if (filled > barLength) filled = barLength;
    QString bar = "[";
    for (int i = 0; i < barLength; ++i) {
        if (i < filled) {
            bar += "■";
        } else {
            bar += "□";
        }
    }
    bar += "]";
    return bar;
}

static QString generateSuggestions(qint64 days, const QMap<QString, QString>& tr) {
    if (days <= 0) return "";
    
    QStringList suggestions;
    
    // Books (assuming 6 hours per book, 8 hours reading per day = 0.75 books/day)
    int books = static_cast<int>(days * 0.75);
    if (books > 0) {
        suggestions << QString("~%1 books").arg(books);
    }
    
    // Movies (assuming 2 hours per movie)
    int movies = static_cast<int>(days * 4);  // 4 movies per day if watching 8 hours
    if (movies > 0 && movies < 10000) {
        suggestions << QString("~%1 movies").arg(movies);
    }
    
    // Travel (assuming 7 days per trip)
    int trips = static_cast<int>(days / 7);
    if (trips > 0 && trips < 1000) {
        suggestions << QString("~%1 week-long trips").arg(trips);
    }
    
    // Languages (assuming 6 months = 180 days per language)
    int languages = static_cast<int>(days / 180);
    if (languages > 0 && languages < 50) {
        suggestions << QString("~%1 new languages").arg(languages);
    }
    
    // Skills (assuming 3 months = 90 days per skill)
    int skills = static_cast<int>(days / 90);
    if (skills > 0 && skills < 100) {
        suggestions << QString("~%1 new skills").arg(skills);
    }
    
    if (suggestions.isEmpty()) return "";
    return "With this time, you could: " + suggestions.join(", ");
}

void LifeClockWindow::updateClock() {
    const auto& tr = translations[currentLang];
    currentTimeLabel->setText(tr["now_time"].arg(
        QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")));

    QDateTime now = QDateTime::currentDateTime();
    
    // Get birth date from separate fields
    QString year = birthYear->text().trimmed();
    QString month = birthMonth->text().trimmed();
    QString day = birthDay->text().trimmed();
    QString timeStr = birthTime->text().trimmed();
    
    // Default time to 00:00 if empty
    if (timeStr.isEmpty()) {
        timeStr = "13:27";
    }
    
    // Combine into datetime string
    QString birthStr = QString("%1-%2-%3 %4")
        .arg(year)
        .arg(month.rightJustified(2, '0'))
        .arg(day.rightJustified(2, '0'))
        .arg(timeStr);
    
    QDateTime birth = QDateTime::fromString(birthStr, "yyyy-MM-dd HH:mm");
    if (!birth.isValid()) return;

    for (const auto& entry : lifeLayout) {
        int age = entry.ageInput->text().toInt();
        // Use same calculation as Python: days = age * 365.25
        qint64 totalDays = static_cast<qint64>(age * 365.25);
        QDateTime death = birth.addDays(totalDays);
        // Clamp to maximum allowed date (QDate maximum year is 7999)
        QDateTime maxDate = QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59));
        if (death > maxDate) death = maxDate;
        
        qint64 secsTotal = birth.secsTo(death);
        qint64 secsLeft = now.secsTo(death);
        if (secsLeft < 0) secsLeft = 0;

        qint64 days = secsLeft / 86400;
        qint64 hours = (secsLeft % 86400) / 3600;
        qint64 mins = (secsLeft % 3600) / 60;
        qint64 secs = secsLeft % 60;

        double battery = static_cast<double>(secsLeft) / secsTotal * 100.0;
        // 시계 그리드 업데이트
        entry.clockGridWidget->setPercentage(battery);
        // 배터리 퍼센트 텍스트만 표시
        entry.resultLabel->setText(tr["time_left"].arg(age)
            .arg(days).arg(hours).arg(mins).arg(secs));
        entry.batteryLabel->setText(tr["battery_left"].arg(QString::number(battery, 'f', 2)));
        entry.suggestionLabel->setText(generateSuggestions(days, tr));
    }
}
