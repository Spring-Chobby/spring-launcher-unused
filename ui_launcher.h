/********************************************************************************
** Form generated from reading UI file 'launcher.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAUNCHER_H
#define UI_LAUNCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Launcher
{
public:
    QWidget *centralWidget;
    QPushButton *btnAction;
    QProgressBar *prDownload;
    QLabel *lblStatus;
    QLabel *lblTitle;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Launcher)
    {
        if (Launcher->objectName().isEmpty())
            Launcher->setObjectName(QStringLiteral("Launcher"));
        Launcher->resize(397, 223);
        centralWidget = new QWidget(Launcher);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        btnAction = new QPushButton(centralWidget);
        btnAction->setObjectName(QStringLiteral("btnAction"));
        btnAction->setGeometry(QRect(280, 90, 91, 61));
        prDownload = new QProgressBar(centralWidget);
        prDownload->setObjectName(QStringLiteral("prDownload"));
        prDownload->setGeometry(QRect(10, 100, 211, 41));
        prDownload->setValue(0);
        lblStatus = new QLabel(centralWidget);
        lblStatus->setObjectName(QStringLiteral("lblStatus"));
        lblStatus->setGeometry(QRect(10, 70, 211, 31));
        lblTitle = new QLabel(centralWidget);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(140, 10, 67, 17));
        lblTitle->setLayoutDirection(Qt::LeftToRight);
        lblTitle->setAlignment(Qt::AlignCenter);
        Launcher->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Launcher);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 397, 25));
        Launcher->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Launcher);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Launcher->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Launcher);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Launcher->setStatusBar(statusBar);

        retranslateUi(Launcher);

        QMetaObject::connectSlotsByName(Launcher);
    } // setupUi

    void retranslateUi(QMainWindow *Launcher)
    {
        Launcher->setWindowTitle(QApplication::translate("Launcher", "Launcher", 0));
        btnAction->setText(QApplication::translate("Launcher", "Action", 0));
        lblStatus->setText(QApplication::translate("Launcher", "Status Label", 0));
        lblTitle->setText(QApplication::translate("Launcher", "Title Label", 0));
    } // retranslateUi

};

namespace Ui {
    class Launcher: public Ui_Launcher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAUNCHER_H
