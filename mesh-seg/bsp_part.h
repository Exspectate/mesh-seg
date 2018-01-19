#pragma once


#include "lty_STL.h"

typedef pair<int, int> PII;		//表示一个边

class ALLPART;




class bsp_part
{
public:
	vector<int> inVerts;		//选中点-int
	vector<int> inFacets;		//选中面片-int
	vector<PII> inbadEdge;		//坏边-PII
	vector<Point3d> featureVerts;	//关键点
	vector<vector<Point3d> > featureLines;		//特征线
	int color;					//颜色-部件标示
	ALLPART *belongTo;

public:
	bsp_part();
	virtual ~bsp_part();
	virtual void findfeatureLines(Mesh & mesh);	//找特征线
	virtual void findfeatureVerts(Mesh & mesh); //找特征点
	void initSelectData(Mesh & mesh, int color);	//初始化

	void writeFeatureLinesToFile(string filePath);	//写特征线到文件中
	int findPartsPoint(Mesh &mesh, int color);
};

class PitchR;
class VRudder;
class bsp_Frame1;
class bsp_Frame2;
class bsp_Frame3;

class ALLPART {
public:
	PitchR* pitchRudder;		//俯仰舵
	VRudder* leftVRudder;	//左V型舵
	VRudder* rightVRudder;	//右V型舵
	bsp_Frame1* f1;
	bsp_Frame2* f2;
	bsp_Frame3* f3;

public:
	ALLPART();
	~ALLPART();
	void initPartDATA(Mesh & mesh);
};

#include "bsp_Frame3.h"
#include "bsp_Frame2.h"
#include "bsp_Frame1.h"
#include "csy_Pitching.h"
#include "zc_VRudder.h"





struct P_L {
	double l;
	Point3d p;
	P_L(double l, Point3d p) { this->l = l; this->p = p; }
};


bool comppl(const P_L & a, const P_L & b);