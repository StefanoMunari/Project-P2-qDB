#include "searchtable.h"

searchTable::searchTable(QWidget *parent): QTableWidget(parent),index(0)
{
        setColumnCount(8);
        QStringList header;
        header<<"Name "<<"Type "<<"LV "<<"MP "<<"HP "<<"Strength "<<"Constitution "<<"Wisdom ";
        setHorizontalHeaderLabels(header);
        setRowCount(0);
}

searchTable::~searchTable(){//distrugge solo i puntatori,gli oggetti puntati rimangono(sono in table::datalist)
    int s=searchlist.size();
    for(int i=s-1;i>=0;--i)
        QTableWidget::removeRow(i);
    searchlist.clear();
}

void searchTable::setRow(TableRow* element){
        insertRow(index);
        searchlist.push_back(element);//elemento condiviso tra le 2 liste
        setCellWidget(index,0,new QLineEdit(element->getName()->text(),this));
        setCellWidget(index,1,new QLineEdit(element->getType()->text(),this));
        setCellWidget(index,2,new QLineEdit(element->getLV()->text(),this));
        setCellWidget(index,4,new QLineEdit(element->getHP()->text(),this));
        setCellWidget(index,5,new QLineEdit(element->getStrength()->text(),this));
        setCellWidget(index,6,new QLineEdit(element->getConstitution()->text(),this));
        setCellWidget(index,3,new QLineEdit(element->getMP()->text(),this));
        setCellWidget(index,7,new QLineEdit(element->getWisdom()->text(),this));
        for(int i=0;i<8;++i)
            cellWidget(index,i)->setEnabled(false);//gli elementi di searchtable non sono modificabili
        setCurrentCell(index,0);
        ++index;
}
