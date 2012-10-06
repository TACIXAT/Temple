//temple.h

/* Copyright 2012 Douglas Gastonguay-Goddard  */
/* edwardhowl [at] gmail [dot] com */
/* If you find this program useful I would love to hear about it. */

#ifndef TEMPLE_H
#define TEMPLE_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
//#include <QTextStream>
//#include <QFile>
//#include <QList>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

class TempleWin : public QMainWindow {
	Q_OBJECT
	
	public:
		TempleWin(QWidget *parent = 0);
		
	private:
    	QLabel *label;
};

class TBar : public QWidget {
	Q_OBJECT
	
	public:
		TBar(QWidget *parent);
		
	private slots:
	    void onByte();
    	void onWord();
    	void onDoub();
    	void onQuad();	
};


#endif
