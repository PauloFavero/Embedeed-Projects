#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore>
#include <QDebug>

#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>

#include <libpcan.h>        // /usr/include/libpcan.h
#include <fcntl.h>    // O_RDWR
#include <signal.h>
#include <unistd.h>   // exit

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openCANPort();
    void sendCANMessage(int msg);
    void receiveCANMessage();

public slots:

    void onButSendClicked();
         void onTimer_Tick();



private:

    HANDLE h;
    TPCANRdMsg pMsgBuff;

    Ui::MainWindow  *ui;
     QGridLayout     *m_layout;
     QPushButton     *but_switch;
     QLineEdit       *receive_box_lum_dis,*receive_box_temp,*receive_box_speed,*receive_box_press;

    QTimer *timer_tick;
};

#endif // MAINWINDOW_H
