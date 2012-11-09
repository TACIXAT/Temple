#include "graph.h"
#include <QtOpenGL/QGLWidget>

/*aaaaaaaaaaa*/
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
    setMouseTracking(true);
    lastPos = new QPointF(-1.0,-1.0);
    scale = 0;
    increment = 0.1;
    float temp[20] = {
    			20.0f, 10.0f, 6.66f, 5.0f, 4.001f,
    		 	3.33f, 2.85f, 2.0f, 2.0f, 2.0f, 2.0f, 
    		 	3.0f, 4.0f, 5.0f, 6.0f, 
    		 	5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
   	for(int i=0; i<20; i++){
   		dragScale[i] = temp[i];
   	}
   	
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5f, 0.79f, 1.0f);
    glRectf(-0.2f, 0.2f, 0.2f, 0.0f);
    glColor3f(0.35f, 0.75f, 1.0f);
    glRectf(-0.2f, 0.5f, 0.2f, 0.3f);
    /*glBegin(GL_QUADS);
    glVertex2f(-0.5,-0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(-0.5,0.5);
    glVertex2f(-0.5,0.5);//*/
    glEnd();
}

void GLWidget::drawGraph(){
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.9f, 0.2f);
    glRectf(-0.2f, 0.2f, 0.2f, 0.0f);
    glColor3f(0.2f, 0.6f, 1.0f);
    glRectf(-0.2f, 0.5f, 0.2f, 0.3f);
}


void GLWidget::zoomIn(){
	float base = 1.0 + increment * scale;
	scale += (scale == 10) ? 0 : 1;
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
	scale += (scale == -9) ? 0 : -1;
	float next = 1.0 + increment * scale;
	//printf("zoom level %f\nscale %d\n", next, scale);
	float zoom = next / base;
	glScalef(zoom, zoom, zoom);
	GLWidget::drawGraph();
	glEnd();
	swapBuffers();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
	lastPos->setX(event->posF().x());
	lastPos->setY(event->posF().y());
	int winx = this->geometry().bottomRight().x();
	int winy = this->geometry().bottomRight().y();
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f((float)event->x()/winx, (float)event->y()/winy, (float)(event->y()*event->x())/(winx));
    glRectf(-0.2f, 0.2f, 0.2f, 0.0f);
    glColor3f((float)event->y()/winy, (float)(event->y()*event->x())/(winx*winy), (float)event->x()/winx);
    glRectf(-0.2f, 0.5f, 0.2f, 0.3f);
    //glScalef(1.1f, 1.1f, 1.1f);
    /*glBegin(GL_QUADS);
    glVertex2f(-0.5,-0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(-0.5,0.5);
    glVertex2f(-0.5,0.5);//*/
    glEnd();
    swapBuffers();
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
				//printf("dx:%f dy:%f\n", deltaX, deltaY);
				//printf("cx:%f cy:%f\n\n", deltaX/winx, deltaY/winy);
				//printf("winx:%d winy:%d\nex:%d ey:%d\nlx:%d ly%d\n\n", winx, winy, event->x(), event->y(), lastPos->x(), lastPos->y());
				glTranslatef(deltaX/(winx*0.5*(1.0 + 0.1*scale)), deltaY/(winy*0.5*(1.0 + 0.1*scale)), 0); 
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
    //printf("%f, %d\n", 1.0f/event->x(), event->y());
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
