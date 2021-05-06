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

    LocationModel bakeryModel("bakery_model", "/Users/jacksonchen/Desktop/CS 318 GUI:OOP Application Dev/FuelThePeople_New/csvTest.csv", "Bakery", Qt::red);
    bakeryModel.addToMap(view);

    LocationModel restModel("rest_model", "/Users/jacksonchen/Desktop/CS 318 GUI:OOP Application Dev/FuelThePeople_New/csvTest.csv", "Restaurant", Qt::green);
    restModel.addToMap(view);

    LocationModel expandingRadii("emptyRadii", "/Users/jacksonchen/Desktop/CS 318 GUI:OOP Application Dev/FuelThePeople_New/csvTest.csv", "Restaurant", Qt::green);
    expandingRadii.addToMap(view);

    return app.exec();
}
