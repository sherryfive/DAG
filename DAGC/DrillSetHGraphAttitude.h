#pragma once

#include "BObb.h"
#include "BasicDrillSet.h"
#include "GraphDAG.h"

class DrillSetHGraphAttitude
{
public:
	DrillSetHGraphAttitude(BDrillSet drilllist){	dlist = drilllist;}	
	DrillSetHGraphAttitude(const DrillSetHGraphAttitude& t){	mmlist = t.mmlist;	dlist = t.dlist;	rnumlist = t.rnumlist;}
	~DrillSetHGraphAttitude() {}

	inline QStringList& getRocklist() { return dlist.getRockList(); }
	inline BDrillSet& getDrillList() { return dlist; }
	
	void DirectedgraphCalOut(QStringList &strlist, QList<int> rank);
	void AttrAndDgCombine(QStringList& strlist);	

	void getStrlistFromBorehole(QStringList& strlist);
	QList<int> rockRankHandleZong(QStringList& strlist);

protected:
	void AttrAndDgCombine_CylcleDis(QStringList& strlist, QStringList coalnamelist);

	Digraph getDiGraph();

	inline int isInRockList(QString name)	{	return BasicFun::getStrId(name, dlist.getRockList());}
	void getnameInRockList(QString& name, QString lianjiefu, QString v);

	BObb getOBBofRock(QString rock);
	QList<BObb> getOBBofRock(QStringList rock);
	double getOBBHofRock(BObb rock);
	QList<double> getOBBHofRock(QList<BObb> rock);

	QStringList sortRockByRank(QList<int> rank, QStringList yuan_rock, QStringList strlist);
	QList<int> getRank(bool isfan);
	void equlRankHandle(QList<int> rank);
	QStringList getRockOfRank(int rank_value, QList<int> rank);

	int changeAttributeByPlane(BObb obb, QString name, QString newname);
	int changeAttributeByPlane(Bvector pos, Bvector nol, BPointSet pp, QString name, QString newname);
	int changeAttribute(QString upstr, QString downstr, QString newname, bool isup);

	int InplaneFace(Bvector pos, Bvector nol, BPointSet pp);

	void writeGraphviz(QString namePath, bool iscolor);
	void writeGraphviz_edge(QString namePath);
	void writeGraphviz_node(QString namePath, QList<int> rank);
	void writeGraphviz_DG(QString namePath);
private:
	QList < QList<int>> mmlist;
	QList<int> rnumlist;
	BDrillSet dlist;
	QList<QStringList> name2colorlist;
};

