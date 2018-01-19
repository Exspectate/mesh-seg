#ifndef _Point3d_H_
#define _Point3d_H_
#include "Util.h"
#include <math.h>
class Point3d {
public:
	double x, y, z;//×ø±ê
	double Cf;
	int color;
	bool isBad;
	bool isRidge;
	int idx;//Ë÷Òý
	Point3d();
	Point3d(double x, double y, double z);
	void setIdx(int a);
	bool operator== (const Point3d& pt) const;
	Point3d operator + (const Point3d &pt) const;
	Point3d operator - (const Point3d &pt) const;
	Point3d operator * (const double t) const;
	double len();
	bool operator < (const Point3d &a) const;
};
#endif