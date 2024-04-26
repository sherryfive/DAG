#include "DrillSetHGraphAttitude.h"

void DrillSetHGraphAttitude::DirectedgraphCalOut(QStringList & strlist, QList<int> rank){
	getStrlistFromBorehole(strlist);

	writeGraphviz_node("vipfile\\Graph data node.csv", rank);
	writeGraphviz_edge("vipfile\\Graph data edge.csv");	

	writeGraphviz("vipfile\\Graphviz_dot.txt", false);
	writeGraphviz_DG("vipfile\\Graphviz_AM.csv");	
}

void DrillSetHGraphAttitude::AttrAndDgCombine(QStringList & strlist){
	QStringList yuan_rock = dlist.getRockList();
	AttrAndDgCombine_CylcleDis(strlist, QStringList());

	getStrlistFromBorehole(strlist);

	QList<int> rank = rockRankHandleZong(strlist);	
	sortRockByRank(rank, yuan_rock, strlist);
	rank = rockRankHandleZong(strlist);	

	DirectedgraphCalOut(strlist, rank);
}

void DrillSetHGraphAttitude::AttrAndDgCombine_CylcleDis(QStringList& strlist, QStringList coalnamelist){
	int fflag = 1;
	for (int i = 0; i < def_MAXVALUE; i++)	{
		fflag = (fflag == 1) ? 2 : 1;

		getStrlistFromBorehole(strlist);
		for (int j = 0; j < dlist.getRockList().size(); j++)		{
			if (rnumlist[j] == 0)			{
				rnumlist.removeAt(j);
				dlist.getRockList().removeAt(j);
				j--;
			}
		}
		getStrlistFromBorehole(strlist);

		Digraph ddd_rapht = getDiGraph();
		DirectedCycle ddd_gcomt = DirectedCycle(ddd_rapht);
		if (!ddd_gcomt.hasCycle())
			break;

		QList<QList<int>>ccs = ddd_gcomt.getcycles();
		QList<int> minc = ddd_gcomt.getMincycle();

		bool isshowcontent = true;		
		for (int k = 0; k < 1; k++)		{
			QList<int> mc = minc;

			QStringList myrock;
			for (int jj = 0; jj < mc.size() - 1; jj++)
				myrock << getRocklist()[mc[jj]];
			QList<BObb> mobb = getOBBofRock(myrock);
			for (int yy = 0; yy < mobb.size(); yy++)			{
				if (mobb[yy].getNum() <= 3)				{
					mobb.removeAt(yy);
					myrock.removeAt(yy);
					yy--;
				}
			}

			int flag_maxh_mobb;
			QString mname;
			int numc = 0; 
			for (;;)			{
				if (myrock.size() == 0)
					break;
				if (numc > 0)
					break;

				flag_maxh_mobb = BasicFun::getMaxValueId(getOBBHofRock(mobb));
				mname = myrock[flag_maxh_mobb];
				getnameInRockList(mname, "-", "N");
				numc = changeAttributeByPlane(mobb[flag_maxh_mobb], myrock[flag_maxh_mobb], mname);
				if (numc == 0)				{
					mobb.removeAt(flag_maxh_mobb);
					myrock.removeAt(flag_maxh_mobb);
				}				
			}
			if (numc > 0 && myrock.size() > 0)			{
				getRocklist().append(mname);
				break;
			}
			if (mc.size() == 3)			{
				int qian = mc[0];
				int hou = mc[1];

				QString strqian = getRocklist()[qian];
				QString strhou = getRocklist()[hou];

				if (BasicFun::getStrId(strqian, coalnamelist) == -1 && 
					BasicFun::getStrId(strhou, coalnamelist) > -1 && mmlist[qian][hou] != rnumlist[qian]){
					QString mynnn = strqian;
					getnameInRockList(mynnn, "-", "N");
					if (changeAttribute(strqian, strhou, mynnn, true) > 0)			
						getRocklist().append(mynnn);
				}
				else if (BasicFun::getStrId(strhou, coalnamelist) == -1 && 
					BasicFun::getStrId(strqian, coalnamelist) > -1 && mmlist[qian][hou] != rnumlist[hou]){
					QString mynnn = strhou;
					getnameInRockList(mynnn, "-", "N");
					if (changeAttribute(strqian, strhou, mynnn, false) > 0)		
						getRocklist().append(mynnn);
				}
				else
				{
					if (fflag == 1)					{
						BasicFun::trans(qian, hou);
						BasicFun::trans(strqian, strhou);
					}
					if (mmlist[qian][hou] != rnumlist[qian])			{
						QString mynnn = strqian;
						getnameInRockList(mynnn, "-", "N");
						if (changeAttribute(strqian, strhou, mynnn, true) > 0)			
							getRocklist().append(mynnn);
					}
				}
			}
			else			{
				for (int j = fflag; j < mc.size(); j++)				{
					int qian = mc[j - 1];
					int hou = mc[j];

					QString strqian = getRocklist()[qian];
					QString strhou = getRocklist()[hou];

					if (BasicFun::getStrId(strqian, coalnamelist) == -1 && mmlist[qian][hou] != rnumlist[qian])		{
						QString mynnn = strqian;
						getnameInRockList(mynnn, "-", "N");
						if (changeAttribute(strqian, strhou, mynnn, true) > 0)						{
							getRocklist().append(mynnn);
							j++;							
						}
					}
					else if (BasicFun::getStrId(strhou, coalnamelist) == -1 && mmlist[qian][hou] != rnumlist[hou])					{
						QString mynnn = strhou;
						getnameInRockList(mynnn, "-", "N");
						if (changeAttribute(strqian, strhou, mynnn, false) > 0)	{
							getRocklist().append(mynnn);
							j++;	
						}
					}
				}
			}
		}
	}
}

