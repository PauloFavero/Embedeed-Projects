/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *AccLayout;
    QLineEdit *AccX_Data;
    QLineEdit *AccY_Data;
    QLineEdit *AccZ_Data;
    QPushButton *Send_Button;
    QProgressBar *Temp_bar;
    QProgressBar *Press_bar;
    QPushButton *ChoseLux;
    QLineEdit *Send_Data;
    QTextEdit *textEdit_2;
    QLabel *AccY;
    QLabel *AccZ;
    QLabel *AccX;
    QLabel *GyroX;
    QLabel *GyroZ;
    QLabel *GyroY;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *GyroLayout;
    QLineEdit *GyroX_Data;
    QLineEdit *GyroY_Data;
    QLineEdit *GyroZ_Data;
    QLabel *Temp;
    QLabel *Press;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(753, 402);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 391, 241));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(110, 250, 91, 83));
        AccLayout = new QVBoxLayout(verticalLayoutWidget);
        AccLayout->setSpacing(6);
        AccLayout->setContentsMargins(11, 11, 11, 11);
        AccLayout->setObjectName(QStringLiteral("AccLayout"));
        AccLayout->setContentsMargins(0, 0, 0, 0);
        AccX_Data = new QLineEdit(verticalLayoutWidget);
        AccX_Data->setObjectName(QStringLiteral("AccX_Data"));

        AccLayout->addWidget(AccX_Data);

        AccY_Data = new QLineEdit(verticalLayoutWidget);
        AccY_Data->setObjectName(QStringLiteral("AccY_Data"));

        AccLayout->addWidget(AccY_Data);

        AccZ_Data = new QLineEdit(verticalLayoutWidget);
        AccZ_Data->setObjectName(QStringLiteral("AccZ_Data"));

        AccLayout->addWidget(AccZ_Data);

        Send_Button = new QPushButton(centralWidget);
        Send_Button->setObjectName(QStringLiteral("Send_Button"));
        Send_Button->setGeometry(QRect(670, 310, 82, 23));
        Temp_bar = new QProgressBar(centralWidget);
        Temp_bar->setObjectName(QStringLiteral("Temp_bar"));
        Temp_bar->setGeometry(QRect(400, 30, 118, 23));
        Temp_bar->setValue(24);
        Press_bar = new QProgressBar(centralWidget);
        Press_bar->setObjectName(QStringLiteral("Press_bar"));
        Press_bar->setGeometry(QRect(400, 90, 118, 23));
        Press_bar->setValue(24);
        ChoseLux = new QPushButton(centralWidget);
        ChoseLux->setObjectName(QStringLiteral("ChoseLux"));
        ChoseLux->setGeometry(QRect(570, 310, 82, 23));
        Send_Data = new QLineEdit(centralWidget);
        Send_Data->setObjectName(QStringLiteral("Send_Data"));
        Send_Data->setGeometry(QRect(670, 280, 81, 21));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(570, 280, 81, 21));
        AccY = new QLabel(centralWidget);
        AccY->setObjectName(QStringLiteral("AccY"));
        AccY->setGeometry(QRect(20, 278, 119, 22));
        AccZ = new QLabel(centralWidget);
        AccZ->setObjectName(QStringLiteral("AccZ"));
        AccZ->setGeometry(QRect(20, 306, 119, 22));
        AccX = new QLabel(centralWidget);
        AccX->setObjectName(QStringLiteral("AccX"));
        AccX->setGeometry(QRect(20, 250, 119, 22));
        GyroX = new QLabel(centralWidget);
        GyroX->setObjectName(QStringLiteral("GyroX"));
        GyroX->setGeometry(QRect(210, 250, 119, 22));
        GyroZ = new QLabel(centralWidget);
        GyroZ->setObjectName(QStringLiteral("GyroZ"));
        GyroZ->setGeometry(QRect(210, 306, 119, 22));
        GyroY = new QLabel(centralWidget);
        GyroY->setObjectName(QStringLiteral("GyroY"));
        GyroY->setGeometry(QRect(210, 278, 119, 22));
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(300, 250, 91, 83));
        GyroLayout = new QVBoxLayout(verticalLayoutWidget_2);
        GyroLayout->setSpacing(6);
        GyroLayout->setContentsMargins(11, 11, 11, 11);
        GyroLayout->setObjectName(QStringLiteral("GyroLayout"));
        GyroLayout->setContentsMargins(0, 0, 0, 0);
        GyroX_Data = new QLineEdit(verticalLayoutWidget_2);
        GyroX_Data->setObjectName(QStringLiteral("GyroX_Data"));

        GyroLayout->addWidget(GyroX_Data);

        GyroY_Data = new QLineEdit(verticalLayoutWidget_2);
        GyroY_Data->setObjectName(QStringLiteral("GyroY_Data"));

        GyroLayout->addWidget(GyroY_Data);

        GyroZ_Data = new QLineEdit(verticalLayoutWidget_2);
        GyroZ_Data->setObjectName(QStringLiteral("GyroZ_Data"));

        GyroLayout->addWidget(GyroZ_Data);

        Temp = new QLabel(centralWidget);
        Temp->setObjectName(QStringLiteral("Temp"));
        Temp->setGeometry(QRect(410, 10, 91, 16));
        Press = new QLabel(centralWidget);
        Press->setObjectName(QStringLiteral("Press"));
        Press->setGeometry(QRect(410, 70, 91, 16));
        MainWindow->setCentralWidget(centralWidget);
        graphicsView->raise();
        verticalLayoutWidget->raise();
        Send_Button->raise();
        Temp_bar->raise();
        Press_bar->raise();
        ChoseLux->raise();
        Send_Data->raise();
        textEdit_2->raise();
        AccY->raise();
        AccZ->raise();
        AccX->raise();
        GyroX->raise();
        GyroZ->raise();
        GyroY->raise();
        verticalLayoutWidget_2->raise();
        Temp->raise();
        Press->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 753, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        Send_Button->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        ChoseLux->setText(QApplication::translate("MainWindow", "Lux/Dis", Q_NULLPTR));
        AccY->setText(QApplication::translate("MainWindow", "Accleration Y:", Q_NULLPTR));
        AccZ->setText(QApplication::translate("MainWindow", "Accleration Z:", Q_NULLPTR));
        AccX->setText(QApplication::translate("MainWindow", "Accleration X:", Q_NULLPTR));
        GyroX->setText(QApplication::translate("MainWindow", "Gyroscope X:", Q_NULLPTR));
        GyroZ->setText(QApplication::translate("MainWindow", "Gyroscope Z:", Q_NULLPTR));
        GyroY->setText(QApplication::translate("MainWindow", "Gyroscope Y:", Q_NULLPTR));
        Temp->setText(QApplication::translate("MainWindow", "Temperature", Q_NULLPTR));
        Press->setText(QApplication::translate("MainWindow", "Pression", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
