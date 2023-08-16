
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lidarHandle.h"
#include "matlabthread.h"



//创建3个进度条List，分别为右边10个和左边10个以及全部，用于后续对全部进度条赋值使用


double dataZtjs[13];
QVector<QVector<double>> dataDensitys(13, QVector<double>(9));



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("喷药系统上位机");

    //初始化,点击启动按钮就初始化
    lidarHandleInitialize();
    if (!lidarHandleInitialize()) {
        qDebug() << "add init failed.";
        return;
    }else
    {
        qDebug() << "add init success.";
    }

    //创建定时器，每隔一秒触发一次
    timer = new QTimer(this);

    setProgressBar();//调用函数，实现图表绘制

    processor = nullptr;
    //连接定时器到更新数据函数
    connect(timer,&QTimer::timeout,this,&MainWindow::processData);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}


//添加一个数据处理类，专门负责数据处理
//主要功能是调用数据处理函数，对数据进行处理并打包到数组中。
void MainWindow::processData()
{
    if (processor == nullptr) {
        processor = new matlabThread(this);
    }
    connect(processor, &matlabThread::dataZtjReady, this, &MainWindow::onDataZtjReady);
    connect(processor, &matlabThread::dataDensityReady, this, &MainWindow::onDataDensityReady);

    // 启动新线程并运行矩阵处理功能
    processor->start();
}

void MainWindow::onDataZtjReady(const QVector<QVector<double>>& dataZtjs)
{
    // 处理 dataZtjs 数据，并更新 UI 界面
    for(int i = 0;i<progressBarList_L.size();i++){
        QPalette palette;
        palette.setColor(QPalette::Base, Qt::lightGray); // 设置背景色为浅灰色

        qDebug() << "控件L：" <<progressBarList_L.size()-i;
        qDebug() << "体积：" <<dataZtjs[i][2];

        progressBarList_L.at(progressBarList_L.size()-1-i)->setValue(dataZtjs[i][2]*1000);

        progressBarList_L.at(progressBarList_L.size()-1-i)->setPalette(palette);

    }
}

void MainWindow::onDataDensityReady(const QVector<QVector<double>>& dataDensitys)
{
    // 处理 dataDensitys 数据，并更新 UI 界面
    for(int i = 0;i<progressBarList_L.size();i++){
        QPalette palette;
        palette.setColor(QPalette::Base, Qt::lightGray); // 设置背景色为浅灰色

        qDebug() << "控件L：" <<progressBarList_L.size()-i;
        qDebug() << "生物量：" <<dataDensitys[i][2];

        if(dataDensitys[i][2]<=255){
            palette.setColor(QPalette::Highlight, QColor(255-dataDensitys[i][2]*0.5, 0 , 0)); // 设置前景色
        }else if(dataDensitys[i][2]>255&&dataDensitys[i][2]<=1000){
            palette.setColor(QPalette::Highlight, QColor(0, 255-(dataDensitys[i][2]*0.125) , 0)); // 设置前景色
        }else if(dataDensitys[i][2]>1000){
            palette.setColor(QPalette::Highlight, QColor(0, 0 , 255-((dataDensitys[i][2]-1000)*0.125))); // 设置前景色
        }

        progressBarList_L.at(progressBarList_L.size()-1-i)->setPalette(palette);

    }
}


//matlab中的密度矩阵是9x13
//传送到qt中，会变成1x117的矩阵，所以将117个数据按照顺序写到一个13x9的矩阵中
//因为传送过来的数据是竖着存储的，所以是每9个数据一换行，在这边要将矩阵转换一下，从9x13变成13x9，方便后面使用




void MainWindow:: setProgressBar(){//进度条控件设置
    //向List中写入数据
    progressBarList_R << ui->progressBar_R1 << ui->progressBar_R2 << ui->progressBar_R3 << ui->progressBar_R4 << ui->progressBar_R5
                      << ui->progressBar_R6 << ui->progressBar_R7 << ui->progressBar_R8 << ui->progressBar_R9 << ui->progressBar_R10
                      << ui->progressBar_R11<< ui->progressBar_R12;
    progressBarList_L << ui->progressBar_L1 << ui->progressBar_L2 << ui->progressBar_L3 << ui->progressBar_L4 << ui->progressBar_L5
                      << ui->progressBar_L6 << ui->progressBar_L7 << ui->progressBar_L8 << ui->progressBar_L9 << ui->progressBar_L10
                      << ui->progressBar_L11<< ui->progressBar_L12;
    progressBarList << ui->progressBar_R1 << ui->progressBar_R2 << ui->progressBar_R3 << ui->progressBar_R4 << ui->progressBar_R5
                    << ui->progressBar_R6 << ui->progressBar_R7 << ui->progressBar_R8 << ui->progressBar_R9 << ui->progressBar_R10
                    << ui->progressBar_R11<< ui->progressBar_R12
                    << ui->progressBar_L1 << ui->progressBar_L2 << ui->progressBar_L3 << ui->progressBar_L4 << ui->progressBar_L5
                    << ui->progressBar_L6 << ui->progressBar_L7 << ui->progressBar_L8 << ui->progressBar_L9 << ui->progressBar_L10
                    << ui->progressBar_L11<< ui->progressBar_L12;


    //对整体控件进行设置
    for(int i = 0;i<progressBarList.size();i++){

        //取消进度条特效
        //        progressBarList.at(i)->setStyleSheet("QProgressBar::chunk { background-color: green; }");
        progressBarList.at(i)->setStyle(QStyleFactory::create("Windows"));

    }
    //对整体控件进行设置
    for(int i = 0;i<progressBarList.size();i++){
        QPalette palette;
        palette.setColor(QPalette::Base, Qt::lightGray); // 设置背景色为浅灰色

        progressBarList.at(i)->setValue(0);

        palette.setColor(QPalette::Highlight, QColor(0, 255 , 0)); // 设置前景色

        progressBarList.at(i)->setPalette(palette);


    }



}


//停止按钮，停止计时器（表现：终止ui继续刷新）
//后续添加停止后台功能（停止接收信息/停止后台功能执行）
void MainWindow::on_pushButton_stopTimer_clicked()
{
    //点击停止按钮时，终止数据处理文件
    //    testTerminate();
    //    mclTerminateApplication();
    qDebug() << "停止计时器";
    timer->stop();
    delete processor;
}

//启动按钮，启动计时器（表现：刷新ui界面）
//后续添加启动功能，对应停止
void MainWindow::on_pushButton_startTimer_clicked()
{
    qDebug() << "启动：执行一次更新函数，启动计时器";
    //并进行一次数据处理显示（是否需要）

    processData();
    //开始计时器，间隔为5s
    timer->start(10000);

}

void MainWindow::on_pushButton_serialPort_clicked()
{
    serialPort *sp = new serialPort(this);
    sp->setWindowModality(Qt::ApplicationModal);
    sp->show();
}

void MainWindow::on_pushButton_UDP_clicked()
{
    udpSocketWindow = new UdpSocket();
    udpSocketWindow->setWindowModality(Qt::ApplicationModal);
    udpSocketWindow->show();
}




void MainWindow::on_pushButton_TCP_clicked()
{
    tcpSocketWindow = new tcpSocket();
    tcpSocketWindow->setWindowModality(Qt::ApplicationModal);
    tcpSocketWindow->show();
}