void DrillSetHGraphAttitude::getnameInRockList(QString & name, QString lianjiefu, QString v){
	for (int i = 1; i < def_MAXVALUE; i++)	{
		int fid = isInRockList(name);
		if (fid == -1)
			break;
		if (name.contains(lianjiefu))
			name = name.split(lianjiefu).first() + lianjiefu + def_QSTR_arg(name.split(lianjiefu).last().toInt() + 1);
		else
			name.append(QString("%0%1").arg(lianjiefu).arg(1));
	}
}

BObb DrillSetHGraphAttitude::getOBBofRock(QString rock){
	QList<BPointSet> plist = dlist.getCenterPsetRnum();
	int flag = BasicFun::getStrId(rock, getRocklist());
	BPointSet o_pset = plist[flag];

	if (o_pset.size() < 3)	{
		BPoint p = o_pset[0];
		p[0] += Bvector(1, 0, 0);
		o_pset << p;
	}
	if (o_pset.size() < 3)	{
		BPoint p = o_pset[0];
		p[0] += Bvector(1, 1, 0);
		o_pset << p;
	}
	BObb nn = BObb(o_pset);
	nn.compute();
	return nn;
}

QList<BObb> DrillSetHGraphAttitude::getOBBofRock(QStringList rock){
	QList<BObb> obb;
	for each (QString var in rock)	{
		obb << getOBBofRock(var);
	}
	return obb;
}

double DrillSetHGraphAttitude::getOBBHofRock(BObb rock){
	return rock.getHalfextent().getMinXYZ();
}

QList<double> DrillSetHGraphAttitude::getOBBHofRock(QList<BObb> rock){
	QList<double> obb;
	for each (BObb var in rock)	{
		obb << getOBBHofRock(var);
	}
	return obb;
}

void DrillSetHGraphAttitude::getStrlistFromBorehole(QStringList & strlist){
	QList<int> numlist;
	for each (QString var in dlist.getRockList())
		numlist << 0;
	for each (BDrill var in dlist.getDist())	{
		for (int i = 1; i < var.size(); i++)		{
			int ff = BasicFun::getStrId(var[i].getContent(), dlist.getRockList());
			numlist[ff]++;
		}
	}
	for (int i = 0; i < numlist.size(); i++)	{
		if (numlist[i] == 0)		{
			numlist.removeAt(i);
			dlist.getRockList().removeAt(i);
			i--;
		}
	}
	dlist.updateValue();
	mmlist.clear();
	rnumlist.clear();
	for (int i = 0; i < dlist.getRockList().size(); i++)	{
		QList<int> alist;
		for (int j = 0; j < dlist.getRockList().size(); j++)
			alist.append(0);
		mmlist.append(alist);
		rnumlist << 0;
	}

	for each (BDrill ddr in dlist.getDist())	{
		for (int i = 2; i < ddr.size(); i++)		{
			QString qianstr = ddr.getDPset()[i - 1].getContent();
			QString houstr = ddr.getDPset()[i].getContent();

			int qian = isInRockList(qianstr);
			int hou = isInRockList(houstr);

			mmlist[qian][hou]++;
			if (i == 2)
				rnumlist[qian]++;
			rnumlist[hou]++;
		}
	}

	for (int i = 0; i < mmlist.size(); i++)	{
		QString ss = "";
		if (i == 0)		{
			ss = "Name";
			for (int j = 0; j < mmlist[i].size(); j++)			{
				ss += ",";
				ss += QString("%0").arg(dlist.getRockList()[j]);
			}
			strlist.append(ss);
		}
		ss = dlist.getRockList()[i];
		for (int j = 0; j < mmlist[i].size(); j++)		{
			ss += ",";
			ss += QString("%0").arg(mmlist[i][j]);
		}
		strlist.append(ss);
	}
}

Digraph DrillSetHGraphAttitude::getDiGraph(){
	Digraph r = Digraph(dlist.getRockList().size());
	int num = dlist.getRockList().size();
	for (int i = 0; i < num; i++)	{
		for (int j = 0; j < num; j++)		{
			if (mmlist[i][j] > 0)
				r.addEdge(i, j);
		}
	}
	return r;
}

QList<int> DrillSetHGraphAttitude::rockRankHandleZong(QStringList& strlist){
	int equal_num = 0;
	bool isfan = false;
	QList<int>rank;	
	for (int i = 0; i < 100; i++)	{
		int numr_before = dlist.getRockList().size();

		rank = getRank(isfan);
		equlRankHandle(rank);
		getStrlistFromBorehole(strlist);

		if (numr_before == dlist.getRockList().size())
			equal_num++;
		if (equal_num >= 2 && !isfan)
			break;
		isfan = !isfan;
	}
	return rank;
}

QStringList DrillSetHGraphAttitude::sortRockByRank(QList<int> rank, QStringList yuan_rock, QStringList strlist){
	QStringList nowrocklist = dlist.getRockList();
	QStringList newr;
	for (int i = 0; i < rank.size(); i++)	{
		QStringList idlist = getRockOfRank(i, rank);
		if (idlist.size() == 1)
			newr << idlist.first();
		else		{
			QList<int>pos;
			for each (QString var in idlist)			{
				int flag = BasicFun::getStrId(var.split("-").first(), yuan_rock);
				if (flag > -1)
					pos << flag;
			}
			for (;;)			{
				if (pos.size() == 0)
					break;
				int minid = BasicFun::getMinValueId(pos);
				newr << idlist[minid];
				idlist.removeAt(minid);
				pos.removeAt(minid);
			}
		}
	}
	dlist.getRockList() = newr;
	getStrlistFromBorehole(strlist);
	return newr;
}

QList<int> DrillSetHGraphAttitude::getRank(bool isfan){
	QList<int> rank;
	for each (QString var in dlist.getRockList())
		rank << -1;
	Digraph r = getDiGraph();
	DirectedCycle g = DirectedCycle(r);

	for (int i = 0; i < dlist.getRockList().size(); i++)	{
		bool isfind = false;
		for (int j = 0; j < dlist.getRockList().size(); j++)	{
			if (i == j)
				continue;
			QList<int> jlist = r.getAdj(j);
			if (BasicFun::getValId(i, jlist) > -1)	{
				isfind = true;
				break;
			}
		}
		if (!isfind)
			rank[i] = 1;
	}
	for (int i = 1; i <= rank.size(); i++){
		for (int j = 0; j < rank.size(); j++){
			if (rank[j] == i)	{
				QList<int> jlist = r.getAdj(j);
				for each (int var in jlist)	{
					rank[var] = rank[var] > i + 1 ? rank[var] : i + 1;
				}
			}
		}
	}
	if (!isfan)
		return rank;
	for (int i = rank.size(); i >= 0; i--)	{
		for (int j = 0; j < rank.size(); j++)	{
			if (rank[j] == i)	{
				for (int k = 0; k < rank.size(); k++)	{
					QList<int> klist = r.getAdj(k);
					if (BasicFun::getValId(j, klist) > -1)	{
						rank[k] = i - 1;
					}
				}
			}
		}
	}
	return rank;
}

void DrillSetHGraphAttitude::equlRankHandle(QList<int> rank){
	QStringList before, after;
	for (int ff = 1; ff < dlist.getRockList().size(); ff++){
		QStringList idlist = getRockOfRank(ff, rank);	
		if (idlist.size() <= 1)
			continue;

		for (int j = 0; j < idlist.size(); j++)	{
			QStringList namelist;

			QString namej = idlist[j];		
			QString name = namej.split("-").first();
			for (int k = 0; k < idlist.size(); k++)	{
				if (j == k)continue;
				QString namek = idlist[k];
				QString namek_t = namek.split("-").first();

				if (name == namek_t)		{
					namelist << namek;
					idlist.removeAt(k);
					k--;
				}
			}

			if (namelist.size() == 0)
				continue;

			for each (QString var in namelist)	{
				before << var;
				after << namej;
			}
		}		
	}
	for (int i = 0; i < dlist.size(); i++)	{
		for (int j = 0; j < dlist[i].size(); j++){
			QString cont = dlist[i][j].getContent();
			int flag = BasicFun::getStrId(cont, before);
			if (flag > -1)	{
				dlist[i][j].getContent() = after[flag];
			}
		}
	}
}

QStringList DrillSetHGraphAttitude::getRockOfRank(int rank_value, QList<int> rank){
	QStringList idlist;
	for (int j = 0; j < rank.size(); j++)	{
		if (rank[j] == rank_value)
			idlist << dlist.getRockList()[j];
	}
	return idlist;
}

int DrillSetHGraphAttitude::changeAttributeByPlane(BObb obb, QString name, QString newname){
	Bvector pos = obb.getPosition();
	Bvector nol = obb.getVectors()[0];
	BPointSet pp = obb.getPoint();
	return changeAttributeByPlane(pos, nol, pp, name, newname);
}

int DrillSetHGraphAttitude::changeAttributeByPlane(Bvector pos, Bvector nol, BPointSet pp, QString name, QString newname){
	int flag = 0;
	int num1 = InplaneFace(pos, nol, pp);
	int num2 = InplaneFace(pos, nol*-1, pp);
	if (num1 == 0 || num2 == 0)
		return flag;
	for each (BPoint var in pp.getPointList())	{
		Bvector nn = var.getPos() - pos;
		if (nn.dot(nol) < 0)		{
			QStringList pname = var.getName().split("+");
			QString dname = pname.first();
			int dpid = pname.last().toInt() + 1;
			int did = dlist.getDrillIdFronName(dname);
			dlist[did][dpid].getContent() = newname;
			flag++;
		}
	}
	return flag;
}

int DrillSetHGraphAttitude::changeAttribute(QString upstr, QString downstr, QString newname, bool isup){
	int nn = 0;
	for (int m = 0; m < dlist.size(); m++)	{
		for (int i = 2; i < dlist[m].size(); i++)		{
			QString qianstr = dlist[m][i - 1].getContent();
			QString houstr = dlist[m][i].getContent();

			if (qianstr == upstr && houstr == downstr)			{
				if (isup)
					dlist[m][i - 1].getContent() = newname;
				else
					dlist[m][i].getContent() = newname;
				nn++;
			}
		}
	}
	return nn;
}

int DrillSetHGraphAttitude::InplaneFace(Bvector pos, Bvector nol, BPointSet pp){
	int flag = 0;
	for each (BPoint var in pp.getPointList())	{
		Bvector nn = var.getPos() - pos;
		if (nn.dot(nol) > 0)
			flag++;
	}
	return flag;
}

void DrillSetHGraphAttitude::writeGraphviz(QString namePath, bool iscolor){
	QStringList alist, blist;
	QList<bool> isboth;
	for (int i = 0; i < dlist.getRockList().size(); i++)	{
		for (int j = 0; j < dlist.getRockList().size(); j++)		{
			if (mmlist[i][j] > 0)			{
				QString aa = dlist.getRockList()[i];
				QString bb = dlist.getRockList()[j];
				alist.append(aa);
				blist.append(bb);

				if (mmlist[j][i] > 0)
					isboth << true;
				else
					isboth << false;
			}
		}
	}

	QStringList str;
	str << "digraph G {";
	if (iscolor && name2colorlist.size() > 0)	{
		str << "node [style=filled]";
		for each (QString rr in dlist.getRockList())		{
			QString name = rr.split("-").first();
			int flag1 = BasicFun::getStrId(name, name2colorlist[0]);
			int flag2 = BasicFun::getStrId(name, name2colorlist[1]);
			int flag3 = BasicFun::getStrId(name, name2colorlist[2]);
			int flagn = flag1 + flag2 + flag3 + 2;

			str << rr + "[color='#" + name2colorlist[3][flagn] + "']";
		}
	}
	for (int i = 0; i < dlist.getRockList().size(); i++)	{
		for (int j = 0; j < alist.size(); j++)		{
			if (alist[j] == dlist.getRockList()[i])			{
				QString aa = alist[j];
				QString bb = blist[j];			

				if (aa.contains(QString::fromLocal8Bit("-")))	aa.replace(QString::fromLocal8Bit("-"), "oo");				
				if (bb.contains(QString::fromLocal8Bit("-")))	bb.replace(QString::fromLocal8Bit("-"), "oo");

				QString res = QString::fromLocal8Bit("%0->%1").arg(aa).arg(bb);
				if (isboth[j])
					res += "[dir ='both']";
				str << res;
			}
		}
	}
	str << "}";
	BasicFun::write2Txt(namePath, str);
}

void DrillSetHGraphAttitude::writeGraphviz_edge(QString namePath){
	QList<int> alist, blist;
	QStringList a1list, b1list, isboth;
	for (int i = 0; i < dlist.getRockList().size(); i++)	{
		for (int j = 0; j < dlist.getRockList().size(); j++)		{
			if (i == j)
				continue;
			if (mmlist[i][j] > 0)			{
				if (mmlist[j][i] > 0 && i < j)
					continue;

				if (mmlist[j][i] > 0)
					isboth << "both";
				else
					isboth << "forward";

				alist.append(i);
				blist.append(j);

				QString aa = dlist.getRockList()[i];
				QString bb = dlist.getRockList()[j];
				a1list.append(aa);
				b1list.append(bb);
			}
		}
	}

	QStringList str;
	str << "origin,target,id1,id2,dir";
	for (int i = 0; i < isboth.size(); i++)	{
		QString temp = a1list[i].replace("x", "");
		temp += "," + b1list[i].replace("x", "");
		temp += "," + def_QSTR_arg(alist[i] + 1);
		temp += "," + def_QSTR_arg(blist[i] + 1);
		temp += "," + isboth[i];
		str << temp;
	}
	BasicFun::write2Txt(namePath, str);
}

