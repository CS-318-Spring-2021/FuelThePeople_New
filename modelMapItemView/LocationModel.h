
#ifndef LOCATIONMODEL_H
#define LOCATIONMODEL_H
#include <QStandardItemModel>
#include <QtQml/qqml.h>
#include <locationrecord.h>
#include <QNetworkAccessManager>
#include <QVariant>
#include "locationrecord.h"
#include "filedownloader.h"

class QString;
class QQuickView;

class LocationModel : public QStandardItemModel
{ Q_OBJECT
  QML_ELEMENT

private:
    QString modelName, filePath;
    QColor color;


public:
    //enumerate roles to communicate between the model and QML
    enum {
        CoordinateRole = Qt::UserRole + 1000,
        ColorRole,
        NameRole,
        WebsiteRole,
        AmenityRole
    };

    std::list<LocationRecord> records;
    FileDownloader *newFile;
    std::map<QUrl, FileDownloader> files;
    LocationModel(QString _modelName, QString _filePath, QColor _color);

    void addToMap(QQuickView &view);
    void importCSV();
    void importJSon();
//    std::map<QString, LocationRecord> getLocationRecordList();
//    LocationRecord getLocationRecord(QString id);
//    void appendLocationRecordList(QVariant data);


public slots:
    void processData();
};

#endif // LOCATIONMODEL_H
