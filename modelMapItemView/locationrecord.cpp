#include "locationrecord.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QFile>
#include <map>
#include <QVariant>
#include <QUrl>

LocationRecord::LocationRecord(QString _label, QVariant _value)
{
    record[_label]=_value;

}

int LocationRecord::addVal(QString label, QVariant value){

    if(record.find(label) == record.end()){
        record[label]= value;
        return 1;
    }
    return 0;
}

int LocationRecord::setVal(QString label, QVariant value){

    if(record.find(label) == record.end()){
        record[label]= value;
        return 1;
    }else{
        record[label] = value;
        return 1;
    }

    return 0;
}

QVariant LocationRecord::getVal(QString label){

    auto iterator = record.find(label);

    if(iterator == record.end()){
        return QVariant();
    }

    return iterator->second;


}

// LocationRecord:: combineAddress(QString label, QString value){
//    if(compare(label,"name"){

//            return true;
//    }
//    return false;
//}




