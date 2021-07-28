#include "widget.h"
#include "ui_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPainter>
#include <QDir>
#include <QMessageBox>
#include  <iostream>
#include <ctime>
#include <QTime>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_rawpic = m_resultpic = NULL;
    QString file = QDir::currentPath()+"//lenna.png";
    //    m_picLenna.load(file);
    m_picLenna.load("lenna.png");

    if(!m_picLenna.isNull())m_rawpic = &m_picLenna;
    ui->setupUi(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *topLayout = new QHBoxLayout;
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    topLayout->addWidget(ui->pushButtonguass);
    topLayout->addWidget(ui->pushButtonsalt);

    ui->widgetRaw->setGeometry(0,20,300,300);
    ui->widgetOut         ->setGeometry(300,20,300,300);

    bottomLayout->addWidget(ui->widgetRaw);
    bottomLayout->addWidget(ui->widgetOut);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
    connect(ui->pushButtonguass, SIGNAL(clicked()), this, SLOT(btnGuassNoise()));
    connect(ui->pushButtonsalt, SIGNAL(clicked()), this, SLOT(btnSaltNoise()));


}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //        if(   strBtnInfo == "pca")
    //        {
    //            painter.drawText(ui->widgetLeft->geometry(),Qt::TextWordWrap, strLeftInfo);
    //        }else
    //        {
    if(NULL!= m_rawpic)
        painter.drawPixmap(ui->widgetRaw->geometry(), *m_rawpic);//绘制图片 横坐标、纵坐标、宽度、高度
    if(NULL!=m_resultpic)
        painter.drawPixmap(ui->widgetOut->geometry(), *m_resultpic);//绘制图片 横坐标、纵坐标、宽度、高度

    //        }
}
void Widget::guassNoise()
{
    int outWidth, outHeight;
      outHeight = m_picLenna.height();
      outWidth = m_picLenna.width();
      QRgb *line;
      QImage *newimage = new QImage(outWidth,outHeight,QImage::Format_ARGB32);
      QImage origin = m_picLenna.toImage();
      qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
      for(int y = 0; y < newimage->height();y++)
      {
          QRgb * line = (QRgb *)origin.scanLine(y);

          for(int x = 0; x<newimage->width(); x++){


              int r = qRed(line[x])+
                      generateGaussianNoise(2,0.8) * 32;
             int g =  qGreen(line[x])+
                     generateGaussianNoise(2,0.8) * 32;
              int b =       qBlue(line[x])+
                      generateGaussianNoise(2,0.8) * 32;
              if(r >255) r = 255;
              if(g >255)g = 255;
              if(b >255)b = 255;
              if(r <0) r = 0;
              if(g <0)g = 0;
              if(b <0)b = 0;
              newimage->setPixel(x,y, qRgb(r, g, b));

          }

      }
      m_picOut = QPixmap::fromImage(*newimage );
      m_resultpic = &m_picOut;
}

double Widget::generateGaussianNoise(double mu, double sigma)
{
    // 定义小值
    const double epsilon = std::numeric_limits<double>::min();
    static double z0, z1;
    static bool flag = false;
    flag= !flag;
    // flag为假构造高斯随机变量X
    if (!flag)
       return z1 * sigma + mu;
    double u1, u2;
    // 构造随机变量
    do
    {
       u1 = rand() * (1.0 / RAND_MAX);
       u2 = rand() * (1.0 / RAND_MAX);
    }while( u1 <= epsilon );
    // flag为真构造高斯随机变量X
    z0 = sqrt(-2.0 * log(u1)) * cos(2 * 3.14159265 * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(2 * 3.14159265 * u2);
    return z0 * sigma + mu;
}
// 图
void Widget::saltNoise()
{
    // 百分比 10%、、、、//
    int outWidth, outHeight;
      outHeight = m_picLenna.height();
      outWidth = m_picLenna.width();
      QRgb *line;
      QImage *newimage = new QImage(outWidth,outHeight,QImage::Format_ARGB32);
      QImage origin = m_picLenna.toImage();
      qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
      for(int y = 0; y < newimage->height();y++)
      {
          QRgb * line = (QRgb *)origin.scanLine(y);

          for(int x = 0; x<newimage->width(); x++){

              int nr = qrand() % 100;    //产生100以内的随机数
               int ng = qrand() % 100;
                int nb = qrand() % 100;
              int r = qRed(line[x]);
             int g =  qGreen(line[x]);
              int b =       qBlue(line[x]);
              if(nr <20) r = 255;
              if(ng <20)g = 255;
              if(nb <20)b = 255;
              int average = (int)(qRed(line[x])*0.3 + qGreen(line[x])*0.59 + qBlue(line[x])*0.11);
              if(nr < 20 && nr >10)average  = 255;
              if(nr < 10)average  = 0;
//              newimage->setPixel(x,y, qRgb(r, g, b));
                newimage->setPixel(x,y, qRgb(average,average, average));
          }

      }
      m_picOut = QPixmap::fromImage(*newimage );
      m_resultpic = &m_picOut;
}
void Widget::btnGuassNoise()
{
    guassNoise();
    update();
}
void Widget::btnSaltNoise()
{
    saltNoise();
    update();
}
