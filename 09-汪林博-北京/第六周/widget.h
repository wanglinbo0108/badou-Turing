#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <string>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    std::string strBtnInfo = "hist";
    QString strLeftInfo = "";
    QString strRightInfo = "";
    QPixmap *m_rawpic,*m_resultpic;
    QPixmap m_picLenna,m_picOut;
    void guassNoise();
    void saltNoise();
    double generateGaussianNoise(double mu, double sigma);
private:
    Ui::Widget *ui;
    public
    slots:
   void btnGuassNoise();
   void btnSaltNoise();
};

#endif // WIDGET_H
