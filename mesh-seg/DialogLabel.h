#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif  
#pragma once

#include <QDialog>
#include <QLayout> 
#include <QtWidgets/QWidget>
#include <QLabel>
#include "MeshViewer.h"
#include "ui_DialogLabel.h"
class DialogLabel : public QDialog
{
	Q_OBJECT

public:
	DialogLabel(QWidget *parent = Q_NULLPTR);
//	DialogLabel(MeshViewer *viewer,QWidget *parent = 0);
	~DialogLabel();
	int getTargetNum();
	
	public slots:
	void getPartNum();
	

private:
	Ui::DialogLabel ui;
private:
	QComboBox *select_parts;
	int targetPart;
};
