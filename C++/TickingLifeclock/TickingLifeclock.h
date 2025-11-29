#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TickingLifeclock.h"

class TickingLifeclock : public QMainWindow
{
    Q_OBJECT

public:
    TickingLifeclock(QWidget *parent = nullptr);
    ~TickingLifeclock();

private:
    Ui::TickingLifeclockClass ui;
};
