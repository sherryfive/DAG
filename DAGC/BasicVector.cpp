#include "BasicVector.h"

Bvector::Bvector(double dec_qinxiang, double dec_qinjiao){
	*this = Bvector();
	BasicFun::validValue(dec_qinxiang, 0, 360);
	BasicFun::validValue(dec_qinjiao, -90, 90);
	vecx = vecy = vecz = 0;
	if (def_EQUAL(dec_qinjiao, 90))	{
		vecz = 1;
		return;
	}
	if (def_EQUAL(dec_qinjiao, -90))	{
		vecz = -1;
		return;
	}
	dec_qinxiang = def_dec2rad(dec_qinxiang);
	dec_qinjiao = def_dec2rad(dec_qinjiao);

	vecx = sin(dec_qinxiang);
	vecy = cos(dec_qinxiang);
	vecz = 0;
	normalized();
	vecz = tan(dec_qinjiao);
	normalized();
}

Bvector Bvector::normalized(void){
	double d = length();
	if (def_EQUAL(d, def_EPLISEN))
		return *this;
	return operator * (1.0f / d);
}

double Bvector::getMinXYZ(){
	if (vecx <= vecy && vecx <= vecz)	return vecx;
	if (vecy <= vecx && vecy <= vecz)	return vecy;
	if (vecz <= vecx && vecz <= vecy)	return vecz;
}
