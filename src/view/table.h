#ifndef TABLE_H
#define TABLE_H
#include <QTableWidget>
#include <QXmlStreamWriter>
#include "tablerow.h"
#include "controller.h"
#include "human.h"

class Table : public QTableWidget
{
    Q_OBJECT
private:
    Controller* c;
    int size;
    QVector<QString> values;//contiene i valori dell'ultimo personaggio inserito
    QList<TableRow*> datalist;
    int modifiedRow;
public:
    Table(QWidget *parent = 0);
    ~Table();
    void setController(Controller*);
    void InsertNewElement(const int&);
    void removeFromList(const int&);
    void enableRow();
    bool confirmRow() const;
    void clear();
    void linkRow(const int&) const;
    void setXML(QXmlStreamWriter&) const;
private slots:
    void setRowValues(human*,const QString&);
    QString* valChanged(QString*,const short&) const;
signals:
    void linkRow(TableRow*) const;
};


#endif // TABLE_H
