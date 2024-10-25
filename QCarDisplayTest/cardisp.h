#ifndef CARDISP_H
#define CARDISP_H

#include <QMainWindow>
#include <QPainter>
#include <QtMath>

class CarDisp : public QMainWindow
{
    Q_OBJECT

public:
    CarDisp(QWidget *parent = 0);
    ~CarDisp();

public:
    void setvalues(qreal iValues);
    void paintEvent(QPaintEvent *event) override;

private:
    qreal Values;
    const static int radius;
    const static int maxv;
    const static int minv;
};

#endif // CARDISP_H
