#ifndef TESTMODEMODEL_H
#define TESTMODEMODEL_H

#include <QObject>
#include "FireworkProperties.h"

class TestModeModel : public QObject
{
    Q_OBJECT
public:
    TestModeModel();

    void generateFireworkSpecifications();

signals:
    void specificationsGenerated(QString shapeSpec, QString colorSpec, QString soundSpec, int shellDiameterSpec);

private:
    FireworkProperties fireworkSpec;

    QString shapeOptions[4] = {"Circle", "Heart", "Smile", "Star"};
    QString colorOptions[8] = {"red", "orange", "yellow", "green", "blue", "purple", "pink", "white"};
    QString soundOptions[3] = {"Crackle", "Bang", "Whistle"};
    int shellDiameterOptions[4] = {3,6,9,12};

};

#endif // TESTMODEMODEL_H
