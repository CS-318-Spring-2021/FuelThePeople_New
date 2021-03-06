#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QGeoCoordinate>
#include <QQmlContext>
#include <QStandardItemModel>
#include <QDir>
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

    // Please build this project in .../FuelThePeople_New/modelMapItemView/ if the application is not reading it in.
    char csvFilePath[] = ":/csvTest.csv";
    char apiLink[] = "https://api.reach4help.org/edge/map/data";

    //creates points for bakeries
    LocationModel bakeryModel("bakery_model", csvFilePath, Qt::red);
    bakeryModel.addToMap(view);

    //creates points for restaurants
    LocationModel restModel("rest_model", csvFilePath, Qt::darkGreen);
    restModel.addToMap(view);

    //creates points for JSON locations
    LocationModel allPoint_model("allPoint_model", apiLink, Qt::cyan);
    allPoint_model.addToMap(view);

    //creates empty points to visualize access
     LocationModel expandingRadii("emptyRadii", csvFilePath, Qt::green);
     expandingRadii.addToMap(view);

    return app.exec();
}
