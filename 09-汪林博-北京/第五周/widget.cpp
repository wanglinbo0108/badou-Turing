#include "widget.h"
#include "ui_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPainter>
#include <QDir>
#include <QMessageBox>
#include  <iostream>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *topLayout1 = new QHBoxLayout;
    topLayout1->addWidget(ui->pushButtonKmeans);
    topLayout1->addWidget(ui->spinBoxKmeans);
    ui->spinBoxKmeans->setValue(3);
    //        QHBoxLayout *bottomLayout = new QHBoxLayout;
    //        topLayout->addWidget(ui->pushButtonCanny);

    //        topLayout->addWidget(ui->pushButtonPerspectiveTransform);
    //        ui->widgetLeft->setGeometry(0,20,300,300);
    //        ui->widgetRight         ->setGeometry(300,20,300,300);

    //        bottomLayout->addWidget(ui->widgetLeft);
    //        bottomLayout->addWidget(ui->widgetRight);
    mainLayout->addLayout(topLayout1);
    mainLayout->addWidget(ui->kmeanswidget);

    setLayout(mainLayout);
    connect(ui->pushButtonKmeans, SIGNAL(clicked()), this, SLOT(btnKMeans()));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::InitData()
{

}
void Widget::Kmeans()
{
    int  k = 3;
    int means = ui->spinBoxKmeans->text().toInt();
    if(means >=2)k = means;
    std::string filename = "testset.txt";
    KMEANS<double> kms(k);
    kms.loadDataSet((char*)filename.c_str());
    kms.randCent();
    kms.kmeans();
    // 统计范围，输出数据//
    vecInt = kms.GetNodeIndex();
    vecData =   kms.GetData();
    //    minPt = QPointF(999999,999999);
    //    maxPt = QPointF(-999999,-999999);
}
void Widget::paintEvent(QPaintEvent *event)
{//只绘制20种颜色//
    // black,    white,    darkGray,
    //    gray,    lightGray,    red,
    //    green,    blue,    cyan,
    //    magenta,    yellow,    darkRed,
    //    darkGreen,    darkBlue,    darkCyan,
    //    darkMagenta,    darkYellow,
    QPainter painter(this);
    painter.begin(this);    QPen pen[20];
    QColor color[20] = {Qt::red,Qt::blue,Qt::yellow, Qt::green,    Qt::magenta,    Qt::darkGray,
                        Qt::gray,    Qt::lightGray,    Qt::red,
                        Qt::green,    Qt::blue,    Qt::cyan,
                        Qt::magenta,    Qt::yellow,    Qt::darkRed,
                        Qt::darkGreen,    Qt::darkBlue,    Qt::darkCyan,
                        Qt::darkMagenta,    Qt::darkYellow,};
    for(int i = 0; i < 20 ; i++)
        pen[i] = QPen(color[i],20,Qt::DashDotLine,Qt::RoundCap);
    for(int i=0;i<vecInt.size();i++)
    {
        if(vecInt.at(i)<20)
        {
            painter.setPen(pen[vecInt.at(i)]);
            double _x = vecData.at(i).at(0)*60+500;
            double _y = vecData.at(i).at(1)*60+500;
            painter.drawPoint(QPointF(_x,_y));
        }

    }
    painter.end();
}
void Widget::btnKMeans()
{
    Kmeans();
    update();
}
