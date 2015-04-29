#ifndef TABLEROW_H
#define TABLEROW_H
#include <QObject>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class TableRow: public QObject
{
    Q_OBJECT
private:                //uso un array dinamico per le varie celle QLineEdit
    QLineEdit** field;//rappresentano i valori dei campi dati del personaggio
    int index;          //indice della riga nella tabella
public:
     TableRow(const QVector<QString>&,const int&,const int&,QObject* =0);
     ~TableRow();
     QLineEdit* getName() const;
     QLineEdit* getType() const;
     QLineEdit* getHP() const;
     QLineEdit* getMP() const;
     QLineEdit* getLV() const;
     QLineEdit* getStrength() const;
     QLineEdit* getConstitution() const;
     QLineEdit* getWisdom() const;
     void enableValues() const;
     bool valuesChanged() const;
signals:
     QString* val(QString*,const short&) const;
};
#endif // TABLEROW_H
