#include "MeshViewer.h"

//static const int COLOR1[19] = { 255,255,255,  0,141, 23, 66,255,139,255,139,139,255,139,139,255,255 };
//static const int COLOR2[19] = { 255,  0,117,  0, 75,248, 80,129,0  ,101,58 ,69 ,137,0  ,228,250,0 };
//static const int COLOR3[19] = { 255,151,  0,255,187,203,102,  0,76 ,0  ,8  ,58 ,0  ,137,0  ,225,205,255 };
static const int COLOR1[19] = { 255,  0,  0,  0,255,139,255,255,255,255,148,136,  0,255,160,238,255 };
static const int COLOR2[19] = { 255,245,  0,238,246,101,255,106,  0, 20,  0, 69,205,215, 32, 64,255 };
static const int COLOR3[19] = { 255,255,128,  0,143,  8,  0,106,  0,147,211, 19,  0,  0,240,  0,240};
//
static const double PI = 3.1415926535;
static float c = PI / 180.0;    //���ȺͽǶ�ת������
static GLfloat winx, winy, winz;
static GLdouble posx, posy, posz;
int targetId = -1;  //��¼��ģ������ѡȡ��������id
int targetColor;	//��¼��ǰ��������ɫ

MeshViewer::MeshViewer(QWidget *parent)
	: QGLWidget(parent)
{
	setAttribute(Qt::WA_NoSystemBackground, true);
	setFocusPolicy(Qt::StrongFocus);
	rotationX = 0.0;
	rotationY = 0.0;
	rotationZ = 0.0;
	times = 1.0;
	oldx = -1000.0;
	oldy = 0.0;
	du = 90;
	r = 1000;
	h = 0;

	targetColor = -1;
	selectMode = 0;
	isMesh = 0;
	isMeshPoint = 0;
	drawLine = 0;

}


MeshViewer::~MeshViewer()
{
}

void MeshViewer::cutMesh()
{//�ָ�
	selectMode = 2;
	isCutMesh = 1;
	updateGL();
}

void MeshViewer::showFlatlines()
{//��ʾ����
	selectMode = 3;
	updateGL();
}

void MeshViewer::showFlat()
{//��ʾԭģ��
	selectMode = 1;
	updateGL();
}

void MeshViewer::hideMesh()
{
	selectMode = 5;
	updateGL();
}

void MeshViewer::showFeatureLineMesh()
{//��ʾ������
	selectMode = 4;
	/*this->leftVRudder.initSelectData(this->mesh,this->mesh.kind_color[5]);
	this->leftVRudder.findFeatureLines(mesh);
	this->leftVRudder.writeFeatureLinesToFile("DataFiles/LeftVFiles/");

	this->rightVRudder.initSelectData(this->mesh,this->mesh.kind_color[6]);
	this->rightVRudder.findFeatureLines(this->mesh);
	this->rightVRudder.writeFeatureLinesToFile("DataFiles/RightVFiles/");

	this->pitchRudder.initSelectData(this->mesh,this->mesh.kind_color[4]);
	this->pitchRudder.findFeatureLines(this->mesh);
	this->pitchRudder.writeFeatureLinesToFile("DataFiles/PitchFiles/");*/
	this->allpart.initPartDATA(mesh);
	updateGL();
}

void MeshViewer::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);    //��ͼ;1��2Ϊ�ӿڵ����½�;3��4Ϊ�ӿڵĿ�Ⱥ͸߶�
	glMatrixMode(GL_PROJECTION);    //����ǰ����ָ��ΪͶӰ����
	glLoadIdentity();
	gluPerspective(75.0, (float)width / height, 1.0, 4000.0); //1����Ұ��Y-Zƽ��ĽǶ�[0,180];2��ͶӰƽ������߶ȵı���;3�����ؼ��浽�ӵ�ľ���;4��Զ�ؼ��浽�ӵ�ľ���
	glMatrixMode(GL_MODELVIEW);     //��ģ���Ӿ������ջӦ�����ľ������.
}


