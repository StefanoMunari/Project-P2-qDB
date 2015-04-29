#include "table.h"
#include <QStringList>
#include <string>
#include <QApplication>
using std::string;

Table::Table(QWidget *parent): QTableWidget(parent),size(6)
{
    setColumnCount(8);
    QStringList header;
    header<<"Name "<<"Type "<<"LV "<<"MP "<<"HP "<<"Strength "<<"Constitution "<<"Wisdom ";
    setHorizontalHeaderLabels(header);
    setRowCount(0);
}

Table::~Table()
{
    QList<TableRow*>::const_iterator end=datalist.end();
    for(QList<TableRow*>::const_iterator it=datalist.begin();it!=end;++it)
        delete *it;
}

void Table::setController(Controller* k) {
 c=k;
}

void Table::setRowValues(human* h,const QString& currentType){//essendo human una classe più estesa ripetto a demon mi basta fare il controllo sulla prima per capire se devo aggiungere dati alla tabella
    QString qs;
    short hp=c->getElement()->getHP();//uso sempre il primo elemento della lista, corrisponde all'ultimo inserito con push_front()
    short lv=c->getElement()->getLV();
    short st=c->getElement()->getStrength();
    short cst=c->getElement()->getConstitution();
    std::string s=c->getElement()->getName();
    values.resize(size);
    values[0]= QString::fromStdString(s);
    values[1]=currentType;
    qs.setNum(lv);
    values[2]= qs;
    qs.setNum(hp);
    values[3]=qs;
    qs.setNum(st);
    values[4]=qs;
    qs.setNum(cst);
    values[5]=qs;
    if(h)//se è un umano
    {
        size=8;
        values.resize(size);
        short mp=h->getMP();
        short ws=h->getWisdom();
        qs.setNum(mp);
        values[6]=qs;
        qs.setNum(ws);
        values[7]=qs;
    }
   else
        size=6;
}

void Table::InsertNewElement(const int& i)
{
    insertRow(i);
    TableRow* element=new TableRow(values,size,i,this);
    values.clear();
    datalist.push_back(element);
    setCellWidget(i,0,element->getName());
    setCellWidget(i,1,element->getType());
    setCellWidget(i,2,element->getLV());
    setCellWidget(i,3,element->getMP());
    setCellWidget(i,4,element->getHP());
    setCellWidget(i,5,element->getStrength());
    setCellWidget(i,6,element->getConstitution());
    setCellWidget(i,7,element->getWisdom());
    setCurrentCell(i,0);
}

void Table::removeFromList(const int& i){
    QList<TableRow*>::const_iterator it=datalist.begin()+i;
    delete *it;//distruggo la riga
    datalist.removeAt(i);//rimuovo l'indice
}

void Table::enableRow(){
    modifiedRow=this->currentRow();
    datalist[modifiedRow]->enableValues();
}

bool Table::confirmRow() const{
    return datalist[modifiedRow]->valuesChanged();
}

QString* Table::valChanged(QString* newValues,const short& size) const
{
    return c->modify(modifiedRow,newValues,size);//eseguo il controllo sui valori inseriti dall'utente
}

void Table::clear()
{
    QList<TableRow*>::const_iterator t=datalist.end();
    for(int i=rowCount();i>=0;i--)
            QTableWidget::removeRow(i);
    for(QList<TableRow*>::const_iterator it=datalist.begin();it!=t;++it)
            delete *it;
    datalist.clear();
}

void Table::linkRow(const int& i) const{
    emit linkRow(datalist[i]);//vedere Tab::setSearch() per il collegamento di SIGNAL
}

void Table::setXML(QXmlStreamWriter& w) const{
    int s=datalist.size();
    for(int i=0;i<s && !w.hasError();i++)
    {
        QString xname=datalist[i]->getName()->text();
        QString xtype=datalist[i]->getType()->text();
        QString xlv=datalist[i]->getLV()->text();
        QString xstrength=datalist[i]->getStrength()->text();
        QString xconstitution=datalist[i]->getConstitution()->text();
        w.writeStartElement(xtype);
        w.writeTextElement("Name",xname);
        w.writeTextElement("LV",xlv);
        w.writeTextElement("Strength",xstrength);
        w.writeTextElement("Constitution",xconstitution);
        if(xtype!="Golem")
        {
            QString xmp=datalist[i]->getMP()->text();
            QString xwisdom=datalist[i]->getWisdom()->text();
            w.writeTextElement("MP",xmp);
            w.writeTextElement("Wisdom",xwisdom);
        }
        w.writeEndElement();
    }
}
