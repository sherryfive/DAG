#pragma once
#include "qdialog.h"
#include <QObject>
#include "QtCore/qmath.h"
#include "qstringlist.h"

#include "QVector3D"
#include "qstring.h"
#include "qlist.h"
#include "QVector"

#include "qfile.h"
#include "qtextstream.h"
#include "qlibrary.h"

#define def_EQUAL(a,b) abs(b-a)<0.001

#define def_EPLISEN 0.001

#define def_MAXVALUE 99999999999999.0
#define def_MINVALUE -9999999999999.0

#define def_MAX(x,y) x>y?x:y
#define def_MIN(x,y) x<y?x:y

#define def_QSTR_arg(s) QString("%0").arg(s)

#define def_rad2dec(r) r / 3.141592657 * 180.0
#define def_dec2rad(a) a / 180.0 * 3.141592657

class BasicFun
{
public:
	static void trans(int& a, int& b) { int c = a; a = b; b = c; }
	static void trans(double& a, double& b) { double c = a; a = b; b = c; }
	static void trans(QString& a, QString& b) { QString c = a; a = b; b = c; }

	static QStringList readFromTxt(QString path);
	static void write2Txt(QString path, QStringList str);

	static int getStrId(QString str, QStringList strlist);
	static int getValId(double str, QList<double> strlist);
	static int getValId(int str, QList<int> strlist);

	static QString getstrFromList(QList<int> vlist);

	static int getMinValueId(QList<double> vlist);
	static int getMaxValueId(QList<double> vlist);

	static int getMinValueId(QList<int> vlist);
	static int getMaxValueId(QList<int> vlist);

	static void validValue(double& vv, double minv, double maxv);

	static bool addRock(QString oldrock, QString newrock, QStringList& rockList);

	static void schmidtOrthogonal(QVector3D& v0, QVector3D& v1, QVector3D& v2);
	static void VomputeLenth(QVector3D& position, QList<QVector3D> pVertices, QVector3D* eVectors, QVector3D& halfExtents);
};
