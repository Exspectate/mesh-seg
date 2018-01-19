#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif  
#pragma once

#include <QGLWidget>
#include <glut.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QVector3D>
#include <QColorDialog>
#include <QFile>
#include "DialogLabel.h"
#include "lty_STL.h"
#include "gy_show.h"
#include "dijkstra.h"
#include "gy_fitting.h"
#include "csy_Pitching.h"
#include "zc_VRudder.h"
#include "csy_ALLPART.h"
typedef pair<int, int> PII;

class MeshViewer : public QGLWidget
{
	Q_OBJECT

	

public:
	MeshViewer(QWidget *parent=0);
	~MeshViewer();
	public slots:
	void openMesh();			//������
	void cutMesh();				//����ָ�
	void showFlatlines();		//����������
	void showFlat();			//������������
	void hideMesh();
	void showFeatureLineMesh();
public:
	int targetPart;				//Ŀ�겿���ı��
	
private:
	void resizeGL(int, int);		//����仯���ػ溯��
	void paintGL();					//OpenGL���ƺ���
	void initializeGL();			//��ʼ������
	
	void DrawOriMesh();				//��ԭʼģ��
	void drawMesh();				//���ָ��ģ��
	void DrawLineMesh();			//��ģ�͵�����
	void DrawFeatureLines();
	void DrawHideMesh();
	

	void mousePressEvent(QMouseEvent *mouseevent);		//�����¼�
	void mouseMoveEvent(QMouseEvent *event);			//�϶��¼�
	void wheelEvent(QWheelEvent * mouseEvent);			//�����¼�	����
	void keyPressEvent(QKeyEvent * keyEvent);			//�����¼�

	//Functions
	int bfs(int node, int color, Mesh &mesh);
	int reBfs(int node, Mesh &mesh);
	void setColor(Mesh &mesh);
	void pickPoint();
	void setPickPart();
	

	float fovy()  const { return 0.00f; };
	float zNear() const { return 0.001f; };
	float zFar()  const { return 100.0f;};


private:
	Mesh mesh;
	QString     m_filename;		//���ļ�·��
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat rotationZ;
	QPoint lastPos;
	float times;				//���ű���
	float oldx;					//����任������
	float oldy;
	int du;						//�ӵ��x��ļн�
	int OriX;					
	int OriY;
	float r;					//�ӵ���y��İ뾶
	float h;					//�ӵ�߶ȼ���y���ϵ�����

	int selectMode;


	int regionCount;			//��������
	vector<vector<Point3d> >regionPt;
								//���������
	Dijkstra dija;			

	bool isMesh;				//�Ƿ��ģ��
	bool isCutMesh;				//�Ƿ�ָ�ģ��
	bool isMeshPoint;			//�Ƿ���ģ���ϵ�
	bool drawLine;				//��������

	//PitchR pitchRudder;		//������
	//VRudder leftVRudder;	//��V�Ͷ�
	//VRudder rightVRudder;	//��V�Ͷ�
	
	ALLPART allpart;
};
