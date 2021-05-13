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

//make a constructor
//add to view

LocationModel::LocationModel(QString _modelName, QString _filePath, QString _amenityType, QColor _color) :
    modelName(_modelName), filePath(_filePath), amenityType(_amenityType), color(_color)
{ }



void LocationModel::addToMap(QQuickView &view) {

    //create an array to store each role
    QHash<int, QByteArray> roles;
    roles[CoordinateRole] = QByteArray("coordinate");
    roles[ColorRole] = QByteArray("color");
    roles[NameRole] = QByteArray("name");
    roles[WebsiteRole] = QByteArray("website");
    setItemRoleNames(roles);

    view.rootContext()->setContextProperty(modelName, this);

    if(filePath.startsWith("https")){
        importJSon();
    }else{
        importCSV();
    }
}

void LocationModel::importCSV(){
#if 1

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
        qDebug()<<rowData[3]<<amenityType;
        //filter by amenity type
        if (rowData[3] == amenityType) {
            latitude= rowData[0].toDouble();
            longitude= rowData[1].toDouble();
            name = rowData[2];
            orderLink = rowData[8];

            //uses QStandardItem to assign attributes from the CSV to roles
            QStandardItem *item = new QStandardItem;
            item->setData(QVariant::fromValue(name), NameRole);
            item->setData(QVariant::fromValue(orderLink), WebsiteRole);
            item->setData(QVariant::fromValue(QGeoCoordinate(latitude, longitude)), CoordinateRole);
            item->setData(QVariant::fromValue(color), ColorRole);
            appendRow(item);
        }

    }
#endif

}


void LocationModel::importJSon(){
    QUrl myUrl= filePath;
    if(myUrl.hasQuery()){
        myUrl.setQuery("New York City");
    }
    newFile = new FileDownloader(myUrl,this);
    connect(newFile, SIGNAL (downloaded()), this, SLOT (processData()));


}

void LocationModel::processData(){
    QJsonDocument itemDoc = QJsonDocument::fromJson(newFile->downloadedData());
    QJsonArray latArr =itemDoc["Latitude"].toArray();
    QJsonArray lngArr =itemDoc["Longitude"].toArray();
    QJsonArray titleArr =itemDoc["title"].toArray();
    QJsonArray addressArr =itemDoc["address"].toArray();
    QJsonArray contactArr =itemDoc["contact"].toArray();

    for(int x=0;x<titleArr.size(); x++){
        LocationRecord record("Latitude",latArr[x].toVariant());
        record.addVal("Longitude",latArr[x].toVariant());
        record.addVal("title",titleArr[x].toVariant());
        record.addVal("address",addressArr[x].toVariant());
        record.addVal("contact",contactArr[x].toVariant());

        QStandardItem *item = new QStandardItem;
        item->setData(QVariant::fromValue(QGeoCoordinate(latArr[x].toDouble(), lngArr[x].toDouble())), CoordinateRole);
        item->setData(QVariant::fromValue(color), ColorRole);
        appendRow(item);

        records.insert(records.end(),record);
    }

    }






//std::list<LocationRecord> LocationModel:: getLocationRecordList(){
//    return records;
//}

//void LocationModel:: appendLocationRecordList(QVariant data){


//}

//LocationRecord LocationModel:: getLocationRecord(QString id){
//    return records.at(id) ;
//}

