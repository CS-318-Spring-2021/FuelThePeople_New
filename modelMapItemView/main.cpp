#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QGeoCoordinate>
#include <QQmlContext>
#include <QStandardItemModel>

int CoordinateRole = Qt::UserRole + 1000;

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQuickView view;
        QStandardItemModel model;
        QHash<int, QByteArray> roles;
        roles[CoordinateRole] = QByteArray("coordinate");
        model.setItemRoleNames(roles);
        view.rootContext()->setContextProperty("circle_model", &model);
        view.setSource(QUrl("qrc:/main.qml"));
        view.resize(1000, 650);
        view.show();
        QString data;
        QFile importedCSV("/users/simonmscharf/Downloads/csvTest 2.csv");
        QStringList rowOfData;
        QStringList rowData;
        double latitude;
        double longitude;
        data.clear();
        rowOfData.clear();
        rowData.clear();

        if (importedCSV.open(QFile::ReadOnly))
        {
            data = importedCSV.readAll();
            rowOfData = data.split("\n");
            importedCSV.close();
        }

        for (int x = 1; x < rowOfData.size(); x++)
        {
            rowData = rowOfData.at(x).split(",");

            latitude= rowData[0].toDouble();
            longitude= rowData[1].toDouble();
            QStandardItem *item = new QStandardItem;
            item->setData(QVariant::fromValue(QGeoCoordinate(latitude, longitude)), CoordinateRole);
            model.appendRow(item);

            }

//        QStandardItem *item = new QStandardItem;
//        item->setData(QVariant::fromValue(QGeoCoordinate(40.66062, -73.95043)), CoordinateRole);
//        model.appendRow(item);

//        QStandardItem *item1 = new QStandardItem;
//        item1->setData(QVariant::fromValue(QGeoCoordinate(40.65207, -73.94954)), CoordinateRole);
//        model.appendRow(item1);

//        QStandardItem *item2 = new QStandardItem;
//        item2->setData(QVariant::fromValue(QGeoCoordinate(40.80438, -73.9558)), CoordinateRole);
//        model.appendRow(item2);

        return app.exec();

    return app.exec();
}
