
#ifndef MATLABTHREAD_H
#define MATLABTHREAD_H
#include "lidarHandle.h"
#include<QThread>
#include <QMainWindow>
#include <QSerialPort>			//访问串口的库
#include <QSerialPortInfo>		//查询串口信息的库
#include <QDebug>				//用于调试打印输出的库
#include <QTimer>				//定时器的库
#include <QTime>				//时间的库
#include <QDate>				//日期的库
#include <QMessageBox>			//一个小的弹窗库
#include <QtCharts>




class matlabThread : public QThread
{
    Q_OBJECT
public:
    matlabThread(QObject* parent = nullptr);

signals:
    void dataZtjReady(const QVector<QVector<double>>& dataZtjs);
    void dataDensityReady(const QVector<QVector<double>>& dataDensitys);

protected:
    void run() override;

private:
    mwArray dataZtj_;
    mwArray dataDensity_;
    QString filename_;

};

#endif // MATLABTHREAD_H
