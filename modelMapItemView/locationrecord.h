#ifndef LOCATIONRECORD_H
#define LOCATIONRECORD_H
#include <QStandardItemModel>
#include <QtQml/qqml.h>
#include <QMap>
#include <list>
#include <QVariant>
#include <QGeoCoordinate>
#include <map>


class LocationRecord
{
public:
    std::map<QString, QVariant> record;
    LocationRecord(QString _label, QVariant _value);
    int addVal(QString label, QVariant value);
    int setVal(QString label, QVariant value);
    QVariant getVal(QString label); 
   // bool isComplete(QString value);

};

#endif // LOCATIONRECORD_H
