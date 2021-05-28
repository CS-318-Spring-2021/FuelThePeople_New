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
        qDebug()<<"API Made It \n";
        importJSon();
    }else{
        qDebug()<<"CSV Made It \n";
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


    for (int x = 1; x < rowOfData.size(); x++)
    {
        rowData = rowOfData.at(x).split(",");
        //filter by amenity type
        //        if (rowData[3] == amenityType) {
        //qDebug()<<rowData[3]<<amenityType;
        //filter by amenity type, move to QML in order to have the drop down menu choose what is displayed?
        //if (rowData[3] == amenityType) {
        latitude= rowData[0].toDouble();
        longitude= rowData[1].toDouble();
        name = rowData[2];
        orderLink = rowData[8];
        amenityType = rowData[3];

        //uses QStandardItem to assign attributes from the CSV to roles
        QStandardItem *item = new QStandardItem;
        item->setData(QVariant::fromValue(name), NameRole);

        item->setData(QVariant::fromValue(amenityType), AmenityRole);
        item->setData(QVariant::fromValue(orderLink), WebsiteRole);
        item->setData(QVariant::fromValue(QGeoCoordinate(latitude, longitude)), CoordinateRole);
        item->setData(QVariant::fromValue(color), ColorRole);
        appendRow(item);
        //        }

    }

#endif

}


void LocationModel::importJSon(){
    QUrl myUrl= filePath;
    newFile = new FileDownloader(myUrl,this);
    connect(newFile, SIGNAL (downloaded()), this, SLOT (processData()));
    qDebug()<<"File Sent";
}

void LocationModel::processData(){
    QJsonDocument itemDoc = QJsonDocument::fromJson(newFile->downloadedData());
    const QJsonValue &dataSet= itemDoc["data"].toArray();
    bool end=false;
    int i=0;
    qDebug()<<"Did We Make It?";
    while(end==false){
        qDebug()<<"1";
        QJsonValue datapoint= dataSet[i];
        QJsonValue information= datapoint["source"];
        QJsonValue locationData= information["data"];
        while(locationData["city"].toString()!="New York City"){
            i=i+1;
            datapoint= dataSet[i];
            information= datapoint["source"];
            locationData= information["data"];
        }



        LocationRecord record("latitude",locationData["lat"]);
        record.addVal("longitude",locationData["lng"]);
        record.addVal("title",locationData["title"]);
        record.addVal("address",locationData["address"]);
        //record.addVal("contact",datapoint["contact"]["general"]["web"]);

        //qDebug()<<(record.getVal("contact")).toString();

        QStandardItem *item = new QStandardItem;
        item->setData(QVariant::fromValue(QGeoCoordinate(record.getVal("latitude").toDouble(), record.getVal("longitude").toDouble())), CoordinateRole);
        item->setData(QVariant::fromValue(color), ColorRole);
        appendRow(item);

        records.insert(records.end(),record);
        i=i+1;
        if(dataSet[i].isNull() || i==100){
            end=true;
            qDebug()<<"We Made It?";

        }
    }

}




    //    QJsonValue latArr =itemDoc["latlng:latitude"].toArray();
    //    QJsonArray lngArr =itemDoc["longitude"].toArray();
    //    QJsonArray titleArr =itemDoc["title"].toArray();
    //    QJsonArray addressArr =itemDoc["address"].toArray();
    //    QJsonArray contactArr =itemDoc["contact"].toArray();
    //    QJsonArray cityArr = itemDoc["city"].toArray();
    //    qDebug()<<titleArr.isEmpty();
    //    qDebug()<<latArr.isEmpty();
    //    qDebug()<<lngArr.isEmpty();
    //    qDebug()<<addressArr.isEmpty();
    //    qDebug()<<contactArr.isEmpty();



    //    for(int x=0;x<titleArr.size(); x++){
    //        if(cityArr[x].toString()!="New York City"){
    //            break;
    //        }
    //        qDebug()<<"Did We Make It?";

    //        LocationRecord record("latitude",latArr[x].toVariant());
    //        record.addVal("longitude",latArr[x].toVariant());
    //        record.addVal("title",titleArr[x].toVariant());
    //        record.addVal("address",addressArr[x].toVariant());
    //        record.addVal("contact",contactArr[x].toVariant());

    //        qDebug()<<(record.getVal("title")).toString();

    //        QStandardItem *item = new QStandardItem;
    //        item->setData(QVariant::fromValue(QGeoCoordinate(latArr[x].toDouble(), lngArr[x].toDouble())), CoordinateRole);
    //        item->setData(QVariant::fromValue(color), ColorRole);
    //        appendRow(item);
    //        qDebug()<<"\n We Made It \n";

    //        records.insert(records.end(),record);

