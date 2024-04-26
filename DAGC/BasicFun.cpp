#include "BasicFun.h"

QStringList BasicFun::readFromTxt(QString path){	
	QStringList cons;
	if (path == "")	
		return cons;
	QFile mfiledtm0(path);
	if (!mfiledtm0.open(QIODevice::ReadOnly | QIODevice::Text))
		return cons;

	QTextStream mRead0(&mfiledtm0);
	while (!mRead0.atEnd())	{
		QString ss = mRead0.readLine().toUtf8();
		if (ss.isEmpty())			continue;
		if (ss.isNull())			continue;
		if (ss == "" || ss.split(" ").size() == 0) continue;
		cons << ss;
	}
	mfiledtm0.close();
	return cons;
}

void BasicFun::write2Txt(QString path, QStringList str){
	if (path=="")	
		return;
	QFile mfile(path);
	if (mfile.open(QIODevice::WriteOnly | QIODevice::Text))	{
		QTextStream mout(&mfile);
		for each (QString t in str)		{
			mout << t << "\n";
		}
		mfile.close();
	}
}


int BasicFun::getStrId(QString str, QStringList strlist){
	for (int i = 0; i < strlist.size(); i++)	{
		if (strlist[i] == str)		{
			return i;
		}
	}
	return -1;
}

int BasicFun::getValId(double str, QList<double> strlist){
	for (int i = 0; i < strlist.size(); i++)	{
		if (strlist[i] == str)		{
			return i;
		}
	}
	return -1;
}

int BasicFun::getValId(int str, QList<int> strlist){
	for (int i = 0; i < strlist.size(); i++)	{
		if (strlist[i] == str)		{
			return i;
		}
	}
	return -1;
}

QString BasicFun::getstrFromList(QList<int> vlist){
	QString ss;
	if (vlist.size() > 0)
		ss = def_QSTR_arg(vlist.first());
	for (int i = 1; i < vlist.size(); i++)	{
		ss += "," + def_QSTR_arg(vlist[i]);
	}
	return ss;
}

int BasicFun::getMinValueId(QList<double> vlist){
	double vv = def_MAXVALUE;
	int flag = -1;
	for (int i = 0; i < vlist.size(); i++)	{
		if (vlist[i] < vv)		{
			vv = vlist[i];
			flag = i;
		}
	}
	return flag;
}

int BasicFun::getMaxValueId(QList<double> vlist){
	double vv = def_MINVALUE;
	int flag = -1;
	for (int i = 0; i < vlist.size(); i++)	{
		if (vlist[i] > vv)		{
			vv = vlist[i];
			flag = i;
		}
	}
	return flag;
}

int BasicFun::getMinValueId(QList<int> vlist){
	int vv = def_MAXVALUE;
	int flag = -1;
	for (int i = 0; i < vlist.size(); i++)	{
		if (vlist[i] < vv)		{
			vv = vlist[i];
			flag = i;
		}
	}
	return flag;
}

int BasicFun::getMaxValueId(QList<int> vlist){
	int vv = def_MINVALUE;
	int flag = -1;
	for (int i = 0; i < vlist.size(); i++)	{
		if (vlist[i] > vv)		{
			vv = vlist[i];
			flag = i;
		}
	}
	return flag;
}

void BasicFun::validValue(double& vv, double minv, double maxv){
	double dd = maxv - minv;
	for (;;)	{
		if (vv > maxv)
			vv -= dd;
		else if (vv < minv)
			vv += dd;
		else
			break;
	}
}

bool BasicFun::addRock(QString oldrock, QString newrock, QStringList& rockList){
	bool flag = true;

	bool isExistTT = false;
	int indexChTT = -1;
	if (oldrock != "")	{
		int numTT = rockList.size();
		for (int K = 0; K < numTT; K++)		{
			if (rockList[K] == oldrock)			{
				isExistTT = true;
				indexChTT = K;
				break;
			}
		}
	}

	bool isExist = false;
	int indexCh = -1;
	int num = rockList.size();
	for (int i = 0; i < num; i++)	{
		if (rockList[i] == newrock)		{
			isExist = true;
			indexCh = i;
			break;
		}
	}

	if (isExist == false)	{
		if (isExistTT == false)
			rockList.append(newrock);
		else
			rockList.insert(indexChTT + 1, newrock);
		return true;
	}
	else	{
		if (indexChTT > indexCh)		{
			rockList.insert(indexChTT + 1, newrock);
			rockList.removeAt(indexCh);
		}
		return true;
	}
}


void BasicFun::schmidtOrthogonal(QVector3D& v0, QVector3D& v1, QVector3D& v2){
	v2.normalize();
	v0 -= v2 * QVector3D::dotProduct(v2, v0);
	v0.normalize();
	v1 -= v0 * QVector3D::dotProduct(v0, v1) + v2 * QVector3D::dotProduct(v2, v1);
	v1.normalize();
}

void BasicFun::VomputeLenth(QVector3D& position, QList<QVector3D> pVertices, QVector3D* orientation, QVector3D& halfExtents){
	float infinity = -1.40129846432481707e-45f;
	QVector3D minExtents = QVector3D(infinity, infinity, infinity);
	QVector3D maxExtents = QVector3D(-infinity, -infinity, -infinity);

	for (int index = 0; index < pVertices.size(); index++)	{
		QVector3D vec = pVertices[index];
		QVector3D displacement = vec - position;

		for (int i = 0; i < 3; i++)		{
			minExtents[i] = minExtents[i] < QVector3D::dotProduct(displacement, orientation[i]) ?
				minExtents[i] : QVector3D::dotProduct(displacement, orientation[i]);
			maxExtents[i] = maxExtents[i] > QVector3D::dotProduct(displacement, orientation[i]) ?
				maxExtents[i] : QVector3D::dotProduct(displacement, orientation[i]);
		}
	}

	QVector3D offset = maxExtents - minExtents;
	offset = offset / 2.0f;
	offset = offset + minExtents;

	for (int i = 0; i < 3; i++)
		position += orientation[i] * offset[i];
	halfExtents = (maxExtents - minExtents) / 2.0f;
}

