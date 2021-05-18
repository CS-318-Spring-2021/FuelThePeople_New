
#ifndef LOCATIONMODEL_H
#define LOCATIONMODEL_H
#include <QStandardItemModel>
#include <QtQml/qqml.h>

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
    LocationModel(QString _modelName, QString _filePath, QColor _color);
    void addToMap(QQuickView &view);

};

#endif // LOCATIONMODEL_H
