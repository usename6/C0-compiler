/********************************************************************************
** Form generated from reading UI file 'work.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORK_H
#define UI_WORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_work
{
public:
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_3;

    void setupUi(QDialog *work)
    {
        if (work->objectName().isEmpty())
            work->setObjectName(QStringLiteral("work"));
        work->resize(634, 400);
        lineEdit = new QLineEdit(work);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(200, 140, 231, 31));
        lineEdit_2 = new QLineEdit(work);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(200, 200, 231, 31));
        label = new QLabel(work);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(116, 150, 61, 20));
        label_2 = new QLabel(work);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(110, 210, 71, 16));
        pushButton = new QPushButton(work);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 290, 89, 25));
        pushButton_2 = new QPushButton(work);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(390, 290, 89, 25));
        label_3 = new QLabel(work);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(240, 50, 131, 31));

        retranslateUi(work);

        QMetaObject::connectSlotsByName(work);
    } // setupUi

    void retranslateUi(QDialog *work)
    {
        work->setWindowTitle(QApplication::translate("work", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("work", "Input file", Q_NULLPTR));
        label_2->setText(QApplication::translate("work", "output file", Q_NULLPTR));
        pushButton->setText(QApplication::translate("work", "exit", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("work", "confirm", Q_NULLPTR));
        label_3->setText(QApplication::translate("work", "C0-Compile-master", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class work: public Ui_work {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORK_H
