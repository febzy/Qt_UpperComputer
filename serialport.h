#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QMainWindow>
#include <QSerialPort>			//访问串口的库
#include <QSerialPortInfo>		//查询串口信息的库
#include <QDebug>				//用于调试打印输出的库
#include <QTimer>				//定时器的库
#include <QTime>				//时间的库
#include <QDate>				//日期的库
#include <QMessageBox>			//一个小的弹窗库
#include <QtCharts>
// 引入串口通信的两个头文件
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
namespace Ui {
class serialPort;
}

class serialPort : public QMainWindow
{
    Q_OBJECT

public:
    explicit serialPort(QWidget *parent = nullptr);
    ~serialPort();

    //串口初始化功能
    void SerialPortInit();

    //刷新串口功能
    void RefreshSerialPort(int index);

public slots:
    //接收数据槽函数
    void DataReceived();


private slots:
    //发送数据槽函数负责数据的发送，发送数据按钮槽函数用于获取发送内容（合并到同一个函数应该也可以）
    //发送数据槽函数
    void DataSend();
    //返回按钮槽函数
    void on_pushButton_return_clicked();
    //发送按钮槽函数
    void on_pushButton_send_clicked();
    //打开串口按钮槽函数
    void on_pushButton_openSerial_clicked();
    //清空信息按钮槽函数
    void on_pushButton_clean_clicked();
    //开关显示灯
    void LED(bool changeColor);

    void on_pushButton_refresh_clicked();

private:
    Ui::serialPort *ui;
    QMainWindow *m_mainWindow;
    QSerialPort *serial;                            // 定义全局的串口对象

};

#endif // SERIALPORT_H