void MeshViewer::initializeGL()
{
	//��ʼ��OpenGL����  
	GLfloat light_position[] = { 0, 0, 0, 0 };	//��Դλ�� ���һλ 0-�����Դ��1-���Դ
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };     //ɢ���;��淴������
	GLfloat Light_Model_Ambient[] = { 0.0,0.0,0.0, 1.0 }; //���������,�׹�
	glEnable(GL_LIGHT0);			   //��0#��
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	//����LIGHT0��λ��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);      //ɢ�������
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);     //���淴���
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Model_Ambient);//RGBAģʽ�Ļ����⣬Ϊ0 

	GLfloat light_position1[] = { 0, 0, 200.0, 0 };	//��Դλ�� ���һλ 0-�����Դ��1-���Դ
	GLfloat white_light1[] = { 1.0, 1.0, 1.0, 1.0 };     //ɢ���;��淴������
	GLfloat Light_Model_Ambient1[] = { 0.0,0.0,0.0, 1.0 }; //���������,�׹�
	glEnable(GL_LIGHT1);			   //��1#��
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);	//����LIGHT1��λ��
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light1);      //ɢ�������
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light1);     //���淴���
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light_Model_Ambient1);//RGBAģʽ�Ļ����⣬Ϊ0 

	GLfloat light_position2[] = { 2000, 0, 0, 0 };	//��Դλ�� ���һλ 0-�����Դ��1-���Դ
	GLfloat white_light2[] = { 1.0, 1.0, 1.0, 1.0 };     //ɢ���;��淴������
	GLfloat Light_Model_Ambient2[] = { 0.0,0.0,0.0, 1.0 }; //���������,�׹�
	glEnable(GL_LIGHT2);			   //��2#��
	glLightfv(GL_LIGHT2, GL_POSITION, light_position2);	//����LIGHT2��λ��
	glLightfv(GL_LIGHT2, GL_DIFFUSE, white_light2);      //ɢ�������
	glLightfv(GL_LIGHT2, GL_SPECULAR, white_light2);     //���淴���
	glLightfv(GL_LIGHT2, GL_AMBIENT, Light_Model_Ambient2);//RGBAģʽ�Ļ����⣬Ϊ0 											
	glEnable(GL_LIGHTING);			   //����:ʹ�ù�
	glShadeModel(GL_SMOOTH);           //��ɫ����ģʽ
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);		   //��Ȳ���
									   //glEnable(GL_DEPTH_TEST);    //������ȣ����������Զ���Զ����ر���ס��ͼ�Σ����ϣ�
	//glTranslatef(1000, 1000, 0.0);
}

void MeshViewer::paintGL()
{

	glClearColor(161. / 255, 175. / 255, 201. / 255, 1.0);   //������ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������壬GL_COLOR_BUFFER_BIT ����ɫ�����־λ
	glLoadIdentity();                                       //���õ�ǰ����Ϊ4*4�ĵ�λ����
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);   //���ӵ㿴Զ��
	switch (selectMode) {
	case 1:DrawOriMesh(); break;			//��ԭʼģ��
	case 2:drawMesh(); break;				//���ָ��ģ��
	case 3:DrawLineMesh(); break;			//��ģ�͵���������ģ��
	case 4:DrawFeatureLines(); break;		//��ģ��������
	case 5:DrawHideMesh(); break;			//�����ػ���
	default:drawMesh();
	}

}

void MeshViewer::DrawOriMesh()
{
	glScalef(times, times, times);
	//glTranslatef(oldx, oldy, 0.0);

	Point3d p1 = this->allpart.f3->bigpoint;
	Point3d p2 = this->allpart.f1->L;
	Point3d p3 = this->allpart.f1->R;

	p1 = p1 + p2;
	p1 = p1 + p3;
	p1.x /= -3.0;
	p1.y /= -3.0;
	p1.z /= -3.0;


	cout << p1.x << " " << p1.y << " " << p1.z << endl;
	glTranslatef(p1.x, p1.y, p1.z);

	glRotatef(rotationX, 1.0, 0.0, 0.0);
	glRotatef(rotationY, 0.0, 1.0, 0.0);

	/*glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);*/
	for (int i = 0; i <mesh.Facets.size(); i = i + 1) {
		glColor3f(0.0, 0.0, 1.0);		//��ɫ
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < 3; ++j) {
			glNormal3f(mesh.vertnorm[mesh.Facets[i].vertIdx[j]].x, mesh.vertnorm[mesh.Facets[i].vertIdx[j]].y, mesh.vertnorm[mesh.Facets[i].vertIdx[j]].z);
			glVertex3f(mesh.Verts[mesh.Facets[i].vertIdx[j]].x, mesh.Verts[mesh.Facets[i].vertIdx[j]].y, mesh.Verts[mesh.Facets[i].vertIdx[j]].z);
		}
		glEnd();
	}
	//glDisable(GL_COLOR_MATERIAL);
	glFlush();
}

