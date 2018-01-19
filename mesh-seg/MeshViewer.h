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
	void openMesh();			//打开网格
	void cutMesh();				//网格分割
	void showFlatlines();		//网格线条化
	void showFlat();			//非线条化网格
	void hideMesh();
	void showFeatureLineMesh();
public:
	int targetPart;				//目标部件的编号
	
private:
	void resizeGL(int, int);		//窗体变化的重绘函数
	void paintGL();					//OpenGL绘制函数
	void initializeGL();			//初始化函数
	
	void DrawOriMesh();				//画原始模型
	void drawMesh();				//画分割后模型
	void DrawLineMesh();			//画模型的线性
	void DrawFeatureLines();
	void DrawHideMesh();
	

	void mousePressEvent(QMouseEvent *mouseevent);		//单击事件
	void mouseMoveEvent(QMouseEvent *event);			//拖动事件
	void wheelEvent(QWheelEvent * mouseEvent);			//滚轮事件	缩放
	void keyPressEvent(QKeyEvent * keyEvent);			//键盘事件

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
	QString     m_filename;		//打开文件路径
	GLfloat rotationX;
	GLfloat rotationY;
	GLfloat rotationZ;
	QPoint lastPos;
	float times;				//缩放倍数
	float oldx;					//矩阵变换的坐标
	float oldy;
	int du;						//视点和x轴的夹角
	int OriX;					
	int OriY;
	float r;					//视点绕y轴的半径
	float h;					//视点高度即在y轴上的坐标

	int selectMode;


	int regionCount;			//特征区域
	vector<vector<Point3d> >regionPt;
								//特征区域点
	Dijkstra dija;			

	bool isMesh;				//是否打开模型
	bool isCutMesh;				//是否分割模型
	bool isMeshPoint;			//是否是模型上点
	bool drawLine;				//画特征线

	//PitchR pitchRudder;		//俯仰舵
	//VRudder leftVRudder;	//左V型舵
	//VRudder rightVRudder;	//右V型舵
	
	ALLPART allpart;
};
