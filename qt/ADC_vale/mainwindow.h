#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QWidget>
#include <QStackedWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QVBoxLayout>
#include <QSerialPortInfo>
#include <QPushButton>

#include "mycombox.h"
#include "myTcpClient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //标签创建并对齐
    QLabel *lablel_type;
    QLabel *lablel_mode;

    QStackedWidget *stackedWidgetMode;
    QGroupBox *GropBoxUart;
    QGroupBox *GropBoxTCP;
    QGroupBox *GropBoxBLE;

    //TCP标签
    QLabel *lablel_port;
    QLabel *lablel_IP;
    //串口标签
    QLabel *lablel_com;
    QLabel *lablel_baud;

    //创建下拉box
    QComboBox *combox_type;
    QComboBox *combox_mode;
    //tcp
    QLineEdit *lineEdit_ip;
    QLineEdit *lineEdit_port;
    //uart
    myComboBox *combox_com;
    QComboBox *combox_baud;

    //button
    QPushButton *open_button;
    QLabel *label_connect_state;

    //tcp
    MyTcpClient *tcpclied_ptr;

    MyTcpClient *myTcpClient;

    void handleButtonClick(void)
    {
        // 切换按钮的文本内容
        if (open_button->text() == "打开连接") {
            myTcpClient->QlineEdit_input = label_connect_state;
            QString ip_text = lineEdit_ip->text();
            QString port_text = lineEdit_port->text();
            myTcpClient->host = ip_text;
            myTcpClient->port = (quint16)port_text.toUInt();
            qDebug() << "QString: " << myTcpClient->host;
            qDebug() << "int: " << myTcpClient->port;
            open_button->setText("断开连接");
        } else {
            open_button->setText("打开连接");
        }

    }


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
