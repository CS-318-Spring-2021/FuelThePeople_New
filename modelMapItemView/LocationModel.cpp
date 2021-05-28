#include "LocationModel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QGeoCoordinate>
#include <QQmlContext>
#include <QStandardItemModel>
#include "locationrecord.h"
#include "filedownloader.h"
#include <QJsonDocument>
#include <QMapIterator>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>

LocationModel::LocationModel(QString _modelName, QString _filePath, QColor _color) :
    modelName(_modelName), filePath(_filePath), color(_color)
{ }

//populates map with points with attributes according to the model and the enumerated roles
void LocationModel::addToMap(QQuickView &view) {
    //create an array to store each role
    QHash<int, QByteArray> roles;
    roles[CoordinateRole] = QByteArray("coordinate");
    roles[ColorRole] = QByteArray("color");
    roles[NameRole] = QByteArray("name");
    roles[WebsiteRole] = QByteArray("website");
    roles[AmenityRole] = QByteArray("amenity");
    setItemRoleNames(roles);
    view.rootContext()->setContextProperty(modelName, this);

    if(filePath.startsWith("https")){
        importJSon();
    }else{
        importCSV();
    }
}

void LocationModel::importCSV(){
    QString data;
    QFile importedCSV(filePath);
    QStringList rowOfData;
    QStringList rowData;
    double latitude;
    double longitude;
    QString amenityType;
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


    for (int x = 1; x < rowOfData.size(); x++) {
        rowData = rowOfData.at(x).split(",");
        latitude= rowData[0].toDouble();
        longitude= rowData[1].toDouble();
        name = rowData[2];
        orderLink = rowData[8];
        amenityType = rowData[3];

        //uses QStandardItem to assign attributes from the CSV to roles
        QStandardItem *item = new QStandardItem;
        item->setData(QVariant::fromValue(name), NameRole);
        item->setData(QVariant::fromValue(amenityType), AmenityRole);
        item->setData(QVariant::fromValue(orderLink).toUrl(), WebsiteRole);
        item->setData(QVariant::fromValue(QGeoCoordinate(latitude, longitude)), CoordinateRole);
        item->setData(QVariant::fromValue(color), ColorRole);
        appendRow(item);
    }
}


void LocationModel::importJSon(){
    QUrl myUrl= filePath;
    newFile = new FileDownloader(myUrl,this);
    connect(newFile, SIGNAL (downloaded()), this, SLOT (processData()));
}

void LocationModel::processData(){
    QJsonDocument itemDoc = QJsonDocument::fromJson(newFile->downloadedData());
    const QJsonValue &dataSet= itemDoc["data"].toArray();
    int i=0;
    QJsonValue datapoint= dataSet[i];
    QJsonValue information= datapoint["source"];
    QJsonValue locationData= information["data"];

    while(!dataSet[i].isNull()){
        datapoint= dataSet[i];
        information= datapoint["source"];
        locationData= information["data"];
        QStandardItem *item = new QStandardItem;
        item->setData(QVariant::fromValue(QGeoCoordinate(locationData["lat"].toDouble(), locationData["lng"].toDouble())), CoordinateRole);
        item->setData(QVariant::fromValue(color), ColorRole);
        item->setData(locationData["title"], NameRole);
        appendRow(item);

        if (i == 1000){ // break after finding 1000 points
            break;
        }

        ++i;
    }
}
