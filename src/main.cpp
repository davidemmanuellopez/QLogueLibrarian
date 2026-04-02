#include <QApplication>
#include "view/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("QLogueLibrarian"));
    app.setOrganizationName(QStringLiteral("qlogue"));

    qlogue::MainWindow w;
    w.show();
    return app.exec();
}
