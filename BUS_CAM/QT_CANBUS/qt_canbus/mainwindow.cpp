#include "mainwindow.h"
#include "ui_mainwindow.h"

#define DEFAULT_NODE "/dev/pcanusb32"

//===============================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QWidget *zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);

    but_switch = new QPushButton("Luminosite/Distance");
    m_layout = new QGridLayout();

    QLabel *label_lum_dis = new QLabel;
    label_lum_dis->setText("Luminosite/Distance");
    QLabel *label_temp = new QLabel;
    label_temp->setText("Temperature");
    QLabel *label_to_press = new QLabel;
    label_to_press->setText("Pression");
    QLabel *label_to_speed = new QLabel;
    label_to_speed->setText("vitesse du vent");

    m_layout->addWidget(but_switch,1,0);


    m_layout->addWidget(label_lum_dis,1,1);
    m_layout->addWidget(label_temp,1,2);
    m_layout->addWidget(label_to_press,1,3);
    m_layout->addWidget(label_to_speed,1,4);


    receive_box_lum_dis = new QLineEdit();
    receive_box_temp = new QLineEdit();
    receive_box_press = new QLineEdit();
    receive_box_speed = new QLineEdit();

    m_layout->addWidget(receive_box_lum_dis,2,1);
    m_layout->addWidget(receive_box_temp,2,2);
    m_layout->addWidget(receive_box_press,2,3);
    m_layout->addWidget(receive_box_speed,2,4);

    zoneCentrale->setLayout(m_layout);

    openCANPort();

    timer_tick = new QTimer();
    connect( timer_tick, SIGNAL(timeout()), this, SLOT(onTimer_Tick()));

    connect(but_switch,SIGNAL(clicked()),this,SLOT(onButSendClicked()));
    timer_tick -> start(10); // in ms
}
//===============================================================

MainWindow::~MainWindow()
{
    delete ui;
}

//===============================================================
void MainWindow::openCANPort()
{
    const char *szDevNode = DEFAULT_NODE;

    h=LINUX_CAN_Open(szDevNode, O_RDWR);
    if (!h)
        {
            printf("can't open %s\n", szDevNode);
        }
    CAN_Init(h, CAN_BAUD_500K,  CAN_INIT_TYPE_ST);         // BTR0BTR1	bitrate code in hex (default=0x1c (500 kbps))
    CAN_Status(h); // Clear Status

}
//===============================================================
void MainWindow::onButSendClicked()
{
    static bool lum_dis = 0;

    lum_dis=!lum_dis;

    if(lum_dis == 0){
        (*but_switch).setText("Distance");
    }

    else if(lum_dis == 1){
        (*but_switch).setText("Luminosite");
    }


    sendCANMessage(int(lum_dis));
}
//===============================================================
void MainWindow::sendCANMessage(int msg)
{
    TPCANMsg msgCAN;

    msgCAN.ID      =   0x4;
    msgCAN.MSGTYPE =   MSGTYPE_STANDARD;
    msgCAN.LEN     =   8;
    msgCAN.DATA    =   msg;



 LINUX_CAN_Write_Timeout(h, &msgCAN,0);

}
//===============================================================
void MainWindow::receiveCANMessage()
{


    LINUX_CAN_Read_Timeout(h, &pMsgBuff,1); // Timeout=1ms --> Non Bloquant
    receive_box_lum_dis->setText(QString::number((uint)(pMsgBuff.Msg.DATA[0])+(uint)(pMsgBuff.Msg.DATA[1]<<8)));
    receive_box_temp->setText(QString::number((uint)(pMsgBuff.Msg.DATA[2])));
    receive_box_press->setText(QString::number((uint)(pMsgBuff.Msg.DATA[3])));
    receive_box_speed->setText(QString::number((uint)(pMsgBuff.Msg.DATA[3])));


}
//===============================================================

void MainWindow::onTimer_Tick()
{
receiveCANMessage();
}


