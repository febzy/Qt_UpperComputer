
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>			//访问串口的库
#include <QSerialPortInfo>		//查询串口信息的库
#include <QDebug>				//用于调试打印输出的库
#include <QTimer>				//定时器的库
#include <QTime>				//时间的库
#include <QDate>				//日期的库
#include <QMessageBox>			//一个小的弹窗库
#include <QtCharts>
QT_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_END_NAMESPACE


//添加子界面头文件
#include "serialport.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_serialPort_clicked();

    //处理数据函数
    void processData();

    void onDataZtjReady(const QVector<QVector<double>>& dataZtjs);

    void onDataDensityReady(const QVector<QVector<double>>& dataDensitys);

    void on_pushButton_stopTimer_clicked();

    void on_pushButton_startTimer_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool isPageCreated = false;

    //R为右侧进度条组
    QList<QProgressBar*> progressBarList_R;
    //L为左侧进度条组
    QList<QProgressBar*> progressBarList_L;
    //无后缀为全部控件，备用
    QList<QProgressBar*> progressBarList;


private:

    void setProgressBar(); //进度条控件设置
};


#endif // MAINWINDOW_H
