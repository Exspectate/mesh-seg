#include "gy_show.h"
#include "dijkstra.h"
#include <glut.h>
static const int COLOR1[19] = { 255,255,255,  0,141, 23, 66,255,139,255,139,139,255,139,139,255,255 };
static const int COLOR2[19] = { 255,  0,117,  0, 75,248, 80,129,0  ,101,58 ,69 ,137,0  ,228,250,0 };
static const int COLOR3[19] = { 255,151,  0,255,187,203,102,  0,76 ,0  ,8  ,58 ,0  ,137,0  ,225,205,255 };
static const double PI = 3.1415926535;
static const int MAX = 20;
static int du = 90, OriX = -500, OriY = -50;   //du���ӵ��x��ļн�
static float r = 1000, h = 0;   //r���ӵ���y��İ뾶��h���ӵ�߶ȼ���y���ϵ�����
static float c = PI / 180.0;    //���ȺͽǶ�ת������
static float times = 1;			//�Ŵ���С����

static float oldx = 0;					//����任������
static float oldy = 0;

static int cx = 0;					//����������
static int cy = 0;

static Dijkstra dija;
static vector<vector<Point3d> >regionPt;
static int regionCount;

static int bfs(int node, int color, Mesh &mesh)
{
	int ret = 0;
	queue<int> que;
	que.push(node);
	while (!que.empty())
	{
		int tmp = que.front();
		que.pop();
		if (mesh.Verts[tmp].color != 0)
			continue;
		mesh.Verts[tmp].color = color;
		++ret;
		for (int i = 0; i<mesh.adjVert[tmp].size(); i++)
			if (mesh.Verts[mesh.adjVert[tmp][i]].color == 0)
				que.push(mesh.adjVert[tmp][i]);

	}
	return ret;
}

static int reBfs(int node, Mesh &mesh) {  //�����������ɫ���Ϊ0
	int ret = 0;
	queue<int> que;
	que.push(node);
	while (!que.empty())
	{
		int tmp = que.front();
		que.pop();
		if (mesh.Verts[tmp].color <= 0)
			continue;
		mesh.Verts[tmp].color = 0;
		++ret;
		for (int i = 0; i<mesh.adjVert[tmp].size(); i++)
			if (mesh.Verts[mesh.adjVert[tmp][i]].color > 0)
				que.push(mesh.adjVert[tmp][i]);

	}
	return ret;
}

static void setColor(Mesh &mesh)
{
	int nowColor = 0;
	for (int i = 0; i<mesh.Verts.size(); i++)
	{
		if (mesh.Verts[i].color == 0)
		{
			nowColor++;
			int ret = bfs(i, nowColor, mesh);
			cout << "����:" << ret << "\n";
		}
	}

	cout << "����:" << nowColor << endl;
}

void InitMesh(Mesh& mdata) {
	cout << "Calculating adjacent facets" << endl;
	mdata.CaladjFacet();//�����������ڽ���Ƭ
	cout << "Calculating adjacent vertexes" << endl;
	mdata.CaladjVert();//�����������ڽӵ�
	cout << "Calculating normal vector for vertexes" << endl;
	mdata.Calvertnorm();//���������ķ�����
	CalCf(mdata);//���������İ�͹�ź�
				 //sort(mdata.Cf.begin(), mdata.Cf.end(), cmp); //����
}

