#ifndef _zc_VRudder_H_
#define _zc_VRudder_H_
#include "bsp_part.h"
#include "gy_fitting.h"


class VRudder :public bsp_part {
public:
	vector<PII> RidgeLine;								//���潻��
	vector<pair<Point3d, Point3d> > tappedLine;			//ƽ���������
public:
	virtual void findFeatureLines(Mesh &mesh);
	void findRidgeLine(Mesh & mesh);
	void findPointDegree(vector<PII> Line, map<int, int> &ma);
	void dfsFindBadLine(Mesh &mesh, int nowNode, int fa, vector<Point3d> &line, int endNode, set<PII> badEdgeSet);
	int findDePoint(int startNode, int endNode, vector<Point3d> &Line);	//��ƫתС�Ƕȵ�
	int findRDePoint(int startNode, int endNode, vector<Point3d> &Line); //������С�Ƕȵ�
};
#endif;
