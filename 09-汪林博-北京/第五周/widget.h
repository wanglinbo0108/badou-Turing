#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "kmeans.h"
#include <QPointF>
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
    void InitData();
    void Kmeans();
    int m_nKNum ;
    vector<int> vecInt ;
    vector< vector<double> >vecData;
    QPointF minPt,maxPt;
    Ui::Widget *ui;
    public
    slots:
    void btnKMeans();
};

#endif // WIDGET_H