void MeshViewer::drawMesh()
{
	if (!isCutMesh) return;
	glScalef(times, times, times);
	glTranslatef(oldx, oldy, 0.0);
	
	glRotatef(rotationX, 1.0, 0.0, 0.0);
	glRotatef(rotationY, 0.0, 1.0, 0.0);
	//glRotatef(rotationZ, 0.0, 0.0, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	for (int i = 0; i <mesh.Facets.size(); i = i + 1) {
		int nowColor = max(max(mesh.Verts[mesh.Facets[i].vertIdx[0]].color, mesh.Verts[mesh.Facets[i].vertIdx[1]].color), mesh.Verts[mesh.Facets[i].vertIdx[2]].color);
		if (nowColor == -1)
		{
			for (int j = 0; j<mesh.adjVert[mesh.Facets[i].vertIdx[0]].size(); j++)
				nowColor = max(nowColor, mesh.Verts[mesh.adjVert[mesh.Facets[i].vertIdx[0]][j]].color);
		}
		glColor3f(1.0*COLOR1[nowColor] / 255, 1.0*COLOR2[nowColor] / 255, 1.0*COLOR3[nowColor] / 255);		//��ɫ
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < 3; ++j) {
			glNormal3f(mesh.vertnorm[mesh.Facets[i].vertIdx[j]].x, mesh.vertnorm[mesh.Facets[i].vertIdx[j]].y, mesh.vertnorm[mesh.Facets[i].vertIdx[j]].z);
			glVertex3f(mesh.Verts[mesh.Facets[i].vertIdx[j]].x, mesh.Verts[mesh.Facets[i].vertIdx[j]].y, mesh.Verts[mesh.Facets[i].vertIdx[j]].z);
		}
		glEnd();
	}
	glDisable(GL_COLOR_MATERIAL);
	glFlush();

}

