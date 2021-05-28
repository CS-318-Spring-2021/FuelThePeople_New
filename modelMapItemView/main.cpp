#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QGeoCoordinate>
#include <QQmlContext>
#include <QStandardItemModel>
#include "LocationModel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQuickView view;
    view.setSource(QUrl("qrc:/main.qml"));
    view.resize(1000, 650);
    view.show();

    char csvFilePath[] = "/Users/jacksonchen/Desktop/CS 318 GUI:OOP Application Dev/FuelThePeople_New/csvTest.csv";

    //creates points for bakeries
    LocationModel bakeryModel("bakery_model", csvFilePath, Qt::red);
    bakeryModel.addToMap(view);

    //creates points for restaurants
    LocationModel restModel("rest_model", csvFilePath, Qt::green);
    restModel.addToMap(view);

    //creates empty points to visualize access
    LocationModel expandingRadii("emptyRadii", csvFilePath, Qt::green);
    expandingRadii.addToMap(view);

    return app.exec();
}
