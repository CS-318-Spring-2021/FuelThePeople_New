#include "locationModel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QGeoCoordinate>
#include <QQmlContext>
#include <QStandardItemModel>

//make a constructor
//add to view

locationModel::locationModel(QString _modelName, QString _filePath, QString _amenityType) :
    modelName(_modelName), filePath(_filePath), amenityType(_amenityType)
{ }
void locationModel::addToMap(QQuickView &view) {
    int CoordinateRole = Qt::UserRole + 1000;

    QHash<int, QByteArray> roles;
    roles[CoordinateRole] = QByteArray("coordinate");
    setItemRoleNames(roles);
    view.rootContext()->setContextProperty(modelName, this);

    QString data;
    QFile importedCSV(filePath);
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
        if (rowOfData[6] == amenityType) {


            rowData = rowOfData.at(x).split(",");

            latitude= rowData[0].toDouble();
            longitude= rowData[1].toDouble();
            QStandardItem *item = new QStandardItem;
            item->setData(QVariant::fromValue(QGeoCoordinate(latitude, longitude)), CoordinateRole);
            appendRow(item);
        }

    }

}

//int mapModel::Coordinates() {
//    int CoordinateRole = Qt::UserRole + 1000;
//    return CoordinateRole;
//}

//void mapModel::createModel(const QString modelName) {
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

//void mapModel::readCSV(const QString filePath, QStandardItemModel itemModel, const QString amenityType) {
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
//        if (rowOfData[6] == amenityType) {


//            rowData = rowOfData.at(x).split(",");

//            latitude= rowData[0].toDouble();
//            longitude= rowData[1].toDouble();
//            QStandardItem *item = new QStandardItem;
//            item->setData(QVariant::fromValue(QGeoCoordinate(latitude, longitude)), mapModel::Coordinates());
//            itemModel.appendRow(item);
//        }

//    }

//}

