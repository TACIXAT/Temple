//temple.cpp

/* Copyright 2012 Douglas Gastonguay-Goddard  */
/* edwardhowl [at] gmail [dot] com */
/* If you find this program useful I would love to hear about it. */

#include "temple.h"

#define DEBUG 1

TempleWin::TempleWin(QWidget *parent)
	: QMainWindow(parent) {
	
	//menu
	QAction *quit = new QAction("&Quit", this);
	
	QMenu *file;	
	file = menuBar()->addMenu("&File");
	file->addAction(quit);
	
	connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
	
	QToolBar *tb = new QToolBar("TOOLBAR");
	TBar *tbw = new TBar(this);
	tb->addWidget(tbw);
	tb->setMovable(false);
	addToolBar(Qt::RightToolBarArea, tb);
}

TBar::TBar(QWidget *parent)
	: QWidget(parent) {
	
	QPushButton *byte = new QPushButton("B");
	byte->setFixedSize(35,35);
	byte->setToolTip("Byte");
	connect(byte, SIGNAL(clicked()), this, SLOT(onByte()));
	
	QPushButton *word = new QPushButton("W");
	word->setFixedSize(35,35);
	word->setToolTip("Word");
	connect(word, SIGNAL(clicked()), this, SLOT(onWord()));
	
	QPushButton *dword = new QPushButton("D");
	dword->setFixedSize(35,35);
	dword->setToolTip("Double Word");
	connect(dword, SIGNAL(clicked()), this, SLOT(onDoub()));
	
	QPushButton *qword = new QPushButton("Q");
	qword->setFixedSize(35,35);
	qword->setToolTip("Quad Word");
	connect(qword, SIGNAL(clicked()), this, SLOT(onQuad()));
	
	QPushButton *str = new QPushButton("S");
	str->setFixedSize(35,35);
	str->setToolTip("String");
			
	QPushButton *vlen = new QPushButton("V");
	vlen->setFixedSize(35,35);
	vlen->setToolTip("Variable Length");
	
	QPushButton *fixed = new QPushButton("F");
	fixed->setFixedSize(35,35);
	fixed->setToolTip("Fixed Value");
			
	QPushButton *unk = new QPushButton("U");
	unk->setFixedSize(35,35);
	unk->setToolTip("Unknown (Binary Blob)");
	
	QPushButton *character = new QPushButton("C");
	character->setFixedSize(35,35);
	character->setToolTip("Character");
	
	QFrame *frame = new QFrame();
	frame->setFrameShape(QFrame::HLine);
	frame->setFrameShadow(QFrame::Sunken);
	frame->setLineWidth(1);
	frame->setMidLineWidth(0);

	QPushButton *len = new QPushButton("L");
	len->setFixedSize(35,35);
	len->setToolTip("Length");
			
	QPushButton *count = new QPushButton("C");
	count->setFixedSize(35,35);
	count->setToolTip("Count");
	
	QPushButton *swcase = new QPushButton("S");
	swcase->setFixedSize(35,35);
	swcase->setToolTip("Switch");
			
	QPushButton *group = new QPushButton("G");
	group->setFixedSize(35,35);
	group->setToolTip("Group");
	
	QPushButton *sign = new QPushButton("S");
	sign->setFixedSize(35,35);
	sign->setToolTip("Signed");
	
	QPushButton *usign = new QPushButton("U");
	usign->setFixedSize(35,35);
	usign->setToolTip("Unsigned");
	
	QPushButton *terminator = new QPushButton("\\0");
	terminator->setFixedSize(35,35);
	terminator->setToolTip("Terminator");
	
	QGridLayout *grid = new QGridLayout(this);
	grid->addWidget(byte, 0, 0);
	grid->addWidget(word, 0, 1);
	grid->addWidget(dword, 1, 0);
	grid->addWidget(qword, 1, 1);
	grid->addWidget(str, 2, 0);
	grid->addWidget(vlen, 2, 1);
	grid->addWidget(fixed, 3, 0);
	grid->addWidget(unk, 3, 1);
	grid->addWidget(character, 4, 0);

	grid->addWidget(frame, 5, 0, 1, 2);

	grid->addWidget(len, 6, 0);
	grid->addWidget(count, 6, 1);
	grid->addWidget(swcase, 7, 0);
	grid->addWidget(group, 7, 1);
	grid->addWidget(sign, 8, 0);
	grid->addWidget(usign, 8, 1);
	grid->addWidget(terminator, 9, 0);
	//*/
	
	setLayout(grid);	
	//*/
}


void TBar::onByte(){
	int i = 3;
	i++;
}

void TBar::onWord(){
	int i = 3;
	i++;
}

void TBar::onDoub(){
	int i = 3;
	i++;
}

void TBar::onQuad(){
	int i = 3;
	i++;
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TempleWin window;

    window.resize(750, 500);
    window.setWindowTitle("Temple");
    window.setWindowIcon(QIcon("icon2.png"));
    window.show();

    return app.exec();
}

/*
    
    QFile data("/tmp/storage.txt");

   	if (data.open(QFile::WriteOnly)) {
		QTextStream out(&data);
		out << "0:0:3:0:1:0:0:1:";
		data.close();
   	}
   	
*/