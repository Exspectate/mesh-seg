#include "bsp_Frame1.h"
bsp_Frame1::bsp_Frame1()
{
	this->featureVerts.clear();
	this->featureVerts.clear();
	this->inbadEdge.clear();
	this->inFacets.clear();
	this->inVerts.clear();

}

void bsp_Frame1::findLR(Mesh& mesh)
{
	Point3d &pfromL = this->belongTo->f3->L;
	Point3d &pfromR = this->belongTo->f3->R;
	vector<Point3d> points; //�����ϵĵ�
	for (size_t i = 0; i < this->inbadEdge.size(); ++i)
	{
		//��ֹ�㲻һ���ڻ����� �赥������
		Point3d l0 = mesh.Verts[this->inbadEdge[i].first];
		Point3d l1 = mesh.Verts[this->inbadEdge[i].second];
		points.push_back(l0);
		points.push_back(l1);
	}

	double minlentoL = DBL_MAX;
	double minlentoR = DBL_MAX;
	size_t minpostoL = -1;
	size_t minpostoR = -1;

	for (size_t k = 0; k < points.size(); ++k)
	{

		Point3d& temp = points[k];

		double templentoL = (temp - pfromL).len();
		double templentoR = (temp - pfromR).len();

		if (templentoL < minlentoL)
		{
			minpostoL = k;
			minlentoL = templentoL;
		}

		if (templentoR < minlentoR)
		{
			minpostoR = k;
			minlentoR = templentoR;
		}
	}

	this->L = points[minpostoL];
	this->R = points[minpostoR];
}


void bsp_Frame1::findCurve(Mesh & mesh)
{
	//ǰ����
	set<Point3d> setcurve;

	//��ÿ����Ƭ����С����
	for (int i = 0; i < this->inFacets.size(); ++i)
	{
		int i1 = mesh.Facets[this->inFacets[i]].vertIdx[0];
		int i2 = mesh.Facets[this->inFacets[i]].vertIdx[1];
		int i3 = mesh.Facets[this->inFacets[i]].vertIdx[2];

		Point3d l0;
		Point3d l1;

		// ƽ��3��  ������Ƭ3��  ������������
		bool flag = PlaneByTri(
			this->L, this->R, this->belongTo->f2->L,
			mesh.Verts[i1], mesh.Verts[i2], mesh.Verts[i3],
			l0, l1
		);

		//�����ϵĵ�������߼���
		if (flag == true)
		{

			setcurve.insert(l0);
			setcurve.insert(l1);
		}
	}

	setcurve.insert(this->L);
	setcurve.insert(this->R);

	vector<P_L> pl;

	set<Point3d>::iterator iter = setcurve.begin();

	while (iter != setcurve.end())
	{
		double l = (this->L - *iter).len();
		pl.push_back(P_L(l, *iter));
		++iter;
	}

	sort(pl.begin(), pl.end(), comppl);

	for (int i = 0; i < pl.size(); ++i)
	{
		this->Curve.push_back(pl[i].p);
	}
}

void bsp_Frame1::initUpDown(Mesh & mesh)
{

	//�����ϰ벿�֡��°벿��
	for (size_t i = 0; i < this->inbadEdge.size(); ++i)
	{
		//��ֹ�㲻һ���ڻ����� �赥������
		Point3d l0 = mesh.Verts[this->inbadEdge[i].first];
		Point3d l1 = mesh.Verts[this->inbadEdge[i].second];

		int UD1 = this->belongTo->f3->Up_Down(l0);
		int UD2 = this->belongTo->f3->Up_Down(l1);

		if (UD1 == 1 || UD2 == 1)
		{
			this->UpCurve.push_back(make_pair(l0, l1));
		}
		else
		{
			this->DownCurve.push_back(make_pair(l0, l1));
		}
	}
	/*******************************************/
	//��¼Up�ϵĵ�(ȥ��LR)
	set<Point3d> UpSet;
	for (size_t i = 0; i < this->UpCurve.size(); ++i)
	{
		Point3d l0 = this->UpCurve[i].first;
		Point3d l1 = this->UpCurve[i].second;
		if (!(l0 == this->L || l0 == this->R))
		{
			UpSet.insert(l0);
		}
		if (!(l1 == this->L || l1 == this->R))
		{
			UpSet.insert(l1);
		}
	}

	//��¼Down�ϵĵ�(ȥ��LR)
	set<Point3d> DownSet;
	for (size_t i = 0; i < this->DownCurve.size(); ++i)
	{
		Point3d l0 = this->DownCurve[i].first;
		Point3d l1 = this->DownCurve[i].second;
		if (!(l0 == this->L || l0 == this->R))
		{
			DownSet.insert(l0);
		}
		if (!(l1 == this->L || l1 == this->R))
		{
			DownSet.insert(l1);
		}
	}

	//���������f1 L��R��������ģ�����U D�������ϵ��ĸ���
	double minlenLU = DBL_MAX;
	double minlenRU = DBL_MAX;

	double minlenLD = DBL_MAX;
	double minlenRD = DBL_MAX;

	Point3d minposLU = Point3d(DBL_MAX, DBL_MAX, DBL_MAX);
	Point3d minposRU = Point3d(DBL_MAX, DBL_MAX, DBL_MAX);

	Point3d minposLD = Point3d(DBL_MAX, DBL_MAX, DBL_MAX);
	Point3d minposRD = Point3d(DBL_MAX, DBL_MAX, DBL_MAX);

	set<Point3d>::iterator itU = UpSet.begin();
	while (itU != UpSet.end())
	{
		double tmplenLU = (*itU - this->L).len();
		double tmplenRU = (*itU - this->R).len();

		if (tmplenLU < minlenLU)
		{
			minlenLU = tmplenLU;
			minposLU = *itU;
		}
		if (tmplenRU < minlenRU)
		{
			minlenRU = tmplenRU;
			minposRU = *itU;
		}

		++itU;
	}

	set<Point3d>::iterator itD = DownSet.begin();
	while (itD != DownSet.end())
	{
		double tmplenLD = (*itD - this->L).len();
		double tmplenRD = (*itD - this->R).len();

		if (tmplenLD < minlenLD)
		{
			minlenLD = tmplenLD;
			minposLD = *itD;
		}
		if (tmplenRD < minlenRD)
		{
			minlenRD = tmplenRD;
			minposRD = *itD;
		}
		++itD;
	}
	//���߽������������ߴ����Ӧ������
	if (minlenLU != 0)
	{
		this->UpCurve.push_back(make_pair(minposLU, this->L));
	}
	if (minlenLD != 0)
	{
		this->DownCurve.push_back(make_pair(minposLD, this->L));
	}
	if (minlenRU != 0)
	{
		this->UpCurve.push_back(make_pair(minposRU, this->R));
	}
	if (minlenRD != 0)
	{
		this->DownCurve.push_back(make_pair(minposRD, this->R));
	}

}

//�����뵱ǰ����featureLines��
void bsp_Frame1::findfeatureLines(Mesh & mesh)
{
	//this->findLR(mesh);
	//this->findCurve(mesh);
	//this->initUpDown(mesh);
};

void bsp_Frame1::findfeatureVerts(Mesh & mesh)
{

}
bsp_Frame1::~bsp_Frame1()
{

}

bool comppl(const P_L & a, const P_L & b)
{
	return a.l < b.l;
}