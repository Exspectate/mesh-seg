#include "csy_Pitching.h"

typedef pair<int,double> PAIR;
bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
	return lhs.second < rhs.second;
}

void PitchR::findRidgeLine(Mesh & mesh)
{
	RidgeLine.clear();
	map<PII, bool> vis;			//边是否被访问
	map<PII, PII> eage;			//边及其相邻面片的关系
	map<PII, int> ma;
	for (int i = 0; i < inFacets.size(); ++i) {
		PII a, b, c;
		a.first = c.second = mesh.Facets[inFacets[i]].vertIdx[0];
		a.second = b.first = mesh.Facets[inFacets[i]].vertIdx[1];
		b.second = c.first = mesh.Facets[inFacets[i]].vertIdx[2];
		if (a.first>a.second)
			swap(a.first, a.second);
		if (b.first>b.second)
			swap(b.first, b.second);
		if (c.first>c.second)
			swap(c.first, c.second);
		if (!vis[a]) {
			vis[a] = 1;
			eage[a].first = inFacets[i];
			if (!vis[b]) {
				vis[b] = 1;
				eage[b].first = inFacets[i];
				if (!vis[c]) {
					vis[c] = 1;
					eage[c].first = inFacets[i];
				}
				else
					eage[c].second = inFacets[i];
			}
			else {
				eage[b].second = inFacets[i];
				if (!vis[c]) {
					vis[c] = 1;
					eage[c].first = inFacets[i];
				}
				else
					eage[c].second = inFacets[i];
			}
		}
		else {
			eage[a].second = inFacets[i];
			if (!vis[b]) {
				vis[b] = 1;
				eage[b].first = inFacets[i];
				if (!vis[c]) {
					vis[c] = 1;
					eage[c].first = inFacets[i];
				}
				else
					eage[c].second = inFacets[i];
			}
			else {
				eage[b].second = inFacets[i];
				if (!vis[c]) {
					vis[c] = 1;
					eage[c].first = inFacets[i];
				}
				else
					eage[c].second = inFacets[i];
			}
		}
		ma[a]++;
		ma[b]++;
		ma[c]++;
	}
	for (map<PII, PII>::iterator it = eage.begin(); it != eage.end(); it++) {
		if (ma[it->first] == 1)
			continue;
		Vector13 norm1, norm2;		//相邻面片法向量
		norm1 = mesh.Facets[it->second.first].normV;
		norm2 = mesh.Facets[it->second.second].normV;
		if (norm1.dot(norm2) / norm1.len() / norm2.len() > 0.70711)
			continue;
		else {
			RidgeLine.push_back(it->first);
			mesh.Verts[it->first.first].isRidge = true;
			mesh.Verts[it->first.second].isRidge = true;
		}
			
	}
}

void PitchR::dfsFindBadLine(Mesh & mesh, int nowNode, int fa, vector<Point3d>& line, int endNode, set<PII> badEdgeSet)
{
	line.push_back(mesh.Verts[nowNode]);
	if (nowNode == endNode)
		return;
	if (endNode == -1)
		endNode = nowNode;
	for (int i = 0; i<mesh.adjVert[nowNode].size(); i++)
	{
		int adj = mesh.adjVert[nowNode][i];
		if (adj == fa)
			continue;
		/*if (!(mesh.Verts[adj].isBad))
			continue;*/
		if (!(mesh.Verts[adj].isBad)&&!(mesh.Verts[adj].isRidge))
			continue;
		PII pii = make_pair(nowNode, adj);
		if (pii.first>pii.second)
			swap(pii.first, pii.second);
		if (!(badEdgeSet.count(pii)))
			continue;
		//存疑 是否只有一个
		dfsFindBadLine(mesh, adj, nowNode, line, endNode, badEdgeSet);
		break;
	}
}


void PitchR::findFeatureLines(Mesh &mesh)
{
	int featureLinesNum = 12; //特征线个数
	featureLines.clear();
	featureLines.resize(featureLinesNum);
	this->findRidgeLine(mesh);

	//底面上4个点 0 1 2 3
	vector<Point3d> tempLine1;			//坏边的有序边集
	int keyPoint1[4];					//底面四个关键点 有序 存储对应tempLine1中的序号
	memset(keyPoint1, -1, sizeof(keyPoint1));
	tempLine1.clear();
	set<PII> badEdgeSet;
	for (int i = 0; i<inbadEdge.size(); i++)
		badEdgeSet.insert(inbadEdge[i]);
	dfsFindBadLine(mesh, inbadEdge[0].first, -1, tempLine1, -1, badEdgeSet);//坏边上的所有点的集合
	int now = 0;
	for (int i = 0; i + 1 < tempLine1.size(); ++i) {
		//找出底边上的4个拐点
		Point3d p1, p2, p3;
		if (i == 0)
			p1 = tempLine1[tempLine1.size() - 2];
		else
			p1 = tempLine1[i - 1];
		p2 = tempLine1[i];
		p3 = tempLine1[i + 1];
		Point3d pv1, pv2;
		pv1 = p2 - p1;
		pv2 = p3 - p2;
		double cos12 = dot(pv1, pv2) / pv1.len() / pv2.len();
		if (cos12>0.70711)//cos(pi/4)
			continue;
		keyPoint1[now++] = i;
	}
	//区分底面4个点的顺序
	int LeftVPoint = findPartsPoint(mesh,mesh.kind_color[5]);		//左V型舵上某一点
	int HeadPoint = findPartsPoint(mesh, mesh.kind_color[1]);		//头部某一点
	vector<PAIR> pL;
	vector<PAIR> pH;
	for (int i = 0; i < 4; ++i) {
		Point3d v1, v2, v3;
		v1 = tempLine1[keyPoint1[i]];
		v2 = mesh.Verts[LeftVPoint];
		PAIR temp;
		temp.first = keyPoint1[i];
		temp.second = (v1 - v2).len();
		pL.push_back(temp);
	}
	sort(pL.begin(), pL.end(), cmp_by_value);
	for (int i = 0; i < 4; ++i) {
		keyPoint1[i] = pL[i].first;
	}
	Point3d v1= mesh.Verts[HeadPoint];
	if ((tempLine1[keyPoint1[0]] - v1).len() < (tempLine1[keyPoint1[1]] - v1).len()) 
		swap(keyPoint1[0], keyPoint1[1]);
	if ((tempLine1[keyPoint1[3]] - v1).len() < (tempLine1[keyPoint1[2]] - v1).len())
		swap(keyPoint1[3], keyPoint1[2]);

	//find line 2 4 1 3
//	cout << "*****点数" << tempLine1.size()<<endl;
	for (int i = keyPoint1[1]; i <= tempLine1.size(); i++) {
		if(i<tempLine1.size())
			featureLines[1].push_back(tempLine1[i]);
		else
			featureLines[1].push_back(tempLine1[keyPoint1[0]]);
	}
	for (int i = keyPoint1[2]; i <= keyPoint1[1]; i++)
		featureLines[3].push_back(tempLine1[i]);
	for (int i = keyPoint1[3]; i <= keyPoint1[2]; i++)
		featureLines[0].push_back(tempLine1[i]);
	for (int i = keyPoint1[0]; i <= keyPoint1[3]; i++)
		featureLines[2].push_back(tempLine1[i]);


	
	//找靠上方的4个关键点
	int keyRidge[4];		//底面4个点对应棱上顶点的位置 
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < RidgeLine.size(); ++j) {
			if (tempLine1[keyPoint1[i]] == mesh.Verts[RidgeLine[j].first]) {
				keyRidge[i] = RidgeLine[j].first; break;
			}
			if (tempLine1[keyPoint1[i]] == mesh.Verts[RidgeLine[j].second]) {
				keyRidge[i] = RidgeLine[j].second; break;
			}
		}
	}
	//上方4个关键点
	map<int, int> RidgeDegree;		//棱上点度数
	for (int i = 0; i < this->RidgeLine.size(); ++i) {
		RidgeDegree[this->RidgeLine[i].first]++;
		RidgeDegree[this->RidgeLine[i].second]++;
	}
	int keyPoint2[4];				//关键点无序
	int keyPointUp[4];				//7，6，5，4关键点 有序 存储对应mesh中点的标号
	int temp[4];
	memset(temp, 0, sizeof(temp));
	now = 0;
	vector<Point3d> UpLine[7];		//上方的8条线
	for (map<int, int>::iterator it = RidgeDegree.begin(); it != RidgeDegree.end(); it++) {
		if (it->second == 3)
			//在棱上度数为3的点是上方4个关键点
			keyPoint2[now++] = it->first;
	}
	vector<PAIR> distanceToUp[4];			//根据上方4个点到下方4个点的距离区分出上方4个点的顺序
											//得到有序的4个关键点
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			distanceToUp[i].push_back(make_pair(j, (tempLine1[keyPoint1[i]] - mesh.Verts[keyPoint2[j]]).len()));
			//distanceToUp[i].push_back((tempLine1[keyPoint1[i]]-mesh.Verts[keyPoint2[j]]).len);
		}
		sort(distanceToUp[i].begin(),distanceToUp[i].end(), cmp_by_value);
		//cout << distanceToUp[i][0].first << endl;
		keyPointUp[i] = keyPoint2[distanceToUp[i][0].first];
	}
	set<PII> RidgeEdgeSet;
	for (int i = 0; i<RidgeLine.size(); i++)
		RidgeEdgeSet.insert(RidgeLine[i]);
	//find line 6 8 7 5
	for (int i = 0; i < 4; ++i) {
		//从底面上的点沿棱边向上方的点做dfs找到侧棱上的线
		dfsFindBadLine(mesh, keyRidge[i], -1, UpLine[i], keyPointUp[i], RidgeEdgeSet);
	}
	for (int i = 0; i < UpLine[0].size(); ++i)
		featureLines[5].push_back(UpLine[0][i]);
	for (int i = 0; i < UpLine[1].size(); ++i)
		featureLines[7].push_back(UpLine[1][i]);
	for (int i = 0; i < UpLine[2].size(); ++i)
		featureLines[6].push_back(UpLine[2][i]);
	for (int i = 0; i < UpLine[3].size(); ++i)
		featureLines[4].push_back(UpLine[3][i]);

	//find 9 10 11 12
	//用上方的4个关键点沿坏边做最短路径找到上方4条边
	int LinePos[4] = { 10,12,9,11 };
	map<int, int> id_node;
	int nodeid=0;
	for (map<int, int>::iterator it = RidgeDegree.begin(); it != RidgeDegree.end(); it++) {
		id_node[it->first] = nodeid++;
	}
	Dijkstra dij;
	dij.init(RidgeDegree.size());
	for (int i = 0; i < RidgeLine.size(); ++i) {
		dij.add(id_node[RidgeLine[i].first],id_node[RidgeLine[i].second],1);
	}
	for (int i = 0; i < 4; ++i) {
		int startNode = id_node[keyPointUp[i%4]];
		int endNode = id_node[keyPointUp[(i + 1)%4]];
		dij.work(startNode);
		while (dij.getFather(endNode) != startNode) {
			auto find_item = find_if(id_node.begin(), id_node.end(),
				[endNode](const map<int, int>::value_type item)
			{
				return item.second == endNode;
			});
			if (find_item != id_node.end())
			{
				featureLines[LinePos[i]-1].push_back(mesh.Verts[(*find_item).first]);
			}
			endNode = dij.getFather(endNode);
		}
		auto find_item = find_if(id_node.begin(), id_node.end(),
			[startNode](const map<int, int>::value_type item)
		{
			return item.second == startNode;
		});
		if (find_item != id_node.end())
		{
			featureLines[LinePos[i] - 1].push_back(mesh.Verts[(*find_item).first]);
		}
	}
	featureVerts.clear();		//存储特征点
	featureVerts.resize(8);
	for (int i = 0; i < 8; ++i) {
		if (i < 4)
			featureVerts[i] = mesh.Verts[keyRidge[i]];
		else
			featureVerts[i] = mesh.Verts[keyPointUp[7-i]];
		//cout << featureVerts[i] << endl;
	}
}




