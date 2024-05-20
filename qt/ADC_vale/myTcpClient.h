#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QPushButton>
#include <QTcpSocket>
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>

class MyTcpClient : public QObject
{
    Q_OBJECT

public:
    MyTcpClient();
    QLabel *QlineEdit_input;
    QString host;
    quint16 port;

private slots:
    void disconnectFromHost();
    void connectToHost();
    void onConnected();
    void onDisconnected();
    void readData();

private:
    QTcpSocket *socket;

};

#endif // MYTCPCLIENT_H
