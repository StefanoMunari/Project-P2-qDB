#ifndef SEARCHTABLE_H
#define SEARCHTABLE_H
#include <QTableWidget>
#include "tablerow.h"

class searchTable : public QTableWidget
{
    Q_OBJECT
private:
    QList<TableRow*> searchlist;
    int index;
public:
    searchTable(QWidget *parent = 0);
    ~searchTable();//distrugge solo i puntatori,gli oggetti puntati rimangono perche' sono condivisi con table::datalist che si preoccupa di deallocarli
private slots:
    void setRow(TableRow*);
};

#endif // SEARCHTABLE_H
