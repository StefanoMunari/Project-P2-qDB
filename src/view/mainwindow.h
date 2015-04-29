#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QWidget>
#include <QComboBox>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QCloseEvent>
#include "controller.h"
#include "tab.h"
#include "add.h"
#include "excView.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
private:
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QToolBar *toolBar;
    QToolBar *toolbar1;
    QToolBar *toolbar2;
    Tab* tab;
    QAction *actionBerserker;
    QAction *actionAlchemist;
    QAction *actionGolem;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionClose;
    QAction *actionRemove;
    QAction *actionModify;
    QAction *actionAdd;
    QLabel *label_search;
    QComboBox *combo_search;
    QLineEdit *txt_search;
    QPushButton *search;
    QPushButton *closeSearch;
    Controller controller;
    bool modified;//modificato ma non ancora salvato
    bool modifying;//modifica in corso
    QString fileopen;//file aperto
    //metodi
    void SaveXml(QFile&) throw(ErrorSave);
    void OpenXml(QString&) throw(ErrorOpen);
    int comboConversion(const QString&) const;//da stringa a intero
    void SaveOnClose(QCloseEvent * event) throw(OnlyRead);
    void closeEvent(QCloseEvent* event) throw(Mod);
    void toolbarStatus(const bool&) const;
public:
    MainWindow(QWidget* parent=0);
private slots://molti slot sono collegati direttamente ai segnali emessi dai campi dati di tipo QAction
    void addCharacter() const;
    void actionForm(const QString&,const bool&,QWidget* =0) const;
    void Golem() const;
    void Alchemist() const;
    void Berserker() const;
    void checkStatus(bool) const;
    void insertCharacter(character*,const QString&);
    void removeCharacter();
    void modifyCharacter();
    void setSearch() const throw(ErrorSearch);
    void Save() throw(EmptyData,OnlyRead);
    void SaveAs() throw(EmptyData,OnlyRead);
    void Open();
signals:
    void setTableValues(human*,const QString&);//signal verso table per settare i valori dell'elemento che si vuole inserire prima che avvenga l'inserimento
};
#endif // MAINWINDOW_H
