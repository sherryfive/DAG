#pragma once

#include "BasicDrillPoint.h"
#include "PCL.h"

class BObb
{
public:
	BObb();
	BObb(BPointSet p);
	BObb(const BObb& p);

	inline BPointSet& getPoint() { return plist; }
	inline int& getNum() { return num; }
	inline Bvector& getHalfextent() { return halflen; }
	inline QList<Bvector>& getVectors() { return vectors; }
	inline Bvector& getPosition() { return cenpoint; }

	void sortVectorLen();
	bool compute();
protected:
private:
	Bvector halflen, cenpoint;
	QList<Bvector> vectors;
	double dis;
	BPointSet plist;	
	int num;
};
