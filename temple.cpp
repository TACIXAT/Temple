//temple.cpp

/* Copyright 2012 Douglas Gastonguay-Goddard  */
/* edwardhowl [at] gmail [dot] com */
/* If you find this program useful I would love to hear about it. */

#include "temple.h"
#include "graph.h"
#include "lang.h"
#define DEBUG 1

/* \x41\x41\x41\x41\x41\x41\x41 */
TempleWin::TempleWin(QWidget *parent)
	: QMainWindow(parent) {

	lang = new TempleLang();

	//menu
	QAction *quit = new QAction("&Quit", this);
	
	QMenu *file;	
	file = menuBar()->addMenu("&File");
	file->addAction(quit);
	
	connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
	
	//toolbar
	QToolBar *tb = new QToolBar("TOOLBAR");
	
	TBar *tbw = new TBar(this, lang);
	tb->addWidget(tbw);
	tb->setMovable(false);
	addToolBar(Qt::RightToolBarArea, tb);
	
	GLWidget *widGl = new GLWidget(this, lang);
	widGl->show();
	widGl->resize(200,200);
	setCentralWidget(widGl);
}

/*void TempleWin::zoomIn() {
	w->zoomIn();
}

void TempleWin::zoomOut() {
	w->zoomOut(0.0f, 0.0f);
}//*/

/* \x41\x41\x41\x41\x41\x41\x41 */
TBar::TBar(TempleWin *parent, TempleLang *lang)
	: QWidget(parent) {
	
	blang = lang;
	TBar::file = new QFile("/tmp/storage.txt");

   	if(TBar::file->open(QFile::WriteOnly)) {
		TBar::out = new QTextStream(file);
		*TBar::out << "File opened" << endl;
   	}
	//file("/tmp/testy.txt");
	//file.open(QFile::WriteOnly);
	//add QFile and QTextStream to TBar
	//Initialize here
	//on*() will access those
	
	//types
	QPushButton *byte = new QPushButton("B");
	byte->setFixedSize(35,35);
	byte->setToolTip("Byte");
	connect(byte, SIGNAL(clicked()), this, SLOT(onByte()));
	//connect(byte, SIGNAL(clicked()), parentWidget(), SLOT(zoomIn()));
	
	
	QPushButton *word = new QPushButton("W");
	word->setFixedSize(35,35);
	word->setToolTip("Word");
	connect(word, SIGNAL(clicked()), this, SLOT(onWord()));
	//connect(word, SIGNAL(clicked()), parentWidget(), SLOT(zoomOut()));
	
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
	
	//horizontal rule
	QFrame *frame = new QFrame();
	frame->setFrameShape(QFrame::HLine);
	frame->setFrameShadow(QFrame::Sunken);
	frame->setLineWidth(1);
	frame->setMidLineWidth(0);
	
	//meta types
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
	
	//layout
	QGridLayout *grid = new QGridLayout(this);
	
	//add type buttons
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

//currently useless
void TBar::onByte(){
	//QTextStream out(&file);
	TDialog *die = new TDialog(this, 0, blang, BYTE);
	if(die->exec() == QDialog::Accepted){ 
		*TBar::out << "B:";
		TBar::out->flush();
	}
}

void TBar::onWord(){
	TDialog *die = new TDialog(this, 0, blang, WORD);
	if(die->exec() == QDialog::Accepted){
		*TBar::out << "W:";
		TBar::out->flush();
	}
}

void TBar::onDoub(){
	TDialog *die = new TDialog(this, 0, blang, DOUB);
	if(die->exec() == QDialog::Accepted){ 
		*TBar::out << "D:";
		TBar::out->flush();
	}
}

void TBar::onQuad(){
	TDialog *die = new TDialog(this, 0, blang, QUAD);
	if(die->exec() == QDialog::Accepted){ 
		*TBar::out << "Q:";
		TBar::out->flush();
	}
}

/* \x41\x41\x41\x41\x41\x41\x41 */
TDialog::TDialog(QWidget *parent, Qt::WindowFlags flags, TempleLang *lang, int ctype)
	: QDialog(parent, flags) {
	setModal(true);

	dlang = lang;
	type = ctype;

	QGridLayout *grid = new QGridLayout(this);

	QLabel *nameLabel = new QLabel("Name:");
	nameIn = new QLineEdit();
	grid->addWidget(nameLabel, 0, 0);
	grid->addWidget(nameIn, 0, 1, 1, 2);

	QPushButton *ok = new QPushButton("Ok");
	ok->setDefault(true);
	connect(ok, SIGNAL(clicked()), this, SLOT(onOk()));

	QPushButton *cancel = new QPushButton("Cancel");
	connect(cancel, SIGNAL(clicked()), this, SLOT(onCancel()));

	grid->addWidget(ok, 1, 1);
	grid->addWidget(cancel, 1, 2);

}

void TDialog::onOk(){
	std::string nombre = nameIn->text().toStdString();
	bool sign = false;

	switch(type) {
		case BYTE:
			dlang->addByte(nombre, sign);
			break;
		case WORD:
			dlang->addWord(nombre, sign);
			break;
		case DOUB:
			dlang->addDoub(nombre, sign);
			break;
		case QUAD:
			dlang->addQuad(nombre, sign);
			break;
	}

	std::list<TempleLang::Container *>::iterator i;
	
	for(i=dlang->ll->begin(); i != dlang->ll->end(); i++)
		std::cout << (*i)->getType() << "\t" << (*i)->getName() << std::endl;
	std::cout << std::endl;

	accept();
}

void TDialog::onCancel(){
	reject();
}

/* \x41\x41\x41\x41\x41\x41\x41 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TempleWin window;

    window.resize(750, 500);
    window.setWindowTitle("Temple");
    window.setWindowIcon(QIcon("icons/icon2.png"));
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
