// LifeClockWindow.h
#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QList>
#include <QMap>
#include <QString>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QScrollArea>
#include <QFont>

// 시계 그리드를 그리는 커스텀 위젯
class ClockGridWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClockGridWidget(QWidget* parent = nullptr);
    void setPercentage(double percentage);  // 0.0 ~ 100.0
    void setClockCount(int count) { clockCount = count; update(); }  // 시계 개수 설정
    void setColumns(int cols) { columns = cols; update(); }  // 열 개수 설정

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    double percentage;  // 0.0 ~ 100.0
    int clockCount;     // 전체 시계 개수
    int columns;        // 열 개수
    double filledClocks;   // 채워진 시계 개수 (소수점 포함)
};

struct LifeRow {
    QLabel* lifeLabelPrefix;  // "Life expectancy at"
    QLineEdit* ageInput;
    QLabel* lifeLabelSuffix;   // "years:"
    QLabel* resultLabel;
    ClockGridWidget* clockGridWidget;  // 시계 그리드 위젯 (batteryLabel 대체)
    QLabel* batteryLabel;  // 배터리 퍼센트 표시용 (텍스트만)
    QLabel* suggestionLabel;  // Activity suggestions
};

class LifeClockWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LifeClockWindow(QWidget* parent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override;

private slots:
    void onLanguageChanged(const QString& lang);
    void updateLabels();
    void updateClock();

private:
    void applyFontScale();  // 폰트 스케일 적용

private:
    QScrollArea* scrollArea;
    QWidget* scrollContent;
    QComboBox* langComboBox;
    QLabel* langLabel;
    QLabel* currentTimeLabel;
    QLabel* birthLabel;
    QLineEdit* birthYear;
    QLineEdit* birthMonth;
    QLineEdit* birthDay;
    QLineEdit* birthTime;
    QList<LifeRow> lifeLayout;
    QMap<QString, QMap<QString, QString>> translations;
    QString currentLang;
    int baseFontSize;  // 기본 폰트 크기
    double fontScale;  // 폰트 스케일 (Ctrl+Wheel로 조정)
};