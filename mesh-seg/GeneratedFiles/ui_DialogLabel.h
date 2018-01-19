/********************************************************************************
** Form generated from reading UI file 'DialogLabel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLABEL_H
#define UI_DIALOGLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogLabel
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QComboBox *select_part;
    QPushButton *pushButton;

    void setupUi(QDialog *DialogLabel)
    {
        if (DialogLabel->objectName().isEmpty())
            DialogLabel->setObjectName(QStringLiteral("DialogLabel"));
        DialogLabel->resize(559, 231);
        gridLayout = new QGridLayout(DialogLabel);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(DialogLabel);
        widget->setObjectName(QStringLiteral("widget"));
        select_part = new QComboBox(widget);
        select_part->setObjectName(QStringLiteral("select_part"));
        select_part->setGeometry(QRect(150, 70, 241, 22));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(240, 140, 75, 31));

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(DialogLabel);

        QMetaObject::connectSlotsByName(DialogLabel);
    } // setupUi

    void retranslateUi(QDialog *DialogLabel)
    {
        DialogLabel->setWindowTitle(QApplication::translate("DialogLabel", "DialogLabel", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DialogLabel", "\347\241\256\350\256\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogLabel: public Ui_DialogLabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLABEL_H
