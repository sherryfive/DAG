#pragma once

#include "BasicPoint.h"

class BDrillPoint
{
public:
	BDrillPoint();
	BDrillPoint(BPoint p);
	BDrillPoint(const BDrillPoint& p);

	inline BPoint& getPoint() { return pp; }
	inline double& getFrom() { return from; }
	inline double& getTo() { return to; }
	inline QString & getContent() { return content; }
	inline QString & getName() { return name; }
	inline double getValue() { return pp.getValue(); }

	inline Bvector getNol() { return Bvector(azimuth, dip); }
	inline double thick()	{		return abs(to - from);	}
	inline void comPos(BDrillPoint p) { pp[0] = p.getPoint()[0] + getNol() * thick(); }

	bool operator == (BDrillPoint p);
	bool fromString(QString str, QString split = ",");	
protected:
private:
	BPoint pp;
	double from, to;
	double azimuth, dip;
	QString content;
	QString name;
};

class BDPset
{
public:
	BDPset(){}
	BDPset(const BDPset& p) { plist = p.plist; }

	inline QList<BDrillPoint>& getDPist() { return plist; }
	inline int size() { return plist.size(); }

	inline BDrillPoint & operator [] (int i) { return plist[i]; }
	inline BDPset& operator << (BDrillPoint p)	{		plist << p;		return *this;	}

	void comPointset(bool ismerge);
protected:
private:
	QList<BDrillPoint> plist;
};

