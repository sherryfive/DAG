#include "DAG.h"

#include "qfiledialog.h"


DrillSetHandle dlist;

void DAG::readboreholes(QString path)
{
	if (path == "")
		path = QFileDialog::getOpenFileName(NULL, "Select File", "", "*.csv");
    QStringList str = BasicFun::readFromTxt(path);
    if (str.size() == 0)
        return;

	QList<BDrill> pl;
	pl << BDrill();
    for (int i = 1; i < str.size(); i++)    {
		BDrillPoint p;
		if (!p.fromString(str[i]))
			continue;

		if (p.getName() != pl.last().getName())
			pl << BDrill(p.getName());

		pl.last().getDPset() << p;
	}

	int num = pl.size();
	for (int i = 0; i < num; i++)	{
		if (pl[i].size() == 0)		{
			pl.removeAt(i);
			i--;
			num--;
		}
	}
	for (int i = 0; i < num; i++)	{
		pl[i].computePoint();
	}
	for (int i = 0; i < num; i++)	{
		if (pl[i].size() == 0)		{
			pl.removeAt(i);
			i--;
			num--;
		}
	}
	if (pl.size() != 0)
		dlist = DrillSetHandle(pl);
}

void DAG::sortByTRG(){
    dlist.getCross_contact_matrix();
}

void DAG::generateGtable(){
    dlist.getDirectedGraph();
}
