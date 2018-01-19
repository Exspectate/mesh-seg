#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	m_Viewer = new MeshViewer();
	setCentralWidget(m_Viewer);
	createActions();
	createToolbar();
	setAcceptDrops(true);
//	ui.setupUi(this);
}
MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
	openMeshAction = new QAction(tr("&Open Mesh"), this);		//打开文件
	openMeshAction->setIcon(QIcon(":/MainWindow/images/open.png"));
	openMeshAction->setShortcut(QKeySequence::Open);
	openMeshAction->setStatusTip(tr("Open a mesh file"));
	connect(openMeshAction, SIGNAL(triggered()),m_Viewer,SLOT(openMesh()));

	/*viewPoints = new QAction(tr("&Points"), this);
	viewPoints->setIcon(QIcon(":/MainWindow/images/points.png"));
	viewPoints->setText(tr("Draw Points"));
	viewPoints->setStatusTip(tr("Points"));
	viewPoints->setCheckable(true);
	viewPoints->setChecked(false);

	renderOptions = new QAction(tr("&Render"), this);
	renderOptions->setIcon(QIcon(":/MainWindow/images/render.png"));
	renderOptions->setText(tr("Set render options"));
	renderOptions->setStatusTip(tr("Render"));

	viewWireframe = new QAction(tr("&Wireframe"), this);
	viewWireframe->setIcon(QIcon(":/MainWindow/images/wireframe.png"));
	viewWireframe->setText(tr("Draw Wireframe"));
	viewWireframe->setStatusTip(tr("Wireframe"));
	viewWireframe->setCheckable(true);
	viewWireframe->setChecked(false);*/


	viewFlatlines = new QAction(tr("Flat&lines"), this);		//显示网格模型
	viewFlatlines->setIcon(QIcon(":/MainWindow/images/flatlines.png"));
	viewFlatlines->setText(tr("Draw Flatlines"));
	viewFlatlines->setStatusTip(tr("Flatlines"));
//	viewFlatlines->setCheckable(true);
//	viewFlatlines->setChecked(false);
	connect(viewFlatlines, SIGNAL(triggered()), m_Viewer, SLOT(showFlatlines()));


	viewFlat = new QAction(tr("&Flat"), this);		//显示原模型
	viewFlat->setIcon(QIcon(":/MainWindow/images/flat.png"));
	viewFlat->setText(tr("Draw Flat"));
	viewFlat->setStatusTip(tr("Flat"));
//	viewFlat->setCheckable(true);
//	viewFlat->setChecked(false);
	connect(viewFlat, SIGNAL(triggered()), m_Viewer, SLOT(showFlat()));

	/*viewSmooth = new QAction(tr("&Smooth"), this);
	viewSmooth->setIcon(QIcon(":/MainWindow/images/smooth.png"));
	viewSmooth->setText(tr("Draw Smooth"));
	viewSmooth->setStatusTip(tr("Smooth"));
	viewSmooth->setCheckable(true);
	viewSmooth->setChecked(false);

	viewBoundary = new QAction(this);
	viewBoundary->setIcon(QIcon(":/MainWindow/images/boundary.png"));
	viewBoundary->setText(tr("Draw Boundary"));
	viewBoundary->setStatusTip(tr("Boundary"));
	viewBoundary->setCheckable(true);
	viewBoundary->setChecked(false);


	viewTexture = new QAction(tr("&Texture"), this);
	viewTexture->setIcon(QIcon(":/MainWindow/images/bunny-alpha0.png"));
	viewTexture->setText(tr("Draw Texture"));
	viewTexture->setStatusTip(tr("Texture"));
	viewTexture->setCheckable(true);
	viewTexture->setChecked(false);

	takeSnapshot = new QAction(tr("&Snapshot"), this);
	takeSnapshot->setIcon(QIcon(":/MainWindow/images/camera.png"));
	takeSnapshot->setText(tr("Take snapshot"));
	takeSnapshot->setStatusTip(tr("Snapshot"));*/

	selectAction = new QAction(this);			//显示特征线
	selectAction->setIcon(QIcon(":/MainWindow/images/38961-200.png"));
	selectAction->setText(tr("Featureline recognition"));
	selectAction->setStatusTip(tr("Featureline recognition"));
//	selectAction->setCheckable(true);
//	selectAction->setChecked(false);
	connect(selectAction, SIGNAL(triggered()), m_Viewer, SLOT(showFeatureLineMesh()));
	
	/*strokeBrush = new QAction(this);
	strokeBrush->setIcon(QIcon(":/MainWindow/images/brush.png"));
	strokeBrush->setText(tr("Draw a stroke"));
	strokeBrush->setStatusTip(tr("Draw a stroke"));
	connect(strokeBrush, SIGNAL(triggered()), m_Viewer, SLOT(showFeatureLineMesh()));*/
	//strokeBrush->setCheckable(true);
	//strokeBrush->setChecked(false);

	/*
	viewHarmonicField = new QAction(tr("&Show harmonic field"), this);
	viewHarmonicField->setIcon(QIcon(":/MainWindow/images/paint.png"));
	viewHarmonicField->setStatusTip(tr("Show harmonic field"));


	viewIsolines = new QAction(tr("&Show isolines"), this);
	viewIsolines->setIcon(QIcon(":/MainWindow/images/show-iso.png"));
	viewIsolines->setStatusTip(tr("Show isolines"));*/

	viewFinalCut = new QAction(tr("&Show final cut"), this);
	viewFinalCut->setIcon(QIcon(":/MainWindow/images/cut.png"));
	viewFinalCut->setStatusTip(tr("Show final cut"));
	connect(viewFinalCut, SIGNAL(triggered()), m_Viewer, SLOT(cutMesh()));
}

void MainWindow::createToolbar()
{
	fileToolbar = addToolBar(tr("&File"));
	fileToolbar->addAction(openMeshAction);

	editToolbar = addToolBar(tr("&Edit"));
	//editToolbar->addAction(strokeBrush);
	editToolbar->addAction(selectAction);
	//editToolbar->addAction(viewHarmonicField);
	//editToolbar->addAction(viewIsolines);
	editToolbar->addAction(viewFinalCut);

	viewToolbar = addToolBar(tr("&View"));
//	viewToolbar->addAction(renderOptions);
	//viewToolbar->addAction(viewTexture);
	//viewToolbar->addAction(viewPoints);
	//viewToolbar->addAction(viewWireframe);
	viewToolbar->addAction(viewFlatlines);
	viewToolbar->addAction(viewFlat);
	//viewToolbar->addAction(viewSmooth);
	//viewToolbar->addAction(viewBoundary);

	drawModeGroup = new QActionGroup(this);
	//drawModeGroup->addAction(viewPoints);
	//drawModeGroup->addAction(viewWireframe);
	drawModeGroup->addAction(viewFlatlines);
	drawModeGroup->addAction(viewFlat);
	//drawModeGroup->addAction(viewSmooth);
	//drawModeGroup->addAction(viewTexture);
}
