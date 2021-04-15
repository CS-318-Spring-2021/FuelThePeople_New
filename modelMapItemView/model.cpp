//#include "model.h"
//#include <QGuiApplication>
//#include <QQmlApplicationEngine>
//#include <QQuickView>
//#include <QGeoCoordinate>
//#include <QQmlContext>
//#include <QStandardItemModel>

//model::model()
//{

//}

//int model::Coordinates() {
//    int CoordinateRole = Qt::UserRole + 1000;
//    return CoordinateRole;
//}

//void model::createModel(const QString modelName) {
//    QQuickView view;
//    QStandardItemModel itemModel;
//    QHash<int, QByteArray> roles;
//    roles[Coordinates()] = QByteArray("coordinate");
//    itemModel.setItemRoleNames(roles);
//    view.rootContext()->setContextProperty(modelName, &itemModel);
//    view.setSource(QUrl("qrc:/main.qml"));
//    view.resize(1000, 650);
//    view.show();

//}

//void model::readCSV(const QString filePath, const QStandardItemModel itemModel) {
//    QString data;
//    QFile importedCSV(filePath);
//    QStringList rowOfData;
//    QStringList rowData;
//    double latitude;
//    double longitude;
//    data.clear();
//    rowOfData.clear();
//    rowData.clear();

//    if (importedCSV.open(QFile::ReadOnly))
//    {
//        data = importedCSV.readAll();
//        rowOfData = data.split("\n");
//        importedCSV.close();
//    }

//    for (int x = 1; x < rowOfData.size(); x++)
//    {
//        rowData = rowOfData.at(x).split(",");

//        latitude= rowData[0].toDouble();
//        longitude= rowData[1].toDouble();
//        QStandardItem *item = new QStandardItem;
//        item->setData(QVariant::fromValue(QGeoCoordinate(latitude, longitude)), model::Coordinates());
//        //itemModel.appendRow(item);

//        }

//}

