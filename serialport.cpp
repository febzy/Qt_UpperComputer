#include "serialport.h"
#include "ui_serialport.h"
#include <QDebug>
#include <QMessageBox>
#include <QVector>


// 定义点云数据的结构体
struct PointCloudData {
    float x;
    float y;
    float z;
};

serialPort::serialPort(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serialPort)
{
    ui->setupUi(this);
    SerialPortInit();
}

serialPort::~serialPort()
{
    delete ui;
}

void serialPort::on_pushButton_return_clicked()
{

    //返回按钮，点击返回回到上个页面
    //当前功能：关闭当前页面
    this->close();//关闭当前页面
}

void serialPort::SerialPortInit()
{
    serial = new QSerialPort;

    //获取计算机中有效的端口号，将端口号交给控件
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        //在对象中设置串口
        serial->setPort(info);
        //以读写方式打开串口
        if(serial->open(QIODevice::ReadWrite))
        {
            //添加计算机中的端口,向ui中的comboBox_serialNum组件添加
            ui->comboBox_serialNum->addItem(info.portName());
            //关闭
            serial->close();
        }else
        {
            qDebug()<<"串口打开失败，请重试";
        }
    }
    //参数设置
    //设置默认波特率
    ui->comboBox_baud->addItem("115200");
    serial->setBaudRate(QSerialPort::Baud115200);
    //禁止点击
//    ui->comboBox_baud->setDisabled(true);
    //数据位
    ui->comboBox_dataBit->addItem("8");
    serial->setDataBits(QSerialPort::Data8);
    //停止位
    ui->comboBox_stopBit->addItem("1");
    serial->setStopBits(QSerialPort::OneStop);
    //检验位
    ui->comboBox_parityBit->addItem("无");
    serial->setParity(QSerialPort::NoParity);
    //刷新串口
    RefreshSerialPort(0);
    //信号
    //连接信号（readyRead）和槽（数据接收函数），readyRead()是串口自带的一种信号，用于接收信息
    connect(serial,&QSerialPort::readyRead,this,&serialPort::DataReceived);
    //连接信号（点击发送按钮）和槽（数据发送函数）
    connect(ui->pushButton_send,&QPushButton::clicked,this,&serialPort::DataSend);


}

void serialPort::RefreshSerialPort(int index)
{
    //存储串口名
    QStringList portNameList;

    if(index != 0)
    {
        //设置串口号
        serial->setPortName(ui->comboBox_serialNum->currentText());
    }else
    {
        //关闭串口号
        ui->comboBox_serialNum->clear();
        //遍历寻找新串口
        foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts()) {
            //append队列尾添加新数据
            portNameList.append(info.portName());
        }
        //注意导入数据，单个数据使用addItem，多个使用addItems
        ui->comboBox_serialNum->addItems(portNameList);
        //当前串口号为COM1
        ui->comboBox_serialNum->setCurrentIndex(1);
        //设置串口号
        serial->setPortName(ui->comboBox_serialNum->currentText());


    }
}

//发送信息槽函数
void serialPort::DataSend()
{
    serial->write(ui->textEdit_output->toPlainText().toLatin1());      // 串口发送数据
}

// 从串口中读取点云数据，并将其存储在 QVector 中
QVector<PointCloudData> readPointCloudData(QSerialPort& serialPort) {

    QVector<PointCloudData> data;
    // 读取点云数据
    QByteArray buffer = serialPort.readAll();
    if (!buffer.isEmpty()) {
        int numPoints = buffer.size() / sizeof(PointCloudData);
        PointCloudData* points = reinterpret_cast<PointCloudData*>(buffer.data());
        for (int i = 0; i < numPoints; ++i) {
            data.append(points[i]);
        }
    }

    return data;
}

//接收信息槽函数
void serialPort::DataReceived()
{

    QVector<PointCloudData> data;
    // 读取点云数据
    QByteArray buffer = serial->readAll();
    if (!buffer.isEmpty()) {
        int numPoints = buffer.size() / sizeof(PointCloudData);
        PointCloudData* points = reinterpret_cast<PointCloudData*>(buffer.data());
        for (int i = 0; i < numPoints; ++i) {
            data.append(points[i]);
        }
    }
    qDebug() << "dataZtjStr = " << buffer.data();
    //返回纯文本
    QString str = ui->textEdit_input->toPlainText();
    //保存数据，数据的返回是一行一行接收的
    str += tr(buffer);
    //清空之前数据
    ui->textEdit_input->clear();
    //将数据放入控件,append函数在textEdit控件中才能使用
    ui->textEdit_input->append(str);



//    //存储转换类型后的数据
//    char BUF[512] = {0};
//    //读取数据
//    QByteArray data = serial->readAll();

//    if(!data.isEmpty()){
//        //返回纯文本
//        QString str = ui->textEdit_input->toPlainText();
//        //保存数据，数据的返回是一行一行接收的
//        str += tr(data);
//        //清空之前数据
//        ui->textEdit_input->clear();
//        //将数据放入控件,append函数在textEdit控件中才能使用
//        ui->textEdit_input->append(str);
//        qDebug()<<"str info:"<<ui->textEdit_input->toPlainText();

//        int index = str.indexOf("\r\n");
//        if(index != -1){
//            snprintf(BUF,500,"%s", str.left(index + 2).toUtf8().data()); // QString转为char * 类型

//            qDebug() << "BUF info: " << BUF;        // 数据类型转换成功
//            str.remove(0,index + 2);

//            // 处理获取到的数据，将其放入对应的控件中
//            // .....

//        }
//    }
}

//打开串口槽函数
void serialPort::on_pushButton_openSerial_clicked()
{
    //打开的情况下先关闭
    if(serial->isOpen()){
        serial->clear();
        serial->close();
        //串口关闭的情况下，按钮显示打开串口，同时可以调整相应设置
        ui->pushButton_openSerial->setText("打开串口");
        ui->comboBox_baud->setDisabled(false);
        ui->comboBox_serialNum->setDisabled(false);
        ui->comboBox_dataBit->setDisabled(false);
        ui->comboBox_parityBit->setDisabled(false);
        ui->comboBox_stopBit->setDisabled(false);

        ui->pushButton_openSerial->setStyleSheet("color:green");
        LED(true);
        //清空数据
        ui->textEdit_input->clear();
        ui->textEdit_output->clear();
    }else{
        //当前选择串口的名字
        serial->setPortName(ui->comboBox_serialNum->currentText());
        //用ReadWrite 的模式尝试打开串口，无法收发数据时，发出警告
        if(!serial->open(QIODevice::ReadWrite)){
            QMessageBox::warning(this,tr("提示"),tr("串口打开失败!"),QMessageBox::Ok);
            return;
        }
        // 打开状态，按钮显示“关闭串口”
        ui->pushButton_openSerial->setText("关闭串口");
        ui->comboBox_baud->setDisabled(true);
        ui->comboBox_serialNum->setDisabled(true);
        ui->comboBox_dataBit->setDisabled(true);
        ui->comboBox_parityBit->setDisabled(true);
        ui->comboBox_stopBit->setDisabled(true);

        ui->pushButton_openSerial->setStyleSheet("color:red");
        LED(false);


    }
}

void  serialPort::LED(bool changeColor)
{
    if(changeColor == false)
    {
        // 显示绿色
        ui->LED->setStyleSheet("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 229, 0, 255), stop:1 rgba(255, 255, 255, 255));border-radius:12px;");
    }
    else
    {
        // 显示红色
        ui->LED->setStyleSheet("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));border-radius:12px;");
    }
}

//发送信息按钮槽函数
void serialPort::on_pushButton_send_clicked()
{

}

//清空信息槽函数
void serialPort::on_pushButton_clean_clicked()
{
    ui->textEdit_input->setText("");
}



void serialPort::on_pushButton_refresh_clicked()
{
    //存储串口名
    QStringList portNameList;
    //关闭串口号
    ui->comboBox_serialNum->clear();
    //遍历寻找新串口
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts()) {
        //append队列尾添加新数据
        portNameList.append(info.portName());
    }
    //注意导入数据，单个数据使用addItem，多个使用addItems
    ui->comboBox_serialNum->addItems(portNameList);
    //当前串口号为COM1
    ui->comboBox_serialNum->setCurrentIndex(1);
    //设置串口号
    serial->setPortName(ui->comboBox_serialNum->currentText());
}

