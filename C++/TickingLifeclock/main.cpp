#include <QApplication>
#include <QIcon>
#include "LifeClockWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    // Set application icon
    QIcon appIcon;
    // Try loading from Qt resource first
    appIcon = QIcon(":/icon.ico");
    if (appIcon.isNull()) {
        // Fallback: try loading from file system
        appIcon = QIcon("icon.ico");
    }
    if (!appIcon.isNull()) {
        app.setWindowIcon(appIcon);
    }
    
    LifeClockWindow window;
    window.setWindowTitle("Ticking Lifeclock");
    window.setWindowIcon(appIcon);  // Also set for the window
    window.resize(600, 750);  // 적절한 초기 크기 (너비 x 높이)
    window.show();
    return app.exec();
}
