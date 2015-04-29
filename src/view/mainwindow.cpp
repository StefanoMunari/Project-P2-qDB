#include <QApplication>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QStatusBar>
#include "mainwindow.h"
#include "form.h"
#include "humanform.h"
#include "alchemist.h"
#include "berserker.h"
#include "golem.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),modified(false),modifying(false)
{
    setObjectName(QString::fromUtf8("MainWindow"));
    setWindowTitle(tr("qDB"));

    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuFile = new QMenu(menuBar);
    menuFile->setTitle("File");
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuEdit = new QMenu(menuBar);
    menuEdit->setTitle("Edit");
    menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
    setMenuBar(menuBar);

    toolBar = new QToolBar(this);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    addToolBar(Qt::TopToolBarArea, toolBar);
    toolbar1 = new QToolBar(this);
    toolbar1->setObjectName(QString::fromUtf8("toolbar1"));
    addToolBar(Qt::TopToolBarArea, toolbar1);
    toolbar2 = new QToolBar(this);
    toolbar2->setObjectName(QString::fromUtf8("toolbar2"));
    addToolBar(Qt::TopToolBarArea, toolbar2);

    actionBerserker = new QAction(this);
    actionBerserker->setObjectName(QString::fromUtf8("actionBerserker"));
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/images/berserker.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionBerserker->setIcon(icon);
    actionAlchemist = new QAction(this);
    actionAlchemist->setObjectName(QString::fromUtf8("actionAlchemist"));
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/images/alchemist.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionAlchemist->setIcon(icon1);
    actionGolem = new QAction(this);
    actionGolem->setObjectName(QString::fromUtf8("actionGolem"));
    QIcon icon2;
    icon2.addFile(QString::fromUtf8(":/images/golem.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionGolem->setIcon(icon2);
    actionOpen = new QAction(this);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    QIcon icon3;
    icon3.addFile(QString::fromUtf8(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionOpen->setIcon(icon3);
    actionSave = new QAction(this);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    QIcon icon4;
    icon4.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionSave->setIcon(icon4);
    actionSaveAs = new QAction(this);
    actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
    QIcon icon5;
    icon5.addFile(QString::fromUtf8(":/images/saveas.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionSaveAs->setIcon(icon5);
    actionClose = new QAction(this);
    actionClose->setObjectName(QString::fromUtf8("actionClose"));
    QIcon icon6;
    icon6.addFile(QString::fromUtf8(":/images/closeDb.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionClose->setIcon(icon6);
    actionRemove = new QAction(this);
    actionRemove->setObjectName(QString::fromUtf8("actionRemove"));
    QIcon icon7;
    icon7.addFile(QString::fromUtf8(":/images/removeC.png"), QSize(), QIcon::Normal, QIcon::Off);
    actionRemove->setIcon(icon7);
    actionModify = new QAction(this);
    actionModify->setObjectName(QString::fromUtf8("actionModify"));
    actionAdd = new QAction(this);
    actionAdd->setObjectName(QString::fromUtf8("actionAdd"));
    QIcon icon9;
    icon9.addFile(QString::fromUtf8(":/images/addC.png"), QSize(), QIcon::Normal, QIcon::On);
    actionAdd->setIcon(icon9);
    label_search=new QLabel(this);
    label_search->setText(QApplication::translate("MainWindow", "Search for:", 0, QApplication::UnicodeUTF8));
    combo_search=new QComboBox(this);
    combo_search->addItem("Name");
    combo_search->addItem("Type");
    combo_search->addItem("HP");
    combo_search->addItem("MP");
    combo_search->addItem("LV");
    combo_search->addItem("Strength");
    combo_search->addItem("Constitution");
    combo_search->addItem("Wisdom");
    txt_search=new QLineEdit(this);
    txt_search->setPlaceholderText("Insert a value to search for...");
    search=new QPushButton(this);
    search->setText(QApplication::translate("MainWindow", "Search", 0, QApplication::UnicodeUTF8));
    closeSearch= new QPushButton(this);
    closeSearch->setText(QApplication::translate("MainWindow", "closeSearch", 0, QApplication::UnicodeUTF8));

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuEdit->menuAction());
    actionOpen->setText("Open");
    actionSave->setText("Save");
    actionSaveAs->setText("SaveAs");
    actionAdd->setText("Add");
    actionClose->setText("Close");
    actionRemove->setText("Remove");
    actionModify->setText("Modify");
    actionGolem->setText("Golem");
    actionAlchemist->setText("Alchemist");
    actionBerserker->setText("Berserker");
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSaveAs);
    menuFile->addAction(actionClose);
    menuEdit->addAction(actionAdd);
    menuEdit->addAction(actionRemove);
    menuEdit->addAction(actionModify);
    toolBar->addAction(actionOpen);
    toolBar->addAction(actionSave);
    toolbar1->addAction(actionAlchemist);
    toolbar1->addAction(actionBerserker);
    toolbar1->addAction(actionGolem);
    toolbar2->addSeparator();
    toolbar2->addAction(actionRemove);
    toolbar2->addSeparator();
    toolbar2->addAction(actionModify);
    toolbar2->addSeparator();
    toolbar2->addWidget(label_search);
    toolbar2->addWidget(combo_search);
    toolbar2->addWidget(txt_search);
    toolbar2->addWidget(search);
    toolbar2->addWidget(closeSearch);
//azioni disabilitate in mancanza di elementi nel DB
    actionRemove->setEnabled(false);
    actionModify->setEnabled(false);
//alloco una nuova tab
    tab=new Tab(this);
    setCentralWidget(tab);
    QWidget::showMaximized();
    tab->getTable()->setController(&controller);//setto un puntatore a controller senza passare per tab

//menu
    //File
    connect(actionClose,SIGNAL(triggered()),this,SLOT(close()));
    connect(actionSave,SIGNAL(triggered()),this,SLOT(Save()));
    connect(actionSaveAs,SIGNAL(triggered()),this,SLOT(SaveAs()));
    connect(actionOpen,SIGNAL(triggered()),this,SLOT(Open()));
    //Edit
    connect(actionAdd,SIGNAL(triggered()),this,SLOT(addCharacter()));
    connect(actionRemove,SIGNAL(triggered()),this,SLOT(removeCharacter()));
    connect(actionModify,SIGNAL(triggered()),this,SLOT(modifyCharacter()));
//toolbar
    connect(actionGolem,SIGNAL(triggered()),this,SLOT(Golem()));
    connect(actionAlchemist,SIGNAL(triggered()),this,SLOT(Alchemist()));
    connect(actionBerserker,SIGNAL(triggered()),this,SLOT(Berserker()));
    connect(tab,SIGNAL(checkEnabled(bool)),this,SLOT(checkStatus(bool)));
    connect(search,SIGNAL(clicked()),this,SLOT(setSearch()));
//others
    connect(this,SIGNAL(setTableValues(human*,QString)),tab->getTable(),SLOT(setRowValues(human*,QString)));
}

void MainWindow::addCharacter() const{
    add* a=new add(const_cast<MainWindow*>(this));
    a->setModal(true);
    a->exec();
}

void MainWindow::actionForm(const QString& n,const bool& b,QWidget* a) const
{
    form* f;
    if(b)
       f=new humanform(n,a);
    else
       f=new form(n,a);
    connect(f,SIGNAL(validForm(character*,QString)),this,SLOT(insertCharacter(character*,QString)));
    f->setModal(true);
    f->exec();
}

void MainWindow::Golem() const{
    actionForm("Golem",false,const_cast<MainWindow*>(this));
}

void MainWindow::Alchemist() const{
    actionForm("Alchemist",true,const_cast<MainWindow*>(this));
}

void MainWindow::Berserker() const{
    actionForm("Berserker",true,const_cast<MainWindow*>(this));
}

void MainWindow::checkStatus(bool b) const{
    if(controller.modelSize() >0 && !modifying)
        toolbarStatus(b);
    else
        if(modifying)
            actionModify->setEnabled(b);
}

void MainWindow::toolbarStatus(const bool& b) const{
        actionRemove->setEnabled(b);
        actionModify->setEnabled(b);
}

void MainWindow::insertCharacter(character* p,const QString& s)
{
    controller.insert(new smartCharacter(p));
    emit setTableValues(dynamic_cast<human*>(p),s);//passo solo human perchè posso dedurre demon essendo le uniche 2 classi intermedie
    if(tab->insertNewElement() && !modifying)
    {
        toolbarStatus(true);
        modified=true;
    }
}


void MainWindow::removeCharacter(){
    if(controller.remove(tab->removeElement()))//se il contenitore e' vuoto
    {
        toolbarStatus(false);
        modified=false;
    }
    else//rimozione di un elemento con contenitore non vuoto
        modified=true;
}


void MainWindow::modifyCharacter(){
    if(actionModify->objectName()=="Confirm")//modifiche da confermare
    {
        if(tab->getTable()->confirmRow())//se confermate
        {
            actionModify->setObjectName(QString::fromUtf8("Modify"));
            actionModify->setText(QApplication::translate("MainWindow", "Modify", 0, QApplication::UnicodeUTF8));
            actionOpen->setEnabled(true);
            actionRemove->setEnabled(true);
            actionSave->setEnabled(true);
            actionSaveAs->setEnabled(true);
            modifying=false;
            modified=true;
         }
    }
    else//abilito le modifiche
    {
        modifying=true;
        actionModify->setObjectName(QString::fromUtf8("Confirm"));
        actionModify->setText(QApplication::translate("MainWindow", "Confirm", 0, QApplication::UnicodeUTF8));
        tab->getTable()->enableRow();//abilita la modifica per un elemento selezionato
        actionOpen->setEnabled(false);
        actionRemove->setEnabled(false);
        actionSave->setEnabled(false);
        actionSaveAs->setEnabled(false);
    }
}

void MainWindow::setSearch() const throw(ErrorSearch)
try
{
    QList<int>* indexlist=controller.search(txt_search->text(), comboConversion(combo_search->currentText()));
    if( indexlist && indexlist->size() >0 )//se ho trovato dei risultati
    {
        tab->setSearch(indexlist);
        connect(closeSearch,SIGNAL(clicked()),tab->getSearchTable(),SLOT(close()));
        connect(closeSearch,SIGNAL(clicked()),tab,SLOT(delSearch()));
        indexlist->clear();
    }
    else
        throw ErrorSearch();
}
catch(ErrorSearch e){
    QMessageBox::warning(0,"Warning!","Zero elements found!");
}

int MainWindow::comboConversion(const QString& s) const{
    if(s=="Name")
        return 0;
    else
    {
        if(s=="Type")
            return 1;
        else
        {
            if(s=="HP")
                return 2;
            else
            {
                if(s=="MP")
                    return 3;
                else
                {
                    if(s=="LV")
                        return 4;
                    else
                    {
                        if(s=="Strength")
                            return 5;
                        else
                        {
                            if(s=="Constitution")
                                return 6;
                            else
                            {
                                if(s=="Wisdom")
                                    return 7;
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::Save() throw(EmptyData,OnlyRead)
try
{
    if(controller.modelSize()) //se c'è un elemento
    {
        if(!fileopen.isEmpty())//se stavo usando un file aperto in precedenza
        {
            QFile file(fileopen);
            if (file.open(QIODevice::WriteOnly))
                SaveXml(file);
            else
                throw OnlyRead();
            file.close();
        }
        else//altrimenti è un file nuovo non ancora salvato
        {
            tab->setCurrentIndex(0);
            QString filename = QFileDialog::getSaveFileName(this,tr("Salva come"),QDir::currentPath(),"*.xml");
            if(!filename.isEmpty())//controllo che sia stato digitato un nome per il file
            {
                QFile file(filename);
                if (file.open(QIODevice::WriteOnly))
                {
                    SaveXml(file);
                    fileopen=filename;
                    file.close();
                }
                else
                {
                    file.close();
                    throw OnlyRead();
                }
            }
        }
    }
    else
        throw EmptyData();
}
catch(OnlyRead o)
{
    QMessageBox::warning(0,"Warning!", "File opened in only-read mode!");

}
catch(EmptyData d)
{
        QMessageBox::warning(0,"Warning!","There aren't data to save!");
}

void MainWindow::SaveXml(QFile& file) throw(ErrorSave)
try
{
    QXmlStreamWriter xmlWriter;
    xmlWriter.setDevice(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("qDB");
    tab->getTable()->setXML(xmlWriter);//salvo i dati registrati in tabella
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    if(xmlWriter.hasError())
    {
        file.close();
        throw ErrorSave();
    }
    else
    {
        statusBar()->showMessage("Saving data...",300);
        file.close();
        modified=false;//modified e' true sse le modifiche fatte al file non sono state ancora salvate
     }
}
catch(ErrorSave es)
{
    QMessageBox::warning(0,"Warning!", "Error during the data saving process!");
}

void MainWindow::SaveAs() throw(EmptyData,OnlyRead)
try
{
    if(controller.modelSize()) //se c'è almeno un elemento
    {
        tab->setCurrentIndex(0);
        QString filename = QFileDialog::getSaveFileName(this,tr("Save as"),QDir::currentPath(),"*.xml");
        if(!filename.isEmpty())//controllo che sia stato digitato un nome per il file
        {
            QFile file(filename);
            if (file.open(QIODevice::WriteOnly))
            {
                SaveXml(file);
                fileopen=filename;
                file.close();
            }
            else//il file e' in modalita' di sola lettura
            {
                file.close();
                throw OnlyRead();
            }
        }
    }
else
    throw EmptyData();
}
catch(OnlyRead o)
{
    QMessageBox::warning(0,"Warning!", "File opened in only-read mode!");

}
catch(EmptyData d)
{
        QMessageBox::warning(0,"Warning!","There aren't data to save!");
}

void MainWindow::Open()
{
    QString filename;
    filename = QFileDialog::getOpenFileName(this,tr("Choose a file"),QDir::currentPath(),"*.xml");
    if(!filename.isNull() && controller.modelSize())//se e' stato scelto un file e ci sono degli elementi nel vecchio DB
    {
        controller.clearModel();//cancello gli elementi presenti nel model
        tab->closeChildren();//cancello gli elementi dalla GUI
    }
    OpenXml(filename);
}

void MainWindow::OpenXml(QString& filename) throw(ErrorOpen)
try
{
    if(!filename.isEmpty())
    {
        QFile file(filename);
        QXmlStreamReader xmlreader(&file);
        if(file.open(QFile::ReadOnly)|| QFile::Text)
        {
            while(!xmlreader.atEnd() && !xmlreader.hasError())//parsing del file .xml aperto per recuperare i dati da caricare nel DB
            {
                QXmlStreamReader::TokenType token = xmlreader.readNext();
                if(token==QXmlStreamReader::StartDocument)
                    continue;
                else
                {
                    if(xmlreader.name()=="qDB")
                        xmlreader.readNext();
                }
                if(xmlreader.isStartElement())
                {
                    QString* xvalues;//uso un array dinamico per conservare i valori che leggero' dal file
                    QString xtype=xmlreader.name().toString();//so con certezza che il valore successivo a qDB indica il tipo dell'oggetto, per il modo in cui il file e' stato costruito durante il salvataggio
                    if(xtype!="Golem")
                        xvalues=new QString[6];
                    else//sottoclasse di demon
                        xvalues=new QString[4];
                    xmlreader.readNext();
                    short i=0;
                    while(!(xmlreader.tokenType()==xmlreader.EndElement))
                    {
                        if(xmlreader.name()=="Name" || xmlreader.name()=="LV" || xmlreader.name()=="Strength" || xmlreader.name()=="Constitution")
                        {
                            xvalues[i]=xmlreader.readElementText();
                            ++i;
                        }
                        if(xtype!="Golem")
                        {
                            if(xmlreader.name()=="MP" || xmlreader.name()=="Wisdom")
                            {
                                xvalues[i]=xmlreader.readElementText();
                                ++i;
                            }
                        }
                        xmlreader.readNext();
                    }//inserisco nel database
                    if(xtype=="Alchemist")
                        this->insertCharacter(new alchemist(xvalues[0].toStdString(),xvalues[1].toShort(),xvalues[2].toShort(),xvalues[3].toShort(),xvalues[4].toShort(),xvalues[5].toShort()),xtype);
                    else
                    {
                        if(xtype=="Berserker")
                            this->insertCharacter(new berserker(xvalues[0].toStdString(),xvalues[1].toShort(),xvalues[2].toShort(),xvalues[3].toShort(),xvalues[4].toShort(),xvalues[5].toShort()),xtype);
                        else
                        {
                            if(xtype=="Golem")
                                this->insertCharacter(new golem(xvalues[0].toStdString(),xvalues[1].toShort(),xvalues[2].toShort(),xvalues[3].toShort()),xtype);
                        }
                    }
                    delete[] xvalues;//dealloco l'array dinamico
                }
            }
            if(xmlreader.hasError() || controller.modelSize()==0)//errore in lettura oppure non è stato inserito nulla nel db(possibile caso di apertura di un file vuoto)
            {
                QString error="";
                if(controller.modelSize())
                {
                    error=xmlreader.errorString();
                    throw ErrorOpen(error);
                }
                else
                {
                    error="The data are incorrect!";
                    throw ErrorOpen(error);
                }
                file.close();
                fileopen="";
            }
            else//non ci sono errori in fase di apertura
            {
                fileopen=filename;
                file.close();
                statusBar()->showMessage("Opening the file...",300);
                modified=false;//non sono state apportate modifiche al file appena aperto
            }
        }
    }
}
catch(ErrorOpen e)
{
    QMessageBox::critical(0,"Errore!",e.Error());
}

void MainWindow::closeEvent(QCloseEvent* event) throw(Mod)
try
{
    if(modified && !modifying)
    {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified");
        msgBox.setInformativeText("Do you want to save the changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int selected = msgBox.exec();
        if(fileopen.isEmpty())//se e' un file creato durante questa sessione
            switch(selected){
            case QMessageBox::Save: SaveOnClose(event); break;
            case QMessageBox::Discard: event->accept(); break;
            case QMessageBox::Cancel: event->ignore(); break;
            default: break;
            }
        else//file che non e' stato creato durante la sessione
            switch(selected){
            case QMessageBox::Save: Save(); event->accept(); break;
            case QMessageBox::Discard: event->accept(); break;
            case QMessageBox::Cancel: event->ignore(); break;
            }

    }
    if(modifying){//file in fase di modifica
        event->ignore();
        throw Mod();
    }
    else//file non modificato
        event->accept();
}
catch(Mod e)
{
    QMessageBox::warning(0,"Warning!", "Please, finish the file editing");
}

void MainWindow::SaveOnClose(QCloseEvent * event) throw(OnlyRead)//salvataggio durante la fase di chiusura del programma
try
{
    tab->setCurrentIndex(0);
    QString filename = QFileDialog::getSaveFileName(this,tr("Salva come"),QDir::currentPath(),"*.xml");
    if(!filename.isEmpty())
    {
        QFile file(filename);
        if(file.open(QIODevice::WriteOnly))
        {
            SaveXml(file);
            file.close();
            event->accept();
        }
        else
        {
            file.close();
            event->ignore();
            throw OnlyRead();
        }
    }
    else
        event->ignore();
}
catch(OnlyRead)
{
    QMessageBox::warning(0,"Warning!", "File opened in only-read mode!");
}
