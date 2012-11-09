#ifndef GRAPH_H
#define GRAPH_H

#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>

class GLWidget : public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLWidget(QWidget *parent = NULL);
    void zoomIn();
    void zoomOut();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void drawGraph();
    QPoint *lastPos;
    int scale;
    float increment;
    float dragScale[20];
};

#endif
