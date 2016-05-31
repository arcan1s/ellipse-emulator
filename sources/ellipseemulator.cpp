/******************************************************************************
* The MIT License (MIT)                                                       *
*                                                                             *
* Copyright (c) 2016 Evgeniy Alekseev                                         *
*******************************************************************************/

#include "ellipseemulator.h"
#include "ui_ellipseemulator.h"

#include <QDebug>
#include <QFileDialog>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QInputDialog>

#include <cmath>


EllipseEmulator::EllipseEmulator()
    : QMainWindow()
    , ui(new Ui::EllipseEmulator)
{
    ui->setupUi(this);
    ui->graphicsView->setContentsMargins(0, 0, 0, 0);
    ui->graphicsView->setFrameShape(QFrame::NoFrame);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->actionGenerate, SIGNAL(triggered(bool)), this, SLOT(doImage()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(save()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(close()));
}


EllipseEmulator::~EllipseEmulator()
{
    delete ui;
}


void EllipseEmulator::init(const int width, const int height, const int grid)
{
    qDebug() << "Init with width" << width << "height" << height << "grid" << grid;
    m_sizes = QSize(width, height);
    m_grid = grid;

    initScene();
    doCell();
    resize(m_sizes);
}


void EllipseEmulator::doImage()
{
    bool ok;
    int grid = QInputDialog::getInt(this, QString("Grid size"), QString("Grid:"), 
                                    4, 4, 1000, 4, &ok);
    if (!ok)
        return;
    int width = QInputDialog::getInt(this, QString("Image width"), QString("Width:"), 
                                     750, 4, 1000000, 1, &ok);
    if (!ok)
        return;
    int height = QInputDialog::getInt(this, QString("Image height"), QString("Height:"), 
                                      500, 4, 1000000, 1, &ok);
    if (!ok)
        return;

    if ((width <= grid) || (height <= grid)) {
        qDebug() << "Invalid params given";
        return;
    }

    return init(width, height, grid);
}


void EllipseEmulator::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, QString("Save image"),
                                                    QString("."), 
                                                    QString("Images (*.png *.jpg *bmp)"));
    if (fileName.isEmpty())
        return;

    QPixmap pixmap = ui->graphicsView->grab();
    pixmap.save(fileName);
}


void EllipseEmulator::doCell()
{
    int maxWidthCount = m_sizes.width() / m_grid;
    int maxHeightCount = m_sizes.height() / m_grid;

    int count = 1;
    while ((count <= maxWidthCount) 
           && (count <= maxHeightCount)) {
        int widthGrid = m_sizes.width() / count;
        int heightGrid = m_sizes.height() / count;
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {
                paintDot(i * widthGrid, j * heightGrid,
                         (i + 1) * widthGrid, (j + 1) * heightGrid);
            }
        }
        count *= 2;
    }
}


bool EllipseEmulator::hasEllipse(const int x1, const int y1,
                                 const int x2, const int y2) const
{
    return (
        intersectionX(y1, x1, x2)
        || intersectionX(y2, x1, x2)
        || intersectionY(x1, y1, y2)
        || intersectionY(x2, y1, y2)
    );
}


bool EllipseEmulator::intersectionX(const double k, const double x1, const double x2) const
{
    double powX1 = (x1 - m_sizes.width() * 0.5) * (x1 - m_sizes.width() * 0.5);
    double powX2 = (x2 - m_sizes.width() * 0.5) * (x2 - m_sizes.width() * 0.5);
    double coordY = k - m_sizes.height() * 0.5;
    double eq = (1.0 - (coordY * coordY) / (m_ellipseB * m_ellipseB)) * (m_ellipseA * m_ellipseA);
    return (eq > std::min(powX1, powX2) && (eq < std::max(powX1, powX2)));
}


bool EllipseEmulator::intersectionY(const double k, const double y1, const double y2) const
{
    double powY1 = (y1 - m_sizes.height() * 0.5) * (y1 - m_sizes.height() * 0.5);
    double powY2 = (y2 - m_sizes.height() * 0.5) * (y2 - m_sizes.height() * 0.5);
    double coordX = k - m_sizes.width() * 0.5;
    double eq = (1.0 - (coordX * coordX) / (m_ellipseA * m_ellipseA)) * (m_ellipseB * m_ellipseB);
    return (eq > std::min(powY1, powY2) && (eq < std::max(powY1, powY2)));
}


void EllipseEmulator::initScene()
{
    // init scene
    delete m_scene;
    m_scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(m_scene);
    // init ellipse
    m_ellipseA = m_sizes.width() * 0.35;
    m_ellipseB = m_sizes.height() * 0.35;
    m_ellipse = m_scene->addEllipse(m_sizes.width() * 0.15,
                                    m_sizes.height() * 0.15,
                                    m_ellipseA * 2.0, m_ellipseB * 2.0,
                                    QPen(QColor(255, 0, 0))
                                   );
}


void EllipseEmulator::paintDot(const int x1, const int y1,
                               const int x2, const int y2)
{
    if (!hasEllipse(x1, y1, x2, y2))
        return;

    int x = x1 + rand() % (x2 - x1);
    int y = y1 + rand() % (y2 - y1);
    qDebug() << "Paint dot in" << x1 << y1 << x2 << y2 << "; dot" << x << y;
    double rad = m_grid / 4.0;
    m_scene->addEllipse(x - rad, y - rad, rad * 2.0, rad * 2.0,
                        QPen(), QBrush(Qt::SolidPattern));
}
