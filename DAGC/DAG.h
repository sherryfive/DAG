#pragma once

#include <QtWidgets/QMainWindow>
#include "DrillSetHandle.h"
#include "qobject.h"

extern DrillSetHandle dlist;
class DAG :public QObject
{
    Q_OBJECT
public:
    DAG() {}
public slots:
    void readboreholes(QString path = "");
    void sortByTRG();
    void generateGtable();
};