void MeshViewer::DrawLineMesh()
{
	glScalef(times, times, times);
	glTranslatef(oldx, oldy, 0.0);

	glRotatef(rotationX, 1.0, 0.0, 0.0);
	glRotatef(rotationY, 0.0, 1.0, 0.0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	for (int i = 0; i <mesh.Facets.size(); i = i + 1) {
		glColor3f(0.0, 0.0, 1.0);		//��ɫ
		glBegin(GL_LINES);
		for (int j = 0; j < 3; ++j) {
			glNormal3f(mesh.vertnorm[mesh.Facets[i].vertIdx[j]].x, mesh.vertnorm[mesh.Facets[i].vertIdx[j]].y, mesh.vertnorm[mesh.Facets[i].vertIdx[j]].z);
			glVertex3f(mesh.Verts[mesh.Facets[i].vertIdx[j]].x, mesh.Verts[mesh.Facets[i].vertIdx[j]].y, mesh.Verts[mesh.Facets[i].vertIdx[j]].z);
		}
		glEnd();
	}
	glDisable(GL_COLOR_MATERIAL);
	glFlush();
}

void MeshViewer::DrawFeatureLines()
{
	glScalef(times, times, times);
	glTranslatef(oldx, oldy, 0.0);

	glRotatef(rotationX, 1.0, 0.0, 0.0);
	glRotatef(rotationY, 0.0, 1.0, 0.0);
	//glRotatef(rotationZ, 0.0, 0.0, 1.0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//for (int i = 0; i <mesh.Facets.size(); i = i + 1) {
	//	int nowColor = max(max(mesh.Verts[mesh.Facets[i].vertIdx[0]].color, mesh.Verts[mesh.Facets[i].vertIdx[1]].color), mesh.Verts[mesh.Facets[i].vertIdx[2]].color);
	//	if (nowColor == -1)
	//	{
	//		for (int j = 0; j<mesh.adjVert[mesh.Facets[i].vertIdx[0]].size(); j++)
	//			nowColor = max(nowColor, mesh.Verts[mesh.adjVert[mesh.Facets[i].vertIdx[0]][j]].color);
	//	}
	//	if (nowColor == this->mesh.kind_color[5]) continue;
	//	if (nowColor == this->mesh.kind_color[6]) continue;
	//	if (nowColor == this->mesh.kind_color[4]) continue;
	//	//if (nowColor == 3) continue;
	//	glColor3f(1.0*COLOR1[nowColor] / 255, 1.0*COLOR2[nowColor] / 255, 1.0*COLOR3[nowColor] / 255);		//��ɫ
	//	glBegin(GL_TRIANGLES);
	//	for (int j = 0; j < 3; ++j) {
	//		glNormal3f(mesh.vertnorm[mesh.Facets[i].vertIdx[j]].x, mesh.vertnorm[mesh.Facets[i].vertIdx[j]].y, mesh.vertnorm[mesh.Facets[i].vertIdx[j]].z);
	//		glVertex3f(mesh.Verts[mesh.Facets[i].vertIdx[j]].x, mesh.Verts[mesh.Facets[i].vertIdx[j]].y, mesh.Verts[mesh.Facets[i].vertIdx[j]].z);
	//	}
	//	glEnd();
	//	
	//}

	//��ʾ��V�Ͷ沿��
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);			//��ɫ
	for (int i = 0; i<11; i++)
	{
		for (int j = 0; j + 1<this->allpart.leftVRudder->featureLines[i].size(); j++)
		{
			int nowColor = 17 - i;
			glColor3f(1.0*COLOR1[nowColor] / 255, 1.0*COLOR2[nowColor] / 255, 1.0*COLOR3[nowColor] / 255);
			Point3d p1 = this->allpart.leftVRudder->featureLines[i][j];
			Point3d p2 = this->allpart.leftVRudder->featureLines[i][j + 1];
			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p2.x, p2.y, p2.z);
		}
	}
	glEnd();
	 
	//��ʾ��V�Ͷ沿��
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);			//��ɫ
	for (int i = 0; i<11; i++)
	{
		for (int j = 0; j + 1<this->allpart.rightVRudder->featureLines[i].size(); j++)
		{
			int nowColor = 17 - i;
			glColor3f(1.0*COLOR1[nowColor] / 255, 1.0*COLOR2[nowColor] / 255, 1.0*COLOR3[nowColor] / 255);
			Point3d p1 = this->allpart.rightVRudder->featureLines[i][j];
			Point3d p2 = this->allpart.rightVRudder->featureLines[i][j + 1];
			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p2.x, p2.y, p2.z);
		}
	}
	glEnd();

	//��ʾ�����沿��
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);			//��ɫ
	for (int i = 0; i<12; i++)
	{
		for (int j = 0; j + 1<this->allpart.pitchRudder->featureLines[i].size(); j++)
		{
			int nowColor = 17 - i;
			glColor3f(1.0*COLOR1[nowColor] / 255, 1.0*COLOR2[nowColor] / 255, 1.0*COLOR3[nowColor] / 255);
			Point3d p1 = this->allpart.pitchRudder->featureLines[i][j];
			Point3d p2 = this->allpart.pitchRudder->featureLines[i][j + 1];
			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p2.x, p2.y, p2.z);
		}
	}
	glEnd();

	//����
	glLineWidth(3.0f);
	cout <<"&&&&&&"<< this->allpart.f3->featureLines.size()<<endl;
	for (int k = 0; k < this->allpart.f3->featureLines.size(); ++k)
	{
		glBegin(GL_LINES);
		int nowColor = 17 - k;
		glColor3f(1.0*COLOR1[nowColor] / 255, 1.0*COLOR2[nowColor] / 255, 1.0*COLOR3[nowColor] / 255);
		vector<Point3d> aline = this->allpart.f3->featureLines[k];
		for (int i = 0; i < aline.size() - 1; ++i) {
			Point3d &a = aline[i];
			Point3d &b = aline[i + 1];

			glVertex3f(a.x, a.y, a.z);
			glVertex3f(b.x, b.y, b.z);

		}
		glEnd();
	}

	glDisable(GL_COLOR_MATERIAL);
	glFlush();
}

