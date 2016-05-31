/******************************************************************************
* The MIT License (MIT)                                                       *
*                                                                             *
* Copyright (c) 2016 Evgeniy Alekseev                                         *
*******************************************************************************/

#ifndef ELLIPSEEMULATOR_H
#define ELLIPSEEMULATOR_H

#include <QMainWindow>


class QGraphicsEllipseItem;
class QGraphicsScene;

namespace Ui {
    class EllipseEmulator;
}
class EllipseEmulator : public QMainWindow
{
    Q_OBJECT

public:
    EllipseEmulator();
    virtual ~EllipseEmulator();
    void init(const int width, const int height, const int grid);

private slots:
    void doImage();
    void save();

private:
    void doCell();
    bool hasEllipse(const int x1, const int y1, const int x2, const int y2) const;
    bool intersectionX(const double k, const double x1, const double x2) const;
    bool intersectionY(const double k, const double y1, const double y2) const;
    void initScene();
    void paintDot(const int x1, const int y1, const int x2, const int y2);
    Ui::EllipseEmulator *ui = nullptr;
    QGraphicsEllipseItem *m_ellipse = nullptr;
    QGraphicsScene *m_scene = nullptr;
    QSize m_sizes;
    int m_grid;
    double m_ellipseA;
    double m_ellipseB;
};


#endif /* ELLIPSEEMULATOR_H */
