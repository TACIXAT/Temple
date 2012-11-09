#include "graph.h"
#include <QtOpenGL/QGLWidget>

/* \x41\x41\x41\x41\x41\x41\x41 */
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
    setMouseTracking(true);
    lastPos = new QPointF(-1.0,-1.0);
    scale = 0;
    increment = 0.2;
    range[0] = -4;
    range[1] = 5;
}

void GLWidget::initializeGL() {
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.5, 0.75, 1, 0);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//*/
}

void GLWidget::paintGL() {
	drawGraph();	
    glEnd();
}

void GLWidget::drawGraph(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.2f, 0.2f, 1.0f);
    glRectf(-0.1f, 0.4f, 0.1f, 0.3f);
    glColor3f(1.0f, 0.2f, 0.2f);
    glRectf(-0.1f, 0.25f, 0.1f, 0.15f);
    glColor3f(0.2f, 1.0f, 0.2f);
    glRectf(-0.5f, 0.75f, -0.3f, 0.65f);
}

//Change zoom center to be at mouse location rather than originally drawn center
void GLWidget::zoomIn(){
	float base = 1.0 + increment * scale;
	scale += (scale != range[1]) ? 1 : 0;
	float next = 1.0 + increment * scale;
	float zoom = next / base;
	//printf("zoom level %f\nscale %d\n", next, scale);
	glScalef(zoom, zoom, zoom);
	GLWidget::drawGraph();
	glEnd();
	swapBuffers();
}

void GLWidget::zoomOut(){
	float base = 1.0 + increment * scale;
	scale += (scale != range[0]) ? -1 : 0;
	float next = 1.0 + increment * scale;
	float zoom = next / base;
	//printf("zoom level %f\nscale %d\n", next, scale);
	glScalef(zoom, zoom, zoom);
	GLWidget::drawGraph();
	glEnd();
	swapBuffers();
}

/* EVENTS */
void GLWidget::mousePressEvent(QMouseEvent *event) {
	lastPos->setX(event->posF().x());
	lastPos->setY(event->posF().y());
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event) {
	Qt::MouseButtons pressed = event->buttons();
	
	if(pressed != Qt::NoButton){
		switch(pressed){
			case Qt::LeftButton:
				zoomIn();
				break;
			case Qt::RightButton:
				zoomOut();
				break;
			default:
				break;
		}
	} 
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
	int winx = this->geometry().bottomRight().x();
	int winy = this->geometry().bottomRight().y();
	float deltaX, deltaY;
	Qt::MouseButtons pressed = event->buttons();
	
	if(pressed != Qt::NoButton){
		switch(pressed){
			case Qt::LeftButton:
				deltaX = event->posF().x() - lastPos->x();
				deltaY = lastPos->y() - event->posF().y();
				lastPos->setX(event->x());
				lastPos->setY(event->y());
				glTranslatef(deltaX / (winx * 0.5 * (1.0 + increment * scale)), deltaY / (winy * 0.5 * (1.0 + increment * scale)), 0); 
				//half the window width or height because 0 is at center, scaled appropriately
				GLWidget::drawGraph();
				glEnd();
				swapBuffers();
				break;
			default:
				break;
		}
	} /*else {
		printf("no button %d %d\n", event->x(), event->y()); 	
	}//*/
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}