void MeshViewer::DrawHideMesh()
{
	//glScalef(times, times, times);
	//glTranslatef(oldx, oldy, 0.0);

	//glRotatef(rotationX, 1.0, 0.0, 0.0);
	//glRotatef(rotationY, 0.0, 1.0, 0.0);
	////glRotatef(rotationZ, 0.0, 0.0, 1.0);
	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//for (int i = 0; i <mesh.Facets.size(); i = i + 1) {
	//	int nowColor = max(max(mesh.Verts[mesh.Facets[i].vertIdx[0]].color, mesh.Verts[mesh.Facets[i].vertIdx[1]].color), mesh.Verts[mesh.Facets[i].vertIdx[2]].color);
	//	if (nowColor == -1)
	//	{
	//		for (int j = 0; j<mesh.adjVert[mesh.Facets[i].vertIdx[0]].size(); j++)
	//			nowColor = max(nowColor, mesh.Verts[mesh.adjVert[mesh.Facets[i].vertIdx[0]][j]].color);
	//	}
	//	if (nowColor == targetColor) continue;
	//	if (nowColor == 3) continue;
	//	glColor3f(1.0*COLOR1[nowColor] / 255, 1.0*COLOR2[nowColor] / 255, 1.0*COLOR3[nowColor] / 255);		//��ɫ
	//	glBegin(GL_TRIANGLES);
	//	for (int j = 0; j < 3; ++j) {
	//		glNormal3f(mesh.vertnorm[mesh.Facets[i].vertIdx[j]].x, mesh.vertnorm[mesh.Facets[i].vertIdx[j]].y, mesh.vertnorm[mesh.Facets[i].vertIdx[j]].z);
	//		glVertex3f(mesh.Verts[mesh.Facets[i].vertIdx[j]].x, mesh.Verts[mesh.Facets[i].vertIdx[j]].y, mesh.Verts[mesh.Facets[i].vertIdx[j]].z);
	//	}
	//	glEnd();

	//}

	//glBegin(GL_LINES);
	//glColor3f(1.0, 0.0, 0.0);			//��ɫ
	//for (int i = 0; i<featureLines.size(); i++)
	//{
	//	for (int j = 0; j + 1<featureLines[i].size(); j++)
	//	{
	//		int nowColor = 17 - i;
	//		glColor3f(1.0*COLOR1[nowColor] / 255, 1.0*COLOR2[nowColor] / 255, 1.0*COLOR3[nowColor] / 255);
	//		Point3d p1 = featureLines[i][j];
	//		Point3d p2 = featureLines[i][j + 1];
	//		glVertex3f(p1.x, p1.y, p1.z);
	//		glVertex3f(p2.x, p2.y, p2.z);
	//	}
	//}
	//glEnd();

	//glDisable(GL_COLOR_MATERIAL);
	//glFlush();

	for (map<int, int> ::iterator it = this->mesh.kind_color.begin(); it != this->mesh.kind_color.end(); it++)
		cout << "kind:" << it->first << " color:" << it->second<<endl;
}

//���+�����¼�
void MeshViewer::mousePressEvent(QMouseEvent * mouseevent)
{
	lastPos = mouseevent->pos();
	if (mouseevent->buttons() == Qt::RightButton) {
		winx = mouseevent->pos().x();
		winy = mouseevent->pos().y();
		pickPoint();
		setPickPart();
		//updateGL();
		if (isMeshPoint) {
		//	cout << isMeshPoint << endl;
			DialogLabel d;
			d.move(100, 100);
			d.exec();
			targetPart = d.getTargetNum();	
			if (sign(posx) != 0 || sign(posy) != 0 || sign(posz) != 0) {
				//Message_label = -1;
				bfs(targetId, targetColor, mesh); //�ڱ����ɺ󣬽�ѡ�в���Ⱦ��ԭ������ɫ
				cout << targetColor << endl;
				this->mesh.kind_color[targetPart] = targetColor;
				posx = posy = posz = 0;
				updateGL();
			}
		}
		else {
			QMessageBox::about(NULL, "", QString("����ı�������±��"));
		}
	} 
}

