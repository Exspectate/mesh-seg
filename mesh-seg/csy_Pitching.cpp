#include "csy_Pitching.h"

typedef pair<int,double> PAIR;
bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
	return lhs.second < rhs.second;
}

void PitchR::findRidgeLine(Mesh & mesh)
{
	RidgeLine.clear();
	map<PII, bool> vis;			//���Ƿ񱻷���
	map<PII, PII> eage;			//�߼���������Ƭ�Ĺ�ϵ
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
		Vector13 norm1, norm2;		//������Ƭ������
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
		//���� �Ƿ�ֻ��һ��
		dfsFindBadLine(mesh, adj, nowNode, line, endNode, badEdgeSet);
		break;
	}
}


void PitchR::findFeatureLines(Mesh &mesh)
{
	int featureLinesNum = 12; //�����߸���
	featureLines.clear();
	featureLines.resize(featureLinesNum);
	this->findRidgeLine(mesh);

	//������4���� 0 1 2 3
	vector<Point3d> tempLine1;			//���ߵ�����߼�
	int keyPoint1[4];					//�����ĸ��ؼ��� ���� �洢��ӦtempLine1�е����
	memset(keyPoint1, -1, sizeof(keyPoint1));
	tempLine1.clear();
	set<PII> badEdgeSet;
	for (int i = 0; i<inbadEdge.size(); i++)
		badEdgeSet.insert(inbadEdge[i]);
	dfsFindBadLine(mesh, inbadEdge[0].first, -1, tempLine1, -1, badEdgeSet);//�����ϵ����е�ļ���
	int now = 0;
	for (int i = 0; i + 1 < tempLine1.size(); ++i) {
		//�ҳ��ױ��ϵ�4���յ�
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
	//���ֵ���4�����˳��
	int LeftVPoint = findPartsPoint(mesh,mesh.kind_color[5]);		//��V�Ͷ���ĳһ��
	int HeadPoint = findPartsPoint(mesh, mesh.kind_color[1]);		//ͷ��ĳһ��
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
//	cout << "*****����" << tempLine1.size()<<endl;
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


	
	//�ҿ��Ϸ���4���ؼ���
	int keyRidge[4];		//����4�����Ӧ���϶����λ�� 
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
	//�Ϸ�4���ؼ���
	map<int, int> RidgeDegree;		//���ϵ����
	for (int i = 0; i < this->RidgeLine.size(); ++i) {
		RidgeDegree[this->RidgeLine[i].first]++;
		RidgeDegree[this->RidgeLine[i].second]++;
	}
	int keyPoint2[4];				//�ؼ�������
	int keyPointUp[4];				//7��6��5��4�ؼ��� ���� �洢��Ӧmesh�е�ı��
	int temp[4];
	memset(temp, 0, sizeof(temp));
	now = 0;
	vector<Point3d> UpLine[7];		//�Ϸ���8����
	for (map<int, int>::iterator it = RidgeDegree.begin(); it != RidgeDegree.end(); it++) {
		if (it->second == 3)
			//�����϶���Ϊ3�ĵ����Ϸ�4���ؼ���
			keyPoint2[now++] = it->first;
	}
	vector<PAIR> distanceToUp[4];			//�����Ϸ�4���㵽�·�4����ľ������ֳ��Ϸ�4�����˳��
											//�õ������4���ؼ���
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
		//�ӵ����ϵĵ���������Ϸ��ĵ���dfs�ҵ������ϵ���
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
	//���Ϸ���4���ؼ����ػ��������·���ҵ��Ϸ�4����
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
	featureVerts.clear();		//�洢������
	featureVerts.resize(8);
	for (int i = 0; i < 8; ++i) {
		if (i < 4)
			featureVerts[i] = mesh.Verts[keyRidge[i]];
		else
			featureVerts[i] = mesh.Verts[keyPointUp[7-i]];
		//cout << featureVerts[i] << endl;
	}
}




