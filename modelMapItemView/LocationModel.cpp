#include "LocationModel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QGeoCoordinate>
#include <QQmlContext>
#include <QStandardItemModel>

//make a constructor
//add to view

LocationModel::LocationModel(QString _modelName, QString _filePath, QString _amenityType, QColor _color) :
    modelName(_modelName), filePath(_filePath), amenityType(_amenityType), color(_color)
{ }
void LocationModel::addToMap(QQuickView &view) {

    QHash<int, QByteArray> roles;
    roles[CoordinateRole] = QByteArray("coordinate");
    roles[ColorRole] = QByteArray("color");
    roles[NameRole] = QByteArray("name");
    roles[WebsiteRole] = QByteArray("website");
    setItemRoleNames(roles);


    view.rootContext()->setContextProperty(modelName, this);
    QString data;
    QFile importedCSV(filePath);
    QStringList rowOfData;
    QStringList rowData;
    double latitude;
    double longitude;
    QString name;
    QString orderLink;
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
        qDebug()<<rowData[3]<<amenityType;//save as tab deliminited and then split by tab
        if (rowData[3] == amenityType) {
            latitude= rowData[0].toDouble();
            longitude= rowData[1].toDouble();
            name = rowData[2];
            orderLink = rowData[8];
            QStandardItem *item = new QStandardItem;
            item->setData(QVariant::fromValue(name), NameRole);
            item->setData(QVariant::fromValue(orderLink), WebsiteRole);
            item->setData(QVariant::fromValue(QGeoCoordinate(latitude, longitude)), CoordinateRole);
            item->setData(QVariant::fromValue(color), ColorRole);
            appendRow(item);
        }


    }
}
