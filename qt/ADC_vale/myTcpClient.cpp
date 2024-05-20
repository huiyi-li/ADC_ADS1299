#include"myTcpClient.h"



MyTcpClient::MyTcpClient()
{
    // 创建TCP客户端
    socket = new QTcpSocket(this);

    // 连接connectToHost信号到槽函数
    connect(this, &MyTcpClient::connectToHost, this, &MyTcpClient::connectToHost);

    // 连接connected信号到槽函数
    connect(socket, &QTcpSocket::connected, this, &MyTcpClient::onConnected);

    // 连接disconnected信号到槽函数
    connect(socket, &QTcpSocket::disconnected, this, &MyTcpClient::onDisconnected);

    // 连接readyRead信号到槽函数
    connect(socket, &QTcpSocket::readyRead, this, &MyTcpClient::readData);
}

void MyTcpClient::connectToHost()
{
    // 连接到主机和端口
    socket->connectToHost(host, port);
}

void MyTcpClient::disconnectFromHost()
{
    // 断开连接
    socket->disconnectFromHost();
}

void MyTcpClient::onConnected()
{
    QlineEdit_input->setText("连接成功");
    qDebug() << "连接成功！";
}

void MyTcpClient::onDisconnected()
{
    QlineEdit_input->setText("连接断开");
    qDebug() << "连接断开！";
}

void MyTcpClient::readData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket) {
        // 读取数据
        QByteArray data = socket->readAll();
        qDebug() << "收到数据：" << data;
    }
}
