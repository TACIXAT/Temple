//temple.h

/* Copyright 2012 Douglas Gastonguay-Goddard  */
/* edwardhowl [at] gmail [dot] com */
/* If you find this program useful I would love to hear about it. */

#ifndef TEMPLE_H
#define TEMPLE_H

#include "graph.h"
#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include <QTextStream>
#include <QFile>
//#include <QList>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

/* \x41\x41\x41\x41\x41\x41\x41 */
class TempleWin : public QMainWindow {
	Q_OBJECT
	
	public:
		TempleWin(QWidget *parent = 0);
		
	//public slots:
		//void zoomIn();
		//void zoomOut();
		
	private:
    	QLabel *label;
    	GLWidget *w;
};

/* \x41\x41\x41\x41\x41\x41\x41 */
class TBar : public QWidget {
	Q_OBJECT
	
	public:
		TBar(QWidget *parent);
		QFile *file;
		QTextStream *out;
		
	private slots:
	    void onByte();
    	void onWord();
    	void onDoub();
    	void onQuad();	
};

#endif
