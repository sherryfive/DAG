#include "BasicDrillPoint.h"

BDrillPoint::BDrillPoint(){
	pp = BPoint();
	content = "";
	from = 0;
	to = 0;
	azimuth = 0;
	dip = -90;
}

BDrillPoint::BDrillPoint(BPoint p){
	*this = BDrillPoint();
	pp = p;
}

BDrillPoint::BDrillPoint(const BDrillPoint& p){
	pp = p.pp;
	content = p.content;
	from = p.from;
	to = p.to;
	azimuth = p.azimuth;
	dip = p.dip;
	name = p.name;
}

bool BDrillPoint::operator==(BDrillPoint p){
	if (dip == p.dip && azimuth == p.azimuth)	{
		if ((content != "" && content == p.getContent()) || (content == "" && getValue() == p.getValue()))
			return true;
	}
	return false;
}

bool BDrillPoint::fromString(QString str, QString split){
	QStringList ss = str.split(split);
	if (ss.size() >= 11)	{
		name = ss[0];
		int tt = 1;
		pp = BPoint(Bvector(ss[tt + 0].toDouble(), ss[tt + 1].toDouble(), ss[tt + 2].toDouble()));
		pp.getValue() = ss[tt + 3].toDouble();

		content = ss[tt + 4];
		from = ss[tt + 5].toDouble();
		to = ss[tt + 6].toDouble();

		azimuth = ss[tt + 7 + 1].toDouble();
		dip = ss[tt + 8 + 1].toDouble();
		return true;
	}
	return false;
}

void BDPset::comPointset(bool ismerge){
	if (plist.size() <= 1)			
		return;
	bool isneedtrans = false;
	for (int j = 1; j < plist.size(); j++)	{
		if (plist[j].getTo() < plist[j].getFrom())
			isneedtrans = true;
		if (isneedtrans)
			break;
	}
	if (isneedtrans)	{
		double fz = plist.first().getPoint()[0][2];
		for (int j = 0; j < plist.size(); j++)		{
			plist[j].getFrom() = fz - plist[j].getFrom();
			plist[j].getTo() = fz - plist[j].getTo();
		}
	}
	for (int j = 0; j < plist.size(); j++)	{
		if (j + 1 < plist.size())		{
			if (plist[j].getContent() == "" && plist[j + 1].getContent() != "")
				plist[j].getContent() = plist[j + 1].getContent();
		}
		if (j - 1 >= 0)		{
			if (plist[j].getContent() == "" && plist[j - 1].getContent() != "")
				plist[j].getContent() = plist[j - 1].getContent();
		}
	}
	double ss = plist[0].getFrom();
	if (ss != 0)	{
		for (int j = 0; j < plist.size(); j++)		{
			plist[j].getFrom() -= ss;
			plist[j].getTo() -= ss;
		}
	}
	for (int j = 1; j < plist.size(); j++)	{
		if (abs(plist[j].getFrom() - plist[j].getTo()) < 0.001)		{
			plist.removeAt(j);
			j--;
			if (j < plist.size() && j - 1 >= 0)			
				plist[j].getFrom() = plist[j - 1].getTo();			
		}
	}

	if (plist.size() <= 1)
		return;
	if (plist[0].getTo() == 0 && plist[0].getFrom() != 0)	{
		if (plist.size() > 1)
			plist[1].getPoint() = plist[0].getPoint();
		plist.removeFirst();
		plist.first().getFrom() = 0;
	}

	if (ismerge)	{
		for (int i = 1; i < size(); i++)		{
			if (plist[i] == plist[i - 1] && i > 1)			{
				plist[i].getFrom() = plist[i - 1].getFrom();
				plist.removeAt(i - 1);
				i--;
			}
		}
	}

	for (int i = 1; i < size(); i++)	{
		plist[i].getFrom() = plist[i - 1].getTo();
	}
	if (plist.first().getTo() != 0)	{
		plist.prepend(plist.first());
		plist.first().getTo() = 0;
	}
	for (int i = 1; i < plist.size(); i++)	{
		plist[i].comPos(plist[i - 1]);
	}
}
