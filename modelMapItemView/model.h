#ifndef MODEL_H
#define MODEL_H
#include <QString>


class model
{
public:
    model();
    void createModel(const QString modelName);
    void readCSV(const QString filePath, const model itemModel);
    int Coordinates();
};

#endif // MODEL_H
