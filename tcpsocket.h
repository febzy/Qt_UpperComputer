#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>				//时间的库
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QFile>


namespace Ui {
class tcpSocket;
}

class tcpSocket : public QMainWindow
{
    Q_OBJECT

public:
    explicit tcpSocket(QWidget *parent = nullptr);
    ~tcpSocket();

private slots:
    void on_pushButton_buildConnect_clicked();

    void on_pushButton_send_clicked();

    //接收消息函数
    void receiveMessage();

    void on_pushButton_openLiDAR_clicked();

    void on_pushButton_stopLiDAR_clicked();

    void on_pushButton_startScan_clicked();

    void on_pushButton_stopScan_clicked();

    void on_pushButton_singleScan_clicked();

    void on_pushButton_saveDataToFile_clicked();

private:
    Ui::tcpSocket *ui;

    QTcpSocket* TcpSocket;
};

#endif // TCPSOCKET_H
