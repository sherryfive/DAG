#include "BasicDrill.h"

BPointSet BDrill::getCenterPointDname(){
	BPointSet pp;
	for (int i = 1; i < dplist.size(); i++)	{
		BPoint p;
		p.getPos() = (dplist[i - 1].getPoint().getPos() + dplist[i].getPoint().getPos()) / 2.0;
		p.getValue() = dplist[i].getPoint().getValue();
		p.getName() = name + "+" + def_QSTR_arg(i - 1);
		pp << p;
	}
	pp.getName() = name;
	return pp;
}