void MeshViewer::mouseMoveEvent(QMouseEvent * event)
{
	GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
	GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
	if (event->buttons() == Qt::LeftButton) {
		rotationX += 180 * dy;
		rotationY += 180 * dx;
		updateGL();
	}
	lastPos = event->pos();
}

void MeshViewer::wheelEvent(QWheelEvent * mouseEvent)
{
	GLfloat scaleUnit = 0.06f;
	double moveAmount = (double)mouseEvent->delta() ;
	if (moveAmount > 0) {
		times += scaleUnit;
	}
	else {
		times -= scaleUnit;
	}
	updateGL();
	mouseEvent->accept();
}

void MeshViewer::keyPressEvent(QKeyEvent * keyEvent)
{
	GLfloat unit = 20.f;
	switch (keyEvent->key()) {
	case Qt::Key_Up:oldy += unit; break;
	case Qt::Key_Down:oldy -= unit; break;
	case Qt::Key_Left:oldx -= unit; break;
	case Qt::Key_Right:oldx += unit; break;
	default:break;
	}
	updateGL();
}

//�㷨
int MeshViewer::bfs(int node, int color, Mesh & mesh)
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

int MeshViewer::reBfs(int node, Mesh & mesh)
{
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

void MeshViewer::setColor(Mesh & mesh)
{
	int nowColor = 0;
	for (int i = 0; i<mesh.Verts.size(); i++)
	{
		if (mesh.Verts[i].color == 0)
		{
			nowColor++;
			int ret = bfs(i, nowColor, mesh);
			cout << "Point count:" << ret << "\n";
		}
	}

	cout << "Block count:" << nowColor << endl;
}

void MeshViewer::pickPoint()
{
	GLdouble modelMatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	GLdouble projMatrix[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	winy = GLdouble(viewport[3] - (GLint)winy);
	glReadPixels(winx, winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);
	gluUnProject(winx, winy, winz, modelMatrix, projMatrix, viewport, &posx, &posy, &posz);
	//cout << posx <<" "<< posy <<" "<< posz << endl;
}

void MeshViewer::setPickPart()
{
	
	if (sign(posx) != 0 || sign(posy) != 0 || sign(posz) != 0) {    //����������Ҽ�ʱ,��ȡ����Ӧ��ά�ռ������
		double dis = 1e30;
		for (int i = 0; i < mesh.Verts.size(); ++i) {
			if (mesh.Verts[i].color < 0) continue;  //����ǻ����ϵĵ㣬������
			Point3d tp = Point3d(posx - mesh.Verts[i].x, posy - mesh.Verts[i].y, posz - mesh.Verts[i].z);
			if (tp.len() < dis) {
				dis = tp.len();
				targetId = i;
				
			}
			
		}
	//	cout << mesh.Verts[targetId].x << " " << mesh.Verts[targetId].y << " " << mesh.Verts[targetId].z << endl;
		if (dis < 1e2) {      //��ѡ�в���Ⱦ�ɰ�ɫ��ʾѡ��
			targetColor = mesh.Verts[targetId].color;
			reBfs(targetId, mesh);
			isMeshPoint = 1;
		}
		else { //�������˵���Ҽ������ģ���⣬���账��
			posx = posy = posz = 0;
		}
	}
}

//���ļ�

void MeshViewer::openMesh() {
	isCutMesh = 0;
	m_filename = QFileDialog::getOpenFileName(this, tr("Open Stl File"), "", tr("STL File (*.stl)"));
	if (!m_filename.isEmpty()) {
		//showOpenGLWindow(fileName.toStdString());
		mesh.clear();
		QByteArray byteArray = m_filename.toUtf8();
		const char * _filename = byteArray.constData();
		//cout << m_filename.toStdString() << endl;
		//const char * _filename = m_filename.toStdString().c_str();
		cout << _filename << endl;
		readASCIstl(_filename, mesh);
		InitMesh(mesh); //�����������ڽӵ�
		for (vector<int>::iterator it = mesh.badPointsId.begin(); it != mesh.badPointsId.end(); ++it) {
			mesh.Verts[*it].color = -1;
		}
		setColor(mesh);
		selectMode = 1;
		m_filename.clear();
	}
	
	updateGL();
}