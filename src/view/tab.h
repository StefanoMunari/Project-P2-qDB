#ifndef TAB_H
#define TAB_H
#include <QTabWidget>
#include "excView.h"
#include "table.h"
#include "searchtable.h"

class Tab : public QTabWidget
{
    Q_OBJECT
private:
    Table* tabella;
    searchTable* searchResult;
public:
    Tab(QWidget *parent = 0);
    Table* getTable() const;
    searchTable* getSearchTable() const;
    bool insertNewElement() throw(Max);
    int removeElement();
    void modifyEnabled() const;
    void closeChildren();
    void setSearch(QList<int>*) throw(ErrorSearch);
private slots:
    void delSearch();
    void modifyToolbar(const int&) const;
signals:
    void checkEnabled(bool) const;
};
#endif // TAB_H
