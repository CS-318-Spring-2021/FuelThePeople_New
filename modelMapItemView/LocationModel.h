
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
    QString modelName, filePath, amenityType;
    QColor color;

public:
    enum {
       CoordinateRole = Qt::UserRole + 1000,
       ColorRole,
       NameRole,
       WebsiteRole
    };
    LocationModel(QString _modelName, QString _filePath, QString _amenityType, QColor _color);
    void addToMap(QQuickView &view);

};

#endif // LOCATIONMODEL_H
