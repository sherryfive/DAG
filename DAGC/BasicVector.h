#pragma once

#include "BasicFun.h"
class Bvector 
{
public:
	Bvector(){	vecx = 0;	vecy = 0;	vecz = 0;}
	Bvector(QVector3D p){*this = Bvector();	vecx = p[0];	vecy = p[1];	vecz = p[2];}
	Bvector(double xpos, double ypos, double zpos){	*this = Bvector();	vecx = xpos;	vecy = ypos;	vecz = zpos;}	
	Bvector(const Bvector& p){	vecx = p.vecx;	vecy = p.vecy;	vecz = p.vecz;}
	Bvector(double dec_qinxiang, double dec_qinjiao);
	
	inline Bvector& operator += (Bvector  v){	vecx += v[0];	vecy += v[1];	vecz += v[2];	return *this;}
	inline Bvector operator + (Bvector  v) { return Bvector(vecx + v[0], vecy + v[1], vecz + v[2]);}
	inline Bvector operator - (Bvector  v) { return Bvector(vecx - v[0], vecy - v[1], vecz - v[2]);}
	inline Bvector operator * (double d)	{ return Bvector(vecx * d, vecy * d, vecz * d);}
	inline Bvector operator / (double d)	{ if (def_EQUAL(d, def_EPLISEN))			return Bvector();		return operator * (1.0f / d);}
	inline double& operator [] (int i)	{	if (i == 0)	return vecx;	if (i == 1)	return vecy;	if (i == 2)	return vecz;}

	inline QVector3D toQvector3D() { return QVector3D(vecx, vecy, vecz); }
	inline double length(void)	{	return sqrt(sqrLength());	}
	inline double sqrLength(void)	{	return vecx * vecx + vecy * vecy + vecz * vecz;	}
	inline double dot(Bvector  v)	{	return vecx * v[0] + vecy * v[1] + vecz * v[2];	}

	Bvector normalized(void);
	double getMinXYZ();
protected:
private:
	double vecx, vecy, vecz;
};
