#include "BasicPoint.h"

QList<QVector3D> BPointSet::getQv3dList(){
	QList<QVector3D> qq;
	for each (BPoint var in plist)
		qq << var[0].toQvector3D();
	return qq;
}
