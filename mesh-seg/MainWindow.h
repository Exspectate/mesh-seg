#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QAction> 
#include <QtWidgets/QMenu> 
#include <QtWidgets/QMenuBar> 
#include <QtGui/QKeySequence> 
#include <QtWidgets/QToolBar> 
#include <QFileDialog>
#include <QtGui>
#include <QFile>
#include "ui_MainWindow.h"
#include "MeshViewer.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();
	void createActions();
	void createToolbar();

private:
	Ui::MainWindowClass ui;
	MeshViewer *m_Viewer;
	QAction *openMeshAction;
	QAction * renderOptions;

	QAction * viewPoints;
	QAction * viewWireframe;
	QAction * viewFlatlines;
	QAction * viewFlat;
	QAction * viewSmooth;
	QAction * viewBoundary;
	QAction * viewTexture;
	QAction * takeSnapshot;
	QAction * viewHarmonicField;
	QAction * viewIsolines;
	QAction * viewFinalCut;

	QToolBar * fileToolbar;
	QToolBar * viewToolbar;
	QToolBar * editToolbar;

	QActionGroup * drawModeGroup;

	QAction * selectAction;
	QAction * strokeBrush;


};
