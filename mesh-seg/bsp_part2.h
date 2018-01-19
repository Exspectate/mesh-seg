#pragma once


#include "lty_STL.h"
typedef pair<int, int> PII;
class ALLPART;
class bsp_part
{
public:
	vector<int> inVerts;		//ѡ�е�-int
	vector<int> inFacets;		//ѡ����Ƭ-int
	vector<PII> inbadEdge;		//����-PII
	vector<Point3d> featureVerts;	//�ؼ���
	vector<vector<Point3d> > featureLines;		//������
	int color;					//������ʶ
	ALLPART *belongTo;
public:
	bsp_part();
	//bsp_part(Mesh &mesh);
	virtual ~bsp_part();
	virtual void findFeatureLines(Mesh &mesh);
	void initSelectData(Mesh &mesh,int color);
	void writeFeatureLinesToFile(string filePath);	//д�����ߵ��ļ���
	int findPartsPoint(Mesh &mesh, int color);
};

