#ifndef _csy_Pitching_H_
#define _csy_Pitching_H_
#include "lty_STL.h"
#include "bsp_part.h"
#include "dijkstra.h"
class PitchR :public bsp_part {
public:
	vector<PII> RidgeLine;		//¸©Ñö¶æÉÏµÄÀâ±ß

public:
	void findRidgeLine(Mesh &mesh);
	void dfsFindBadLine(Mesh &mesh, int nowNode, int fa, vector<Point3d> &line, int endNode, set<PII> badEdgeSet);
	virtual void findFeatureLines(Mesh &mesh);


};
#endif;