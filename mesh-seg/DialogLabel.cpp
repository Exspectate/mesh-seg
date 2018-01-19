#include "DialogLabel.h"


DialogLabel::DialogLabel(QWidget *parent)
	: QDialog(parent)
{
	//ui.setupUi(this);
	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->setColumnStretch(0, 1);
	gridLayout->setColumnStretch(1, 3);

	gridLayout->setMargin(10);

	QLabel *lbl_caption = new QLabel(QWidget::tr("Parts:"));
	select_parts = new QComboBox();

	select_parts->addItem(QWidget::tr("机身头部椭球"));
	select_parts->addItem(QWidget::tr("机身椭圆柱1"));
	select_parts->addItem(QWidget::tr("机身椭圆柱2"));
	select_parts->addItem(QWidget::tr("左V型舵"));
	select_parts->addItem(QWidget::tr("右V型舵"));
	select_parts->addItem(QWidget::tr("俯仰舵"));
	//select_parts->insertItem(2, tr("Insert item"));
	//select_parts->insertSeparator(2);

	gridLayout->addWidget(lbl_caption, 0, 0);
	gridLayout->addWidget(select_parts, 0, 1);

	QHBoxLayout *bomLayout = new QHBoxLayout;
	QPushButton *btn = new QPushButton(QWidget::tr("确定"));
	connect(btn, SIGNAL(clicked()), this, SLOT(getPartNum()));

	bomLayout->addStretch();
	bomLayout->addWidget(btn);
	bomLayout->addStretch();

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(gridLayout);
	mainLayout->addLayout(bomLayout);

	setLayout(mainLayout);
	setWindowTitle(tr("Part Options"));
	resize(300, 150);

}


//DialogLabel::DialogLabel(MeshViewer *viewer, QWidget * parent)
//	: QDialog(parent)
//{
//	//ui.setupUi(this);
//	QGridLayout *gridLayout = new QGridLayout;
//	gridLayout->setColumnStretch(0, 1);
//	gridLayout->setColumnStretch(1, 3);
//
//	gridLayout->setMargin(10);
//
//	QLabel *lbl_caption = new QLabel(QWidget::tr("Parts:"));
//	select_parts = new QComboBox();
//
//	select_parts->addItem(QWidget::tr("机身头部椭球"));
//	select_parts->addItem(QWidget::tr("机身椭圆柱1"));
//	select_parts->addItem(QWidget::tr("机身椭圆柱2"));
//	select_parts->addItem(QWidget::tr("左V型舵"));
//	select_parts->addItem(QWidget::tr("右V型舵"));
//	select_parts->addItem(QWidget::tr("俯仰舵"));
//	//select_parts->insertItem(2, tr("Insert item"));
//	//select_parts->insertSeparator(2);
//
//	gridLayout->addWidget(lbl_caption, 0, 0);
//	gridLayout->addWidget(select_parts, 0, 1);
//
//	QHBoxLayout *bomLayout = new QHBoxLayout;
//	QPushButton *btn = new QPushButton(QWidget::tr("确定"));
//	connect(btn, SIGNAL(clicked()), this, SLOT(getPartNum()));
//
//	bomLayout->addStretch();
//	bomLayout->addWidget(btn);
//	bomLayout->addStretch();
//
//	QVBoxLayout *mainLayout = new QVBoxLayout;
//	mainLayout->addLayout(gridLayout);
//	mainLayout->addLayout(bomLayout);
//
//	setLayout(mainLayout);
//	setWindowTitle(tr("Part Options"));
//	resize(300, 150);
//
//}

DialogLabel::~DialogLabel()
{
}

int DialogLabel::getTargetNum()
{
	return targetPart;
}



void DialogLabel::getPartNum() {
	if (select_parts->currentText() == QString("机身头部椭球"))
		targetPart = 1;
	else if (select_parts->currentText() == QString("机身椭圆柱1"))
		targetPart = 2;
	else if (select_parts->currentText() == QString("机身椭圆柱2"))
		targetPart = 3;
	else if (select_parts->currentText() == QString("左V型舵"))
		targetPart = 5;
	else if (select_parts->currentText() == QString("右V型舵"))
		targetPart = 6;
	else if (select_parts->currentText() == QString("俯仰舵"))
		targetPart = 4;
	close();
}