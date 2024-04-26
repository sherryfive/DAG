#include <QtCore/QCoreApplication>
#include <QTextStream>
#include "DAG.h"
#include "qstring.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    printf("DATA : 1: DTO;   2: ETO;   3:TTO.\n");
    printf("Please enter a number (1бл3) to select the data:\n");

    int input;
    QTextStream cin(stdin);    
    while (true) {
        input = cin.readLine().toInt();
        if (input <=3 || input>=1) {
            break;
        }  
        else        {
            printf("Please enter a number (1бл3) to select the data:\n");
        }
    }

    QStringList path;
    path << "vipfile/BH-5000-YUAN.csv";
    path << "vipfile/BH-5000-order.csv";
    path << "vipfile/BH-5000-myorder.csv";

    DAG dd;
    dd.readboreholes(path[input - 1]);
    if (input == 1)
        dd.sortByTRG();
    dd.generateGtable();

    printf("Success!\n");

    return a.exec();
}
