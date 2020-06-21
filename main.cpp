#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "boardmodel.h"
#include "NetetrisModel.h"
#include "NextFigureModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<BoardModel>("com.NikolayStepanov.BoardModel", 1, 0, "BoardModel");
    qmlRegisterType<NetetrisModel>("com.NikolayStepanov.NetetrisModel", 1, 0, "NetetrisModel");
    qmlRegisterType<NextFigureModel>("com.NikolayStepanov.NextFigureModel", 1, 0, "NextFigureModel");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
