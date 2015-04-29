#include "tab.h"
#include <QMessageBox>

Tab::Tab(QWidget *parent): QTabWidget(parent), searchResult(0)
{
    tabella=new Table(this);
    addTab(tabella,"Data");
    setCurrentWidget(tabella);
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(modifyToolbar(int)));
}

Table* Tab::getTable() const{
    return tabella;
}

searchTable* Tab::getSearchTable() const{
    return searchResult;
}

bool Tab::insertNewElement() throw(Max)
try
{
    int row=tabella->rowCount();
    if(row<=100)
    {
        tabella->InsertNewElement(row);
        return true;
    }
    throw Max();
    return false;
}
catch(Max m)
{
    QMessageBox::warning(0,"Warning!","It is not possible to insert other elements!");
}

int Tab::removeElement()
{
    int selected=tabella->currentRow();
    tabella->removeFromList(selected);
    tabella->removeRow(selected);
    return selected;
}

void Tab::modifyEnabled() const{
    tabella->enableRow();
}

void Tab::closeChildren()
{
    if(searchResult){
        searchResult->close();
        delSearch();
    }
    tabella->clear();
    setTabEnabled(1,true);
    setCurrentIndex(0);
}

void Tab::setSearch(QList<int>* indexlist) throw(ErrorSearch)
try
{
    if(!searchResult)
    {
        searchResult=new searchTable(this);
        addTab(searchResult,"Search Result");
        setCurrentWidget(searchResult);
        connect(tabella,SIGNAL(linkRow(TableRow*)),searchResult,SLOT(setRow(TableRow*)));
        for(short i=0;i<indexlist->size();++i)//table emette linkRow(tablerow*) verso searchtable
            tabella->linkRow(indexlist->at(i));//index[i]
    }
    else
        throw ErrorSearch();
    indexlist->clear();
}
catch(ErrorSearch e){
    QMessageBox::warning(0,"Warning!","Search Result already opened!\n Close the previous Search Result tab if you want to do another search.");
}

void Tab::delSearch(){
    removeTab(1);
    delete searchResult;
    searchResult=0;
}

void Tab::modifyToolbar(const int& i) const{
    if(i>0)
        emit(checkEnabled(false));
    else
        emit(checkEnabled(true));
}
