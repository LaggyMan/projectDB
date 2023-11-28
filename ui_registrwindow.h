/********************************************************************************
** Form generated from reading UI file 'registrwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRWINDOW_H
#define UI_REGISTRWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegistrWindow
{
public:
    QGroupBox *groupBox_2;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *nameregistr;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QLineEdit *loginregistr;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *passwordregistr;
    QPushButton *pushButton_2;
    QLabel *label_5;

    void setupUi(QWidget *RegistrWindow)
    {
        if (RegistrWindow->objectName().isEmpty())
            RegistrWindow->setObjectName(QString::fromUtf8("RegistrWindow"));
        RegistrWindow->resize(792, 532);
        groupBox_2 = new QGroupBox(RegistrWindow);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(250, 130, 271, 211));
        layoutWidget_2 = new QWidget(groupBox_2);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(0, 30, 272, 180));
        verticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        nameregistr = new QLineEdit(layoutWidget_2);
        nameregistr->setObjectName(QString::fromUtf8("nameregistr"));

        horizontalLayout_3->addWidget(nameregistr);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_7 = new QLabel(layoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        loginregistr = new QLineEdit(layoutWidget_2);
        loginregistr->setObjectName(QString::fromUtf8("loginregistr"));

        horizontalLayout_5->addWidget(loginregistr);


        verticalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        passwordregistr = new QLineEdit(layoutWidget_2);
        passwordregistr->setObjectName(QString::fromUtf8("passwordregistr"));

        horizontalLayout_4->addWidget(passwordregistr);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(verticalLayout_4);

        pushButton_2 = new QPushButton(layoutWidget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_3->addWidget(pushButton_2);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, -11, 271, 51));

        retranslateUi(RegistrWindow);

        QMetaObject::connectSlotsByName(RegistrWindow);
    } // setupUi

    void retranslateUi(QWidget *RegistrWindow)
    {
        RegistrWindow->setWindowTitle(QApplication::translate("RegistrWindow", "Form", nullptr));
        groupBox_2->setTitle(QString());
        label_3->setText(QApplication::translate("RegistrWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">\320\230\320\274\321\217:</span></p></body></html>", nullptr));
        label_7->setText(QApplication::translate("RegistrWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">\320\233\320\276\320\263\320\270\320\275:</span></p></body></html>", nullptr));
        label_4->setText(QApplication::translate("RegistrWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">\320\237\320\260\321\200\320\276\320\273\321\214:</span></p></body></html>", nullptr));
        pushButton_2->setText(QApplication::translate("RegistrWindow", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
        label_5->setText(QApplication::translate("RegistrWindow", "<html><head/><body><p align=\"center\"><span style=\" color:#0000ff;\">\320\240\320\265\320\263\320\270\321\201\321\202\321\200\320\260\321\206\320\270\321\217</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegistrWindow: public Ui_RegistrWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRWINDOW_H
