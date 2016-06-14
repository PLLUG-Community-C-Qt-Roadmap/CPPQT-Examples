#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "detailsloader.h"
#include "detail.h"
#include <QDebug>
#include <QQmlContext>
#include "detailsmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DetailsLoader loader;
    loader.setFileName("D:/PLLUG/Projects/DetailsBrowser/test.json");

    for (auto detail: loader.details())
    {
        qDebug() << detail->type() << detail->model();
    }

    QQmlApplicationEngine engine;


    engine.rootContext()->setContextProperty("myModel", loader.detailsModel());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
