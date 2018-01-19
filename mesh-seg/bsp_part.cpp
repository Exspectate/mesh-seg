#include "bsp_part.h"


bsp_part::bsp_part()
{
}


bsp_part::~bsp_part()
{
}

void bsp_part::findfeatureLines(Mesh & mesh)
{


}

void bsp_part::findfeatureVerts(Mesh& mesh)
{
}


void bsp_part::initSelectData(Mesh& mesh, int color)
{

	map<PII, int> ma;

	this->inVerts.clear();
	this->inFacets.clear();
	this->inbadEdge.clear();
	this->featureLines.clear();
	this->featureVerts.clear();


	this->color = color;

	for (int i = 0; i < mesh.Verts.size(); i++)
		if (mesh.Verts[i].color == color)
			this->inVerts.push_back(i);

	for (int i = 0; i < mesh.Facets.size(); i++)
	{
		//nowColor=iƬ�����������ɫ���ֵ
		int nowColor = max(
			max(mesh.Verts[mesh.Facets[i].vertIdx[0]].color,
				mesh.Verts[mesh.Facets[i].vertIdx[1]].color),
			mesh.Verts[mesh.Facets[i].vertIdx[2]].color);

		if (nowColor == -1)
		{
			for (int j = 0; j < mesh.adjVert[mesh.Facets[i].vertIdx[0]].size(); j++) //������iƬ��0����ڽӶ��㼯
				nowColor = max(nowColor, mesh.Verts[mesh.adjVert[mesh.Facets[i].vertIdx[0]][j]].color);//nowColor=������iƬ��0�㼰���ڽӶ��㼯����ɫ���ֵ
		}

		if (nowColor == color)		//���Ƭ����ɫƥ��������ɫ
		{
			this->inFacets.push_back(i);
			PII a, b, c;
			a.first = c.second = mesh.Facets[i].vertIdx[0];
			a.second = b.first = mesh.Facets[i].vertIdx[1];
			b.second = c.first = mesh.Facets[i].vertIdx[2];
			if (a.first > a.second)	//�Ƚϵ���������
				swap(a.first, a.second);
			if (b.first > b.second)
				swap(b.first, b.second);
			if (c.first > c.second)
				swap(c.first, c.second);
			ma[a]++;	//��¼����ƥ���� ����ĳ����ܴ���
			ma[b]++;
			ma[c]++;
		}
	}

	for (map<PII, int>::iterator it = ma.begin(); it != ma.end(); it++)
	{
		if (it->second == 1)
		{
			this->inbadEdge.push_back(it->first);
			mesh.Verts[it->first.first].isBad = true;
			mesh.Verts[it->first.second].isBad = true;
			this->inVerts.push_back(it->first.first);
			this->inVerts.push_back(it->first.second);
		}
	}
	sort(this->inVerts.begin(), this->inVerts.end());
	this->inVerts.erase(unique(this->inVerts.begin(), this->inVerts.end()), this->inVerts.end()); //�Ե�idȥ��
}


void bsp_part::writeFeatureLinesToFile(string filePath)
{
	cout << fixed << setprecision(8);
	for (int i = 0; i<featureLines.size(); i++)
	{
		int t = i + 1;
		stringstream stream;
		stream << t;
		string ts = stream.str();
		ofstream fout(filePath + "DataFile" + ts + ".dat");
		fout << "x\ty\tz" << endl;
		for (int j = 0; j<featureLines[i].size(); j++)
			fout << featureLines[i][j].x << "\t" << featureLines[i][j].y << "\t" << featureLines[i][j].z << endl;
		fout.flush();
		fout.close();
	}
}

int bsp_part::findPartsPoint(Mesh & mesh, int color)
{
	for (int i = 0; i < mesh.Verts.size(); ++i) {
		if (mesh.Verts[i].color == color)
			return i;
	}
	return 0;
}