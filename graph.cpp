#include "graph.h"
#include <QtOpenGL/QGLWidget>
#include <unistd.h>

/* \x41\x41\x41\x41\x41\x41\x41 */
GLWidget::GLWidget(QWidget *parent, TempleLang *lang) : QGLWidget(parent) {
	glang = lang;

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
    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof(0, 1, 1, 0, -1.0, 1.0); // set origin to bottom left corner
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();//*/
}

void GLWidget::paintGL() {
	drawGraph();	
    glEnd();
}

/* UTILITY */
void GLWidget::drawGraph(){
	int count = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	std::list<TempleLang::Container *>::iterator i;
	//glang becomes null
	for(i=glang->ll->begin(); i != glang->ll->end(); i++){
		int typo = (*i)->getType(); 
		int size;
		switch(typo) {
			case BYTE:
				size = 1;
				break;
			case WORD:
				size = 2;
				break;
			case DOUB:
				size = 4;
				break;
			case QUAD:
				size = 8;
				break;
		}
		float hstart = 0.0 - 0.05f * size;
		float hend = 0.05f * size;
		float vstart = 0.9 - 0.2 *  count;
		float vend = 0.8 - 0.2 * count;
		glColor3f(0.2f, 0.2f*size, 0.4f);
    	glRectf(hstart, vstart, hend, vend);

    	count++;
	}
}

//Change zoom center to be at mouse location rather than originally drawn center
/*void GLWidget::zoomIn(QPointF *to){
	float modCenterX = centerX + totalChangeX * (this->geometry().bottomRight().x());
	float modCenterY = centerY + totalChangeY * (this->geometry().bottomRight().y());
	QPointF *origin = new QPointF(modCenterX, modCenterY);

	////printf("%f\t%f\n", to->x(), to->y());

	float dx = getDxF(to, origin, false);	//this move is from the origin to the original position
	float dy = getDyF(to, origin, false);
	
	float base = 1.0 + increment * scale;
	scale += (scale != range[1]) ? 1 : 0;
	float next = 1.0 + increment * scale;
	float zoom = next / base;
	
	dx = totalChangeX - dx;
	dy = totalChangeY - dy;
	
	dx *= (zoom - 1.0);
	dy *= (zoom - 1.0);
	
	totalChangeX += dx;
	totalChangeY += dy;	
	//totalChangeX -= dx * (zoom - 1.0);
	//totalChangeY -= dy * (zoom - 1.0);
	//printf("%f\t%f\n", dx, dy);
	//printf("%f\t%f\n", totalChangeX, totalChangeY);
	//printf("%f\t%f\n", to->x(), to->y());
	//printf("%f\t%f\n", modCenterX, modCenterY);
	//printf("%f\t%f\n\n", centerX, centerY);
	if(scale <= 2)
		glTranslatef(dx, dy, 0);		//move back (from origin => to)
	glScalef(zoom, zoom, 0);
	//glTranslatef(dx, dy, 0);		//negative for move to origin, this happens first
	GLWidget::drawGraph();
	glEnd();
	swapBuffers();
}//*/

//Change zoom center to be at mouse location rather than originally drawn center
void GLWidget::zoomIn(QPointF *to){
	float base = 1.0 + increment * scale;
	scale += (scale != range[1]) ? 1 : 0;
	float next = 1.0 + increment * scale;
	float zoom = next / base;
	int screenX = this->geometry().bottomRight().x();
	int screenY = this->geometry().bottomRight().y();

	//xorg is click point to screen origin and x
	float xorg = (to->x() - screenX * 0.5f) / (screenX * 0.5);
	float yorg = (to->y() - screenY * 0.5f) / (screenY * 0.5);
	//xvec is x component of vector between true origin and xorg
	//totalChangeX should be x component of vector between origin and true origin
	//printf("clk: %f\t%f\n", xorg, yorg);
	//printf("org: %f\t%f\n", totalChangeX, totalChangeY);

	float xvec = xorg - totalChangeX;
	float yvec = yorg + totalChangeY;

	//printf("cto: %f\t%f\n", xvec, yvec);
	//printf("czo: %f\t%f\n", xvec * zoom, yvec * zoom);

	xvec = xvec * zoom - xvec;
	yvec = yvec * zoom - yvec;
	//debug printing xvec, new xvec, and diff
	//printf("dif: %f\t%f\n\n", xvec, yvec);
	//totalChangeX -= xvec * (1.0 + increment * scale);
	//totalChangeY += yvec * (1.0 + increment * scale);

	glTranslatef(-xvec, yvec, 0);		
	glScalef(zoom, zoom, 0);
	//glTranslatef(totalChangeX * base,  totalChangeY * base, 0);
	GLWidget::drawGraph();
	glEnd();
	swapBuffers();
}

void GLWidget::zoomOut(QPointF *to){
	float base = 1.0 + increment * scale;
	scale += (scale != range[0]) ? -1 : 0;
	float next = 1.0 + increment * scale;
	float zoom = next / base;
	int screenX = this->geometry().bottomRight().x();
	int screenY = this->geometry().bottomRight().y();

	//xorg is click point to screen origin and x
	float xorg = (to->x() - screenX * 0.5f) / (screenX * 0.5);
	float yorg = (to->y() - screenY * 0.5f) / (screenY * 0.5);
	//xvec is x component of vector between true origin and xorg
	//totalChangeX should be x component of vector between origin and true origin
	//printf("clk: %f\t%f\n", xorg, yorg);
	//printf("org: %f\t%f\n", totalChangeX, totalChangeY);

	float xvec = xorg - totalChangeX;
	float yvec = yorg + totalChangeY;

	//printf("cto: %f\t%f\n", xvec, yvec);
	//printf("czo: %f\t%f\n", xvec * zoom, yvec * zoom);

	xvec = xvec * zoom - xvec;
	yvec = yvec * zoom - yvec;
	//debug printing xvec, new xvec, and diff
	//printf("dif: %f\t%f\n\n", xvec, yvec);

	glTranslatef(-xvec, yvec, 0);		
	glScalef(zoom, zoom, 0);
	//glTranslatef(totalChangeX * base,  totalChangeY * base, 0);
	GLWidget::drawGraph();
	glEnd();
	swapBuffers();
}

/*void GLWidget::zoomOut(QPointF *to){
	QPointF *origin = new QPointF(centerX, centerY);
	
	////printf("%f\t%f\n", to->x(), to->y());
	
	float dx = getDxF(to, origin, false);	//this move is from the origin to the original position
	float dy = getDyF(to, origin, false);
	
	float base = 1.0 + increment * scale;
	scale += (scale != range[0]) ? -1 : 0;
	float next = 1.0 + increment * scale;
	float zoom = next / base;
	
	dx = totalChangeX - dx;
	dy = totalChangeY - dy;
	
	//totalChangeX += dx * (1.0 - zoom);
	//totalChangeY += dy * (1.0 - zoom);
	
	////printf("%f\t%f\n\n", dx, dy);

	//glTranslatef(-dx, -dy, 0);		//move back (from origin => to)
	glScalef(zoom, zoom, 0);
	glTranslatef(dx, dy, 0);		//negative for move to origin, this happens first
	GLWidget::drawGraph();
	glEnd();
	swapBuffers();
}//*/

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
	//QPointF *to = new QPointF(centerX, centerY);
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
		//printf("no button %d %d\n", event->x(), event->y()); 	
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
