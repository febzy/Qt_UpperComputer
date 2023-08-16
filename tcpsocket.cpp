#include "tcpsocket.h"
#include "ui_tcpsocket.h"


QString currentTime = QTime::currentTime().toString("HH:mm:ss:zzz");
QString upperComputer = "upperComputer";
QString LiDAR = "LMS111-10100";


tcpSocket::tcpSocket(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tcpSocket)
{
    ui->setupUi(this);

    TcpSocket = new QTcpSocket(this);


}

tcpSocket::~tcpSocket()
{
    delete ui;
}

void tcpSocket::on_pushButton_buildConnect_clicked()
{
    QString ipAddress = "192.168.0.1";
    quint16 port = 2112;
    TcpSocket->connectToHost(ipAddress, port);


    if (TcpSocket->waitForConnected(3000))
    {
        ui->textEdit_receiveData->append(QString("<font color='green'>[%1]%2 : %3</font>").arg(currentTime).arg(upperComputer).arg("Connected to LiDAR"));
        // 连接成功，进行登录
        QString hexMessage = "02734D4E205365744163636573734D6F646520303320463437323437343403";
        QByteArray hexData = QByteArray::fromHex(hexMessage.toUtf8());
        TcpSocket->write(hexData);

        //登录验证
        if (TcpSocket->waitForReadyRead(3000)) {
            QByteArray response = TcpSocket->readAll();
            QString messageHEX = response.toHex(' ');
            ui->textEdit_receiveData->append(QString("<font color='blue'>[%1]%2 : %3</font>").arg(currentTime).arg(LiDAR).arg(messageHEX));
            if (messageHEX == "02 73 41 4e 20 53 65 74 41 63 63 65 73 73 4d 6f 64 65 20 31 03") {
                ui->textEdit_receiveData->append(QString("<font color='green'>[%1]%2 : %3</font>").arg(currentTime).arg(upperComputer).arg("Success to log in"));
                //采用Qt5以后版本的连接方式
                connect(TcpSocket, &QTcpSocket::readyRead, TcpSocket, [=]() {
                    receiveMessage();
                });
            } else {

                ui->textEdit_receiveData->append(QString("<font color='green'>[%1]%2 : %3</font>").arg(currentTime).arg(upperComputer).arg("Failed to log in"));

            }
        }
    } else {

        ui->textEdit_receiveData->append(QString("<font color='green'>[%1]%2 : %3</font>").arg(currentTime).arg(upperComputer).arg("Failed to connect to LiDAR"));

    }
}


void tcpSocket::on_pushButton_send_clicked()
{
    QString message = ui->textEdit_sendData->toPlainText();

    if(!message.isEmpty()){
        // 将HEX字符串转换为字节数组
        QByteArray hexData = QByteArray::fromHex(message.toUtf8());

        TcpSocket->write(hexData);
        ui->textEdit_receiveData->append(QString("<font color='green'>[%1]%2 : %3</font>").arg(currentTime).arg(upperComputer).arg(message));
        ui->textEdit_sendData->setText("");
    }
}

void tcpSocket::receiveMessage()
{
    QString framedata;
    QByteArray response = TcpSocket->readAll();

    //判断是否为空
    if(!response.isEmpty()){
        if(ui->checkBox_isHex->isChecked()){
            framedata = QString(response);
        }else{
            framedata = response.toHex(' ').trimmed().toUpper();
        }
        //时间戳
        framedata = QString("<font color='blue'>[%1]%2 : %3</font>").arg(currentTime).arg(LiDAR).arg(framedata);
        ui->textEdit_receiveData->append(framedata);

    }


}

void tcpSocket::on_pushButton_openLiDAR_clicked()
{
    //将hexMessage转换为字节数组，更适合网络通讯协议信息传输
    QString hexMessage = "02 73 4D 4E 20 4C 4D 43 73 74 61 72 74 6D 65 61 73 03";
    QByteArray hexData = QByteArray::fromHex(hexMessage.toUtf8());
    TcpSocket->write(hexData);
    ui->textEdit_receiveData->append(QString("<font color='green'>[%1]%2 : %3</font>").arg(currentTime).arg(upperComputer).arg(hexMessage));
}


void tcpSocket::on_pushButton_stopLiDAR_clicked()
{
    QString hexMessage = "02 73 4D 4E 20 4C 4D 43 73 74 6F 70 6D 65 61 73 03";
    QByteArray hexData = QByteArray::fromHex(hexMessage.toUtf8());
    TcpSocket->write(hexData);
    ui->textEdit_receiveData->append(QString("<font color='green'>[%1]%2 : %3</font>").arg(currentTime).arg(upperComputer).arg(hexMessage));
}


void tcpSocket::on_pushButton_startScan_clicked()
{
    QString hexMessage = "02 73 45 4E 20 4C 4D 44 73 63 61 6E 64 61 74 61 20 31 03";
    QByteArray hexData = QByteArray::fromHex(hexMessage.toUtf8());
    TcpSocket->write(hexData);
    ui->textEdit_receiveData->append(QString("<font color='green'>[%1]%2 : %3</font>").arg(currentTime).arg(upperComputer).arg(hexMessage));
}


void tcpSocket::on_pushButton_stopScan_clicked()
{
    QString hexMessage = "02 73 45 4E 20 4C 4D 44 73 63 61 6E 64 61 74 61 20 30 03";
    QByteArray hexData = QByteArray::fromHex(hexMessage.toUtf8());
    TcpSocket->write(hexData);
    ui->textEdit_receiveData->append(QString("<font color='green'>[%1]%2 : %3</font>").arg(currentTime).arg(upperComputer).arg(hexMessage));
}


void tcpSocket::on_pushButton_singleScan_clicked()
{
    QString hexMessage = "02 73 52 4E 20 4C 4D 44 73 63 61 6E 64 61 74 61 03";
    QByteArray hexData = QByteArray::fromHex(hexMessage.toUtf8());
    TcpSocket->write(hexData);
    ui->textEdit_receiveData->append(QString("<font color='green'>[%1]%2 : %3</font>").arg(currentTime).arg(upperComputer).arg(hexMessage));
}


void tcpSocket::on_pushButton_saveDataToFile_clicked()
{
    QString data = ui->textEdit_receiveData->toPlainText();

    if (data.isEmpty())
    {
        QMessageBox::information(this, "提示", "数据内容空");
        return;
    }
    QString curPath = QDir::currentPath();            //获取系统当前目录
    QString dlgTitle = "保存文件";                     //对话框标题
    QString filter = "文本文件(*.txt);;所有文件(*.*)";  //文件过滤器
    QString filename = QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);


    if (filename.isEmpty())
    {
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    /*保存文件*/
    QTextStream stream(&file);
    stream << data;
    file.close();
}

