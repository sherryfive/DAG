#pragma once

#include "BasicVector.h"

class BPoint
{
public:
	BPoint()	{	pos = Bvector(0, 0, 0);	nol = Bvector(0, 0, 1);	id = "";value = 0;}
	BPoint(Bvector p)	{  *this = BPoint();	pos = p;}
	BPoint(const BPoint& p):id(p.id), pos(p.pos), nol(p.nol), value(p.value){}

	inline Bvector& getPos(void)	{	return pos;	}
	inline Bvector& getNol(void)	{	return nol;	}
	inline QString& getName(void)	{	return id;	}
	inline double & getValue(void)	{	return value;	}
	inline Bvector& operator [] (int i) { return  (i == 0) ? pos : nol; }
protected:
	Bvector pos;
	Bvector nol;
	QString id;
	double value;
private:
};

class BPointSet
{
public:
	BPointSet(QString nn = "")	{	name = nn;}
	BPointSet(const BPointSet& p): plist(p.plist), name(p.name)	{}

	inline QString & getName()	{	return name;}
	inline QList<BPoint> getPointList()	{	return plist;}
	inline int size() { return plist.size(); }

	inline BPoint& operator [] (int i)	{	return plist[i];}
	inline BPointSet& operator << (BPoint p)	{	plist << p;	return *this;}

	QList<QVector3D> getQv3dList();
protected:
private:
	QString name;
	QList<BPoint> plist;
};
