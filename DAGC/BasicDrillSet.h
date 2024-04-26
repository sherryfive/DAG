#pragma once

#include "BasicDrill.h"

class BDrillSet
{
public:
	BDrillSet(){}
	BDrillSet(QList<BDrill> pl){	*this = BDrillSet();	dlist = pl;}
	BDrillSet(QList<BDrill> pl, QStringList rlist){	*this = BDrillSet();	dlist = pl;	rocklist = rlist;}
	BDrillSet(const BDrillSet& p){	dlist = p.dlist;	rocklist = p.rocklist;}

	inline QList<BDrill>& getDist() { return dlist; }
	inline QStringList& getRockList() { if (rocklist.size() == 0)			sortAttributeDefault();		return rocklist; }

	inline int size() { return dlist.size(); }
	inline void clear() { dlist.clear(); }
	inline void removeAt(int i) { dlist.removeAt(i); }

	inline BDrill& first() { return dlist.first(); }
	inline BDrill& last() { return dlist.last(); }
	inline BDrill& operator [] (int i) { return dlist[i]; }

	inline int getRockValue(QString _rock) { return BasicFun::getStrId(_rock, rocklist); }
             	 
	int getDrillIdFronName(QString name);	            
	void updateValue();
	QList<BPointSet> getCenterPsetRnum();	
	void sortAttributeDefault();

protected:
	QList<BDrill> dlist;
	QStringList rocklist;
private:	
};