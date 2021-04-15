
#ifndef LOCATIONMODEL_H
#define LOCATIONMODEL_H
#include <QStandardItemModel>

class QString;
class QQuickView;

class locationModel : public QStandardItemModel
{ Q_OBJECT
private:
    QString modelName, filePath, amenityType;
public:
    locationModel(QString _modelName, QString _filePath, QString _amenityType);
    void addToMap(QQuickView &view);
//public:
//    mapModel();
//    void createModel(const QString modelName);
//    void readCSV(const QString filePath, QStandardItemModel itemModel, const QString amenityType);
//    int Coordinates();
};

#endif // LOCATIONMODEL_H


