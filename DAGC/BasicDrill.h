#pragma once
#include "BasicDrillPoint.h"
class BDrill
{
public:
	BDrill(QString nn = "")	{
		name = nn;
		dplist = BDPset();
	}
	BDrill(const BDrill& p)	{
		name = p.name;
		dplist = p.dplist;
	}

	inline QString & getName() { return name; }
	inline BDPset & getDPset() { return dplist; }
	inline BDrillPoint & operator [] (int i) { return dplist[i]; }
	inline int size() { return dplist.size(); }
	inline void computePoint(bool ismerge = true)	{		dplist.comPointset(ismerge);	}
	
	BPointSet getCenterPointDname();

protected:
private:
	QString name;
	BDPset dplist;
};
