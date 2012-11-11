#ifndef GRAPH_H
#define GRAPH_H

#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    GLWidget(QWidget *parent = NULL);
    void zoomIn(QPointF *to);
    void zoomOut(QPointF *to);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void drawGraph();
    float getDxF(QPointF *to, QPointF *from, bool adjusted);
    float getDyF(QPointF *to, QPointF *from, bool adjusted);
    QPointF *lastPos;	//track mouse position
    int scale;			//track zoom level
    int range[2];		//range of zoom level (cannot scale to zero, bounded above at 2x)
    float increment;	//the delta scale, usually 0.2 (zoom levels would be 1.2, 1.4, 1.6, etc. from the **original** scale)
	float centerX, centerY, offsetX, offsetY, totalChangeX, totalChangeY;
};

#endif
