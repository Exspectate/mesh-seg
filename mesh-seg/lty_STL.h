#ifndef _lty_STL_H_
#define _lty_STL_H_

#include <fstream>
#include <iomanip>  
#include <vector>
#include <string>
#include <Eigen/Eigen>
#include <algorithm>
#include <set>
#include <map>
#include <iostream>
#include "Point3d.h"
#include "Util.h"
#include "dijkstra.h"
#include "3dOperator.h"


#pragma warning(disable:4996)

using namespace std;
using namespace Eigen;



typedef Eigen::Triplet<double> T;

struct Vector13 { //1x3����
public:
	double x, y, z;
	Vector13();
	~Vector13();
	Vector13(double x, double y, double z);
	double dot(const Vector13 &t);
    Vector13 crossmult(const Vector13 &t);
    double getcos(const Vector13 &t);
    double len();
};

class TriFacet { //������Ƭ
public:
	//int nEdges=3;
	vector<int> vertIdx;//������������
	vector<int> edgeIdx;//����������
	Vector13 normV;//������
	int idx;//����
	TriFacet();
	~TriFacet();
	void addVertIdx(int a);
	void setnormV(Vector13 nv);
	void setIdx(int a);
};

class Edge {
public:
	int a,b;//���˵�����
	int adj1, adj2;//���ڽ���Ƭ����
	int idx;
	Edge();
	Edge(int a, int b, int idx);
	void setFacetidx(int adj1, int adj2);
};

struct VtCf {
	double Cf;
	int idx;
	VtCf(double Cf, int idx);
};

class Mesh {   //����ģ��
public:
	vector<Point3d> Verts;
	vector<TriFacet> Facets;
	vector<Edge> Edges;
	vector< vector<int> > adjVert;//������ڽӶ���������
	vector< vector<int> > adjFacet;//������ڽ���Ƭ������
	vector<Vector13> vertnorm;//����ķ�������
	vector< VtCf > Cf;//����İ�͹�ź�
	vector<int> badPointsId; //����id����

	map<int, int> kind_color;

	void CaladjVert();//�����������ڽӶ���
	void CaladjFacet();//�����������ڽ���Ƭ
	void Calvertnorm();//���������ķ�����
	void Calfacetnorm();//�����������Ƭ�ķ�����
	void AddVertex(Point3d& pts);//��Ӷ���
	void AddFacet(TriFacet& facets);//�����Ƭ
	void clear();					//�����
};

SparseMatrix<double> CalLapMatrix(Mesh& mesh);

//���������İ�͹��
void CalCf(Mesh& mesh);

bool cmp(VtCf& a, VtCf& b);

//��vector<int>�а�ֵɾ��Ԫ��
void delvec(vector<int> &vec, int value);


//��ASCII��STL�ļ��ж�ȡ����
void readASCIstl(const char* filename, Mesh& mdata);

//д���ݵ�ASCII��STL�ļ�
void writeASCIstl(char* filename, vector<Point3d> &Verts, vector<TriFacet> &Facets);

void writeASCIstltest(char* filename, vector<Point3d> &Verts);

void adjFacetForEdge(Edge &e, Mesh &mesh);//����һ���ߵ��ڽ���Ƭ,�������Ƭ����Ӹñߵ���Ϣ

//�ж�һ�����Ƿ��ڰ�����߽�   
bool isBoundaryEdge(Edge &e, Mesh &mesh, vector<int> &concavesigne, int num);

//ȥ���ߺ�����µı�
void addnewboundEdges(list<int> &list, Edge &e, Mesh &mesh, vector<int> &concavesigne, int num);

//
bool belongsToMeshFeature(Edge &e, Mesh &mesh, vector<int> &regionEdge);

Point3d det2(const Point3d &a, const Point3d &b);

Point3d pVec2(const Point3d &a, const Point3d &b, const Point3d &c);

#endif