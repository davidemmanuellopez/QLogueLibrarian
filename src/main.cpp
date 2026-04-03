#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "controller/AppController.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("QLogueLibrarian"));
    app.setOrganizationName(QStringLiteral("qlogue"));

    qlogue::AppController controller;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("App"), &controller);

    engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
