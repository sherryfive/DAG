#include "DrillSetHandle.h"

void DrillSetHandle::getDirectedGraph(){
	if (rocklist.size() == 0)
		sortAttributeDefault();

	DrillSetHGraphAttitude matrix = DrillSetHGraphAttitude(getDset());

	QStringList str;
	matrix.getStrlistFromBorehole(str);
	QList<int> rank = matrix.rockRankHandleZong(str);
	matrix.DirectedgraphCalOut(str, rank);

	rocklist = matrix.getRocklist();
	dlist = matrix.getDrillList().getDist();

	updateValue();
}

void DrillSetHandle::getCross_contact_matrix(){
	if (rocklist.size() == 0)
		sortAttributeDefault();

	DrillSetHGraphAttitude matrix = DrillSetHGraphAttitude(getDset());

	QStringList str;
	matrix.AttrAndDgCombine(str);

	rocklist = matrix.getRocklist();
	dlist = matrix.getDrillList().getDist();

	updateValue();
	return;
}

