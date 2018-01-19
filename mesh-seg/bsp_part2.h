#pragma once


#include "lty_STL.h"
typedef pair<int, int> PII;
class ALLPART;
class bsp_part
{
public:
	vector<int> inVerts;		//选中点-int
	vector<int> inFacets;		//选中面片-int
	vector<PII> inbadEdge;		//坏边-PII
	vector<Point3d> featureVerts;	//关键点
	vector<vector<Point3d> > featureLines;		//特征线
	int color;					//部件标识
	ALLPART *belongTo;
public:
	bsp_part();
	//bsp_part(Mesh &mesh);
	virtual ~bsp_part();
	virtual void findFeatureLines(Mesh &mesh);
	void initSelectData(Mesh &mesh,int color);
	void writeFeatureLinesToFile(string filePath);	//写特征线到文件中
	int findPartsPoint(Mesh &mesh, int color);
};

