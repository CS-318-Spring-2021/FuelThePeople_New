#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QStandardItemModel>


class model
{
public:
    model();
    void createModel(const QString modelName);
    void readCSV(const QString filePath, const QStandardItemModel itemModel);
    int Coordinates();
};

#endif // MODEL_H
