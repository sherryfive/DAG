#include "BObb.h"

BObb::BObb(){
	halflen = Bvector();
	cenpoint = Bvector();
	vectors.append(Bvector(0, 0, 1));
	vectors.append(Bvector(0, 1, 0));
	vectors.append(Bvector(1, 0, 0));
	plist = BPointSet();
	dis = 0;
	num = 0;
}

BObb::BObb(BPointSet p){
	*this = BObb();
	plist = p;
	num = p.size();
}

BObb::BObb(const BObb& p){
	halflen = p.halflen;
	cenpoint = p.cenpoint;
	vectors = p.vectors;
	dis = p.dis;
	plist = p.plist;
	num = p.num;
}

void BObb::sortVectorLen(){
	for (int i = 1; i < 3; i++)	{
		if (halflen[0] > halflen[i])		{
			double thalf = halflen[0];
			Bvector tvec = vectors[0];

			halflen[0] = halflen[i];
			vectors[0] = vectors[i];

			halflen[i] = thalf;
			vectors[i] = tvec;
		}
	}
	if (halflen[1] > halflen[2])	{
		double thalf = halflen[1];
		Bvector tvec = vectors[1];

		halflen[1] = halflen[2];
		vectors[1] = vectors[2];

		halflen[2] = thalf;
		vectors[2] = tvec;
	}
}

bool BObb::compute(){
	if (plist.size() == 0)
		return false;

	QVector3D pos, half;
	QVector3D* vv = new QVector3D[3];
	for (int i = 0; i < 3; i++)
		vv[i] = QVector3D();
	PCL::ComputePlaneNormalByPCA(plist.getQv3dList(), pos, half, vv);

	halflen = Bvector(half);
	cenpoint = Bvector(pos);

	for (int i = 0; i < 3; i++)
		vectors[i] = Bvector(vv[i]);

	sortVectorLen();
	return true;
}
