#pragma once

#include "BasicDrillSet.h"
#include "DrillSetHGraphAttitude.h"
class DrillSetHandle : public BDrillSet
{
public:
	DrillSetHandle(){}
	DrillSetHandle(BDrillSet dd){	*this = DrillSetHandle();	dlist << dd.getDist();	rocklist = dd.getRockList();}
	DrillSetHandle(const DrillSetHandle& p)	{	dlist = p.dlist;	rocklist = p.rocklist;	mmlist = p.mmlist;	obblist = p.obblist;}

	inline BDrillSet getDset() { return BDrillSet(dlist, rocklist); }

	void getDirectedGraph();
	void getCross_contact_matrix();
private:
	QList<QList<int>> mmlist;
	QList<BObb> obblist;
};


