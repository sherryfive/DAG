#include "BasicDrillSet.h"

int BDrillSet::getDrillIdFronName(QString name){
	for (int i = 0; i < size(); i++)	{
		if (dlist[i].getName() == name)
			return i;
	}
	return -1;
}

void BDrillSet::updateValue(){
	for (int i = 0; i < dlist.size(); i++)	{
		for (int j = 1; j < dlist[i].size(); j++)		{
			int ff = BasicFun::getStrId(dlist[i][j].getContent(), rocklist);
			dlist[i][j].getPoint().getValue() = ff;
		}
	}
}

QList<BPointSet> BDrillSet::getCenterPsetRnum(){
	QList<BPointSet> pp;
	for each (QString var in rocklist)
		pp << BPointSet(var);

	for each (BDrill var in dlist)	{
		BPointSet tp = var.getCenterPointDname();
		for each (BPoint var1 in tp.getPointList())		{
			pp[var1.getValue()] << var1;
		}
	}
	return pp;
}

void BDrillSet::sortAttributeDefault()
{
	rocklist.clear();
	for each (BDrill tempd in dlist)	{
		for (int i = 0; i < tempd.size(); i++)		{
			if (i == 0)
				BasicFun::addRock("", tempd[i].getContent(), rocklist);
			else
				BasicFun::addRock(tempd[i - 1].getContent(), tempd[i].getContent(), rocklist);
		}
	}
	for (int i = 0; i < rocklist.size(); i++)	{
		if (rocklist[i] == "")		{
			rocklist.removeAt(i);
			i--;
		}
	}
	updateValue();
}
