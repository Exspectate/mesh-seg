#pragma once


#include "lty_STL.h"

typedef pair<int, int> PII;		//��ʾһ����

class ALLPART;




class bsp_part
{
public:
	vector<int> inVerts;		//ѡ�е�-int
	vector<int> inFacets;		//ѡ����Ƭ-int
	vector<PII> inbadEdge;		//����-PII
	vector<Point3d> featureVerts;	//�ؼ���
	vector<vector<Point3d> > featureLines;		//������
	int color;					//��ɫ-������ʾ
	ALLPART *belongTo;

public:
	bsp_part();
	virtual ~bsp_part();
	virtual void findfeatureLines(Mesh & mesh);	//��������
	virtual void findfeatureVerts(Mesh & mesh); //��������
	void initSelectData(Mesh & mesh, int color);	//��ʼ��

	void writeFeatureLinesToFile(string filePath);	//д�����ߵ��ļ���
	int findPartsPoint(Mesh &mesh, int color);
};

class PitchR;
class VRudder;
class bsp_Frame1;
class bsp_Frame2;
class bsp_Frame3;

class ALLPART {
public:
	PitchR* pitchRudder;		//������
	VRudder* leftVRudder;	//��V�Ͷ�
	VRudder* rightVRudder;	//��V�Ͷ�
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