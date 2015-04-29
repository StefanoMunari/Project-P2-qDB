#include "tablerow.h"
#include <QApplication>
#include <QRegExpValidator>
#include <QTableWidget>

TableRow::TableRow(const QVector<QString>& p,const int& size,const int& ind,QObject* parent): QObject(parent),index(ind)
{
    field=new QLineEdit*[8]();

    for(int j=0;j<size;++j)
    {
        field[j]=new QLineEdit();
        field[j]->setText(p[j]);
        field[j]->setStyleSheet("color: #000080");
        field[j]->setEnabled(false);//inizialmente i vari campi non sono modificabili
    }

    if(size < 8)
    {
        for(int j=6;j<8;++j)
        {
            field[j]=new QLineEdit();
            field[j]->setText("\\");
            field[j]->setStyleSheet("color: #000080");
            field[j]->setEnabled(false);//inizialmente i vari campi non sono modificabili
        }
    }

    //espressioni regolari per limitare il range di valori inseribili dall'utente
    QRegExp re("^\\S+(\\s*\\S*)*$");
    field[0]->setValidator(new QRegExpValidator(re, this));
    re.setPattern("^[1-9][0-9]?$");
    field[2]->setValidator(new QRegExpValidator(re, this));
    re.setPattern("^0?^([1-9][0-9])?^([1-3][0-9][0-9])?^(4[0-9][0-5])?$");
    field[4]->setValidator(new QRegExpValidator(re, this));
    field[5]->setValidator(new QRegExpValidator(re, this));
    field[7]->setValidator(new QRegExpValidator(re, this));
    re.setPattern("^([1-9][0-9][0-9])?^0?$");
    field[6]->setValidator(new QRegExpValidator(re, this));

    //durante modify, verrà eseguito un aggiornamento dei valori del model
    connect(this,SIGNAL(val(QString*,short)),this->parent(),SLOT(valChanged(QString*,short)));
}

TableRow::~TableRow(){
    for(short i=7;i>=0;--i){
        delete field[i];//cancello gli oggetti puntati da ogni elemento
    }
    delete[] field;//cancello l'array di puntatori
}

QLineEdit* TableRow::getName() const {return field[0];}
QLineEdit* TableRow::getType() const {return field[1];}
QLineEdit* TableRow::getLV() const {return field[2];}
QLineEdit* TableRow::getHP() const {return field[3];}
QLineEdit* TableRow::getStrength() const {return field[4];}
QLineEdit* TableRow::getConstitution() const {return field[5];}
QLineEdit* TableRow::getMP() const {return field[6];}
QLineEdit* TableRow::getWisdom() const {return field[7];}


void TableRow::enableValues() const{
    field[0]->setEnabled(true);
    field[2]->setEnabled(true);
    field[4]->setEnabled(true);
    field[5]->setEnabled(true);
    for(short i=6;i<8;++i)
        if(field[i]->text()!="\\")//non abilito la modifica per i campi vuoti
                field[i]->setEnabled(true);
}

bool TableRow::valuesChanged() const//emette il segnale che chiama le modifiche in controller tramite TABLE e ritorna un boolenao invalid t.c. !invalid indica se il valore e' valido
{
    bool invalid(false);
    short i(0);
    while(i<8)
    {
        if(field[i]->isEnabled() && field[i]->text().isEmpty())//se vuoto non e' un valore valido
        {
            invalid=true;
            field[i]->setStyleSheet("background-color: #FFFF00");
        }
        else
            field[i]->setStyleSheet("color: #000080");
        ++i;
    }
    if(!invalid)//modifiche valide
    {
        i=0;
        while(i<8)
        {
            if(field[i]->isEnabled())//disabilito ulteriori modifiche, sono valide quelle appena confermate
                field[i]->setEnabled(false);
            ++i;
        }
        QString* newValues;//conterrà i nuovi valori inseriti dall'utente
        short size;
        if(field[6]->text()=="\\")//in questo caso è un sottoclasse di demon
        {
            size=4;
            newValues= new QString[size];
        }
        else//altrimenti è sottoclasse di human
        {
            size=6;
            newValues= new QString[size];
            newValues[4]=field[6]->text();newValues[5]=field[7]->text();
        }
        newValues[0]=field[0]->text();newValues[1]=field[2]->text();newValues[2]=field[4]->text();newValues[3]=field[5]->text();
        --size;//viene usato come size di confirmedValues
        QString* confirmedValues;//conterrà i valori realmente inseriti nel model
        confirmedValues=emit val(newValues,size);
        newValues[1]=field[3]->text();//per poter eseguire comodamente i confronti nel ciclo while sostituisco il valore di lv con quello di hp
        i=0;
        while(i<size)//ciclo che setta i valori confermati
        {
            if(confirmedValues[i]!=newValues[i+1])//se il valore è stato ricalcolato allora lo inserisco al posto di quello digitato dall'utente, quest'ultimo è un valore non valido.
                field[i+3]->setText(confirmedValues[i]);
            ++i;
        }
        delete[] confirmedValues;//dealloco gli array dinamici
        delete[] newValues;
    }
    return !invalid;
}
