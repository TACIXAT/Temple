#include "graph.h"
#include <QtOpenGL/QGLWidget>
#include <unistd.h>

/* \x41\x41\x41\x41\x41\x41\x41 */
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
    setMouseTracking(true);
    lastPos = new QPointF(-1.0,-1.0);
    offsetX = 0.0;
    offsetY = 0.0;
    totalChangeX = 0.0;
    totalChangeY = 0.0;
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
    centerX = this->geometry().bottomRight().x() / 2.0f;
	centerY = this->geometry().bottomRight().y() / 2.0f;
    glMatrixMode(GL_PROJECTION);
    /*glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//*/
}

void GLWidget::paintGL() {
	drawGraph();	
    glEnd();
}

/* UTILITY */
void GLWidget::drawGraph(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.2f, 0.2f, 1.0f);
    glRectf(-0.1f, 0.4f, 0.1f, 0.3f);
    
    glColor3f(1.0f, 0.2f, 0.2f);
    glRectf(-0.1f, 0.25f, 0.0f, 0.0f);
    
    glColor3f(1.0f, 0.2f, 0.2f);
    glRectf(-0.6f, 0.25f, -0.5f, 0.0f);
    
    glColor3f(0.2f, 1.0f, 0.2f);
    glRectf(-0.5f, 0.75f, -0.3f, 0.65f);
}

//Change zoom center to be at mouse location rather than originally drawn center
void GLWidget::zoomIn(QPointF *to){
	QPointF *origin = new QPointF(centerX, centerY);

	//printf("%f\t%f\n", to->x(), to->y());

	float dx = getDxF(to, origin, false);	//this move is from the origin to the original position
	float dy = getDyF(to, origin, false);
	
	float base = 1.0 + increment * scale;
	scale += (scale != range[1]) ? 1 : 0;
	float next = 1.0 + increment * scale;
	float zoom = next / base;
	
	dx -= totalChangeX;
	dy -= totalChangeY;
	
	//printf("%f\t%f\n\n", dx, dy);
	
	glTranslatef(dx, dy, 0);		//move back (from origin => to)
	glScalef(zoom, zoom, 0);
	glTranslatef(-dx, -dy, 0);		//negative for move to origin, this happens first
	GLWidget::drawGraph();
	glEnd();
	swapBuffers();
}

void GLWidget::zoomOut(QPointF *to){
	QPointF *origin = new QPointF(centerX, centerY);
	
	//printf("%f\t%f\n", to->x(), to->y());
	
	float dx = getDxF(to, origin, false);	//this move is from the origin to the original position
	float dy = getDyF(to, origin, false);
	
	float base = 1.0 + increment * scale;
	scale += (scale != range[0]) ? -1 : 0;
	float next = 1.0 + increment * scale;
	float zoom = next / base;
	
	dx -= totalChangeX;
	dy -= totalChangeY;
	
	//printf("%f\t%f\n\n", dx, dy);

	glTranslatef(dx, dy, 0);		//move back (from origin => to)
	glScalef(zoom, zoom, 0);
	glTranslatef(-dx, -dy, 0);		//negative for move to origin, this happens first
	GLWidget::drawGraph();
	glEnd();
	swapBuffers();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
	lastPos->setX(event->posF().x());
	lastPos->setY(event->posF().y());
}

float GLWidget::getDxF(QPointF *to, QPointF *from, bool adjusted){
	float deltaX = to->x() - from->x();
	if(adjusted)
		deltaX = deltaX / (centerX * (1.0 + increment * scale));
	else
		deltaX = deltaX / centerX;
	return deltaX;
}

float GLWidget::getDyF(QPointF *to, QPointF *from, bool adjusted){
	float deltaY = from->y() - to->y();
	if(adjusted)
		deltaY = deltaY / (centerY * (1.0 + increment * scale));
	else
		deltaY = deltaY / centerY;
	return deltaY;
}

/* EVENTS */
void GLWidget::mouseDoubleClickEvent(QMouseEvent *event) {
	Qt::MouseButtons pressed = event->buttons();
	QPointF *to = new QPointF(event->posF().x(), event->posF().y());
	if(pressed != Qt::NoButton){
		switch(pressed){
			case Qt::LeftButton:
				zoomIn(to);
				break;
			case Qt::RightButton:
				zoomOut(to);
				break;
			default:
				break;
		}
	} 
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
	Qt::MouseButtons pressed = event->buttons();
	QPointF *ePosF;
	ePosF = new QPointF(event->posF().x(), event->posF().y());
	if(pressed != Qt::NoButton){
		switch(pressed){
			case Qt::LeftButton:
				totalChangeX += getDxF(ePosF, lastPos, false);
				totalChangeY += getDyF(ePosF, lastPos, false);
				glTranslatef(getDxF(ePosF, lastPos, true), getDyF(ePosF, lastPos, true), 0);
				GLWidget::drawGraph();
				glEnd();
				swapBuffers();
				lastPos->setX(event->x());
				lastPos->setY(event->y()); 
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
