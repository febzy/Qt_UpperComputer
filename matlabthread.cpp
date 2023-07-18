
#include "matlabthread.h"
#include "lidarHandle.h"

matlabThread::matlabThread(QObject* parent)
    : QThread(parent)
{

}

void matlabThread::run()
{
    qDebug() << "开启线程运行";

    mwArray filename_("D:/qt/QTWorkSpace/upperComputer/0.22.txt");
    lidarHandle(2, dataZtj_, dataDensity_, filename_);

    QVector<QVector<double>> dataZtjs(13, QVector<double>(13));
    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 13; j++) {
            try {
                // 尝试从dataZtj_矩阵中获取元素
                dataZtjs[i-1][j-1] = dataZtj_.Get(2,i,j);
            } catch (...) {
                // 如果获取失败，则将对应位置设置为0
                dataZtjs[i-1][j-1] = 0.0;
            }
//            qDebug() << "i:" << i << "j:" << j << dataZtjs[i-1][j-1];
        }
    }



    QVector<QVector<double>> dataDensitys(13, QVector<double>(13));
    for (int i = 1; i <= 13; ++i) {
        for (int j = 1; j <= 13; ++j) {
            try {
                // 尝试从dataZtj_矩阵中获取元素
                dataDensitys[i-1][j-1] = dataDensity_.Get(2,i,j);
            } catch (...) {
                // 如果获取失败，则将对应位置设置为0
                dataDensitys[i-1][j-1] = 0.0;
            }
        }
    }

    qDebug() << "线程运行完毕";

    emit dataZtjReady(dataZtjs);
    emit dataDensityReady(dataDensitys);
}

