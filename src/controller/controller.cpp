#include "controller.h"
#include "functor.h"

Controller::Controller(){}
/*
disposizione degli oggetti inseriti in:
table::datalist: 0->1->2->3
lista di model:  3->2->1->0
*/
void Controller::insert(const smartCharacter* p){
    model.push_front(const_cast<smartCharacter*>(p));
}

smartCharacter& Controller::getElement() const{
    Container<smartCharacter*>::iterator it=model.begin();
    return *(model[it]);//ritorno smartCh per riferimento
}

bool Controller::remove(const int& i)
{
    int index=model.index_size()-i;
    if(!index)//se l'indice e' zero elimino il primo elemento
        model.pop_front();
    else//i>0
    {
        Container<smartCharacter*>::iterator it=model.begin();
        model.erase_after(it+(index-1));//il parametro iteratore punta all'elemento precedente rispetto a quello che andra' eliminato
    }
    return model.empty();
}

QString* Controller::modify(const int& i,QString* val,const short& s)//indice della riga modificata che identifica l'elemento da aggiornare
{
    Container<smartCharacter*>::iterator it=model.begin();
    it=it+(model.index_size()-i);
    return model[it]->setter(val,s);
}

int Controller::modelSize() const
{
    if(model.empty())
        return 0;
    else
        return model.index_size()+1;
}

void Controller::clearModel()
{
    model.clear();
}

QList<int>* Controller::search(QString txt,const int& c) const{
    QList<int>* indexlist=0;
    if( !model.empty() && !txt.isEmpty() )//se il db non è vuoto e c'è un valore su cui eseguire la ricerca
    {
        switch(c){
        case 0://Name
            indexlist=model.find(name(txt.toStdString()));//funtori
            break;
        case 1://Type
            indexlist=model.find(type(txt.toStdString()));
            break;
        case 2://HP
            indexlist=model.find(hp(txt.toShort()));
            break;
        case 3://MP
            indexlist=model.find(mp(txt.toShort()));
            break;
        case 4://LV
            indexlist=model.find(lv(txt.toShort()));
            break;
        case 5://Strength
            indexlist=model.find(strength(txt.toShort()));
            break;
        case 6://Constitution
            indexlist=model.find(constitution(txt.toShort()));
            break;
        case 7://Wisdom
            indexlist=model.find(wisdom(txt.toShort()));
            break;
        }
    }
        return indexlist;
}
