#include "gy_show.h"
#include "dijkstra.h"
#include <glut.h>
static const int COLOR1[19] = { 255,255,255,  0,141, 23, 66,255,139,255,139,139,255,139,139,255,255 };
static const int COLOR2[19] = { 255,  0,117,  0, 75,248, 80,129,0  ,101,58 ,69 ,137,0  ,228,250,0 };
static const int COLOR3[19] = { 255,151,  0,255,187,203,102,  0,76 ,0  ,8  ,58 ,0  ,137,0  ,225,205,255 };
static const double PI = 3.1415926535;
static const int MAX = 20;
static int du = 90, OriX = -500, OriY = -50;   //du是视点和x轴的夹角
static float r = 1000, h = 0;   //r是视点绕y轴的半径，h是视点高度即在y轴上的坐标
static float c = PI / 180.0;    //弧度和角度转换参数
static float times = 1;			//放大缩小倍数

static float oldx = 0;					//矩阵变换的坐标
static float oldy = 0;

static int cx = 0;					//交叉点的坐标
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

static int reBfs(int node, Mesh &mesh) {  //将本区域点颜色标记为0
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
			cout << "点数:" << ret << "\n";
		}
	}

	cout << "块数:" << nowColor << endl;
}

void InitMesh(Mesh& mdata) {
	cout << "Calculating adjacent facets" << endl;
	mdata.CaladjFacet();//计算各顶点的邻接面片
	cout << "Calculating adjacent vertexes" << endl;
	mdata.CaladjVert();//计算各顶点的邻接点
	cout << "Calculating normal vector for vertexes" << endl;
	mdata.Calvertnorm();//计算各顶点的法向量
	CalCf(mdata);//计算各顶点的凹凸信号
				 //sort(mdata.Cf.begin(), mdata.Cf.end(), cmp); //升序
}