void DrillSetHGraphAttitude::writeGraphviz_node(QString namePath, QList<int> rank){
	QStringList duizhao = BasicFun::readFromTxt("vipfile\\Graph data duizhao.csv");
	QStringList name1, name2, color;
	for (int i = 1; i < duizhao.size(); i++)	{
		QStringList ss = duizhao[i].split(",");
		if (ss.size() > 8)		{
			name1 << ss[1];
			name2 << ss[2];
			color << ss[8];
		}
	}
	QList<int> numrank;
	for (int i = 0; i < dlist.getRockList().size(); i++)
		numrank << 0;

	QStringList str;
	str << "nameall,name,id,color16,xy,rank";
	for (int i = 0; i < dlist.getRockList().size(); i++)	{
		QString tr = dlist.getRockList()[i];
		int flag1 = BasicFun::getStrId(tr.split("-").first(), name1);
		int flag2 = BasicFun::getStrId(tr.split("-").first(), name2);

		QString co;
		if (flag1 > -1)
			co = color[flag1];
		else if (flag2 > -1)
			co = color[flag2];
		else
			return;

		QString temp = tr;
		temp += "," + tr.replace("x", "");
		temp += "," + def_QSTR_arg(i + 1);
		temp += "," + co;

		if (rank.size() > 0)	{
			int x = rank[i];
			int y = numrank[x];
			if (numrank[x] >= 0)	{
				numrank[x]++;
				numrank[x] *= -1;
			}
			else	{
				numrank[x] *= -1;
			}

			temp += "," + def_QSTR_arg(x) + ":" + def_QSTR_arg(y) + "!";
			temp += "," + def_QSTR_arg(rank[i]);
		}
		str << temp;
	}
	BasicFun::write2Txt(namePath, str);
}

void DrillSetHGraphAttitude::writeGraphviz_DG(QString namePath){
	QStringList str;

	str << "\nAdjacency array";
	Digraph r = getDiGraph();
	DirectedCycle g = DirectedCycle(r);
	for (int i = 0; i < dlist.getRockList().size(); i++){
		QString temp = QString("%0,").arg(i);

		QList<int> ilist = r.getAdj(i);
		for (int j = 0; j < ilist.size(); j++)	{
			if (j > 0)
				temp += QString::fromLocal8Bit("£¬");
			temp += QString("%0").arg(ilist[j]);
		}
		str << temp;
	}

	str << "\nAdjacency matrix";
	for (int i = 0; i < mmlist.size(); i++)	{
		QString ss = "";
		if (i == 0)	{
			ss = "Adjacency matrix";
			for (int j = 0; j < mmlist[i].size(); j++)	{
				ss += ",";
				ss += QString("%0").arg(j);
			}
			str << ss;
		}
		ss = QString("%0").arg(i);
		for (int j = 0; j < mmlist[i].size(); j++)	{
			ss += ",";
			int flag = 0;
			if (mmlist[i][j] > 0)
				flag = 1;
			ss += QString("%0").arg(flag);
		}
		str << ss;
	}
	str << "\nAdjacency matrix";
	QStringList ttss;
	for (int i = 0; i < mmlist.size(); i++)	{
		QString ss = "";
		if (i == 0)		{
			ss = "Adjacency matrix";
			for (int j = 0; j < mmlist[i].size(); j++)			{
				ss += ",";
				ss += dlist.getRockList()[j];
			}
			ttss.prepend(ss);
		}
		ss = dlist.getRockList()[i];
		for (int j = 0; j < mmlist[i].size(); j++)		{
			ss += ",";
			int flag = 0;
			if (mmlist[i][j] > 0)
				flag = 1;
			ss += QString("%0").arg(flag);
		}
		ttss.prepend(ss);
	}
	str << ttss;
	BasicFun::write2Txt(namePath, str);
}