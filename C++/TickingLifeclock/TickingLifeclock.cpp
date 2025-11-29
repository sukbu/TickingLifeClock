#include "LifeClockWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QTimer>
#include <QDateTimeEdit>
#include <QDoubleSpinBox>
#include <QPainter>
#include <QTime>
#include <cmath>

LifeClockWindow::LifeClockWindow(QWidget* parent)
    : QWidget(parent)
{
    // Set up widgets
    birthInput = new QDateTimeEdit(QDateTime::currentDateTime());
    birthInput->setDisplayFormat("yyyy-MM-dd HH:mm");

    lifeExpectancyInput = new QDoubleSpinBox();
    lifeExpectancyInput->setRange(1, 1000);
    lifeExpectancyInput->setValue(80);
    lifeExpectancyInput->setSuffix(" years");

    updateLabel = new QLabel("Time Left:");
    batteryCanvas = new QWidget();
    batteryCanvas->setMinimumSize(300, 30);

    // Layouts
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* inputLayout = new QHBoxLayout();

    inputLayout->addWidget(new QLabel("Birth Time:"));
    inputLayout->addWidget(birthInput);
    inputLayout->addWidget(new QLabel("Life Expectancy:"));
    inputLayout->addWidget(lifeExpectancyInput);

    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(updateLabel);
    mainLayout->addWidget(batteryCanvas);
    setLayout(mainLayout);

    // Timer for updates
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LifeClockWindow::updateClock);
    connect(birthInput, &QDateTimeEdit::dateTimeChanged, this, &LifeClockWindow::updateClock);
    connect(lifeExpectancyInput, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &LifeClockWindow::updateClock);
    timer->start(1000);

    updateClock();
}

void LifeClockWindow::updateClock()
{
    QDateTime birth = birthInput->dateTime();
    QDateTime now = QDateTime::currentDateTime();
    double expectancyYears = lifeExpectancyInput->value();

    QDateTime expectedDeath = birth.addSecs(static_cast<qint64>(expectancyYears * 365.25 * 24 * 60 * 60));

    qint64 total = birth.secsTo(expectedDeath);
    qint64 remaining = now.secsTo(expectedDeath);

    if (remaining < 0) remaining = 0;

    int days = remaining / (24 * 3600);
    int hours = (remaining % (24 * 3600)) / 3600;
    int minutes = (remaining % 3600) / 60;
    int seconds = remaining % 60;

    double percent = (double)remaining / total * 100.0;

    updateLabel->setText(
        QString("Time Left: %1 days %2 hours %3 minutes %4 seconds\nBattery: %5%")
        .arg(days).arg(hours).arg(minutes).arg(seconds).arg(QString::number(percent, 'f', 2))
    );

    batteryCanvas->update();
}

void LifeClockWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(batteryCanvas);
    QRect rect = batteryCanvas->rect();
    double expectancyYears = lifeExpectancyInput->value();
    QDateTime birth = birthInput->dateTime();
    QDateTime now = QDateTime::currentDateTime();
    QDateTime expectedDeath = birth.addSecs(static_cast<qint64>(expectancyYears * 365.25 * 24 * 60 * 60));
    qint64 total = birth.secsTo(expectedDeath);
    qint64 remaining = now.secsTo(expectedDeath);
    if (remaining < 0) remaining = 0;
    double percent = (double)remaining / total;

    painter.setBrush(Qt::gray);
    painter.drawRect(rect);
    painter.setBrush(Qt::green);
    painter.drawRect(rect.x(), rect.y(), rect.width() * percent, rect.height());
}
