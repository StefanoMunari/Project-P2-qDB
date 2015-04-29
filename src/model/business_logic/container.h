#ifndef _Container_H
#define _Container_H
#include <iostream>
#include "functor.h"
#include "excContainer.h"
#include <QList>

using std::cout;using std::endl;

template <class K> class Container;

template <class K> class Container{
private:			//private perchè sono classi di utilità,trasparenti all'utente
    class nodo;			//dichiarazione incompleta,serve a smartp
    class smartp{
    public:
        nodo* punt;
        smartp(nodo* p=0);	//agisce da convertitore implicito nodo* -> smartp,funziona anche da costruttore senza argomenti
        smartp(const smartp& s);
        ~smartp();
        operator bool();
        smartp& operator=(const smartp&);
        nodo& operator* () const;
        nodo* operator-> () const;
        bool operator ==(const smartp&) const;
        bool operator !=(const smartp&) const;
    };
    class nodo{ 	 //template di classe implicito annidato associato
    public:
        K info;
        smartp next;
        int riferimenti;
        nodo();
        nodo(const K&,const smartp&);
    };
    smartp first;//puntatore al primo nodo della lista
    smartp last;//puntatore all'ultimo nodo della lista
    smartp& copy(const smartp&);//metodo di utilità
public:
    class iterator{
        friend class Container <K>;//usata nei metodi begin() ed end()
    private:
        Container<K>::smartp punt;
    public:
        iterator& operator ++();
        iterator operator ++(int);
        iterator& operator +(const int&);
        bool operator ==(const iterator&) const;
        bool operator !=(const iterator&) const;
        operator bool();
    };
    Container(): first(0), last(0) {}
    //metodi per la gestione di iterator
    K& operator [](iterator&) const throw(InvalidOperation);//NB:non utilizzo iterator negli scorrimenti interni alle definizioni dei templates perchè non è più efficente di smartp
    iterator begin() const;
    iterator end() const;
    //metodi per la gestione di Container
    bool empty() const;
    void clear();
    void push_front(const K&);
    void pop_front() throw(ErrorEmpty);
    void push_back(const K&);
    void pop_back() throw(ErrorEmpty);
    void insert_after(iterator&,const K&) throw(InvalidOperation);//nei seguenti metodi il parametro iterator è passato per riferimento NON COSTANTE
    void erase_after(iterator&) throw(InvalidOperation);//perchè esiste il caso in cui l'iteratore venga spostato nella lista "giusta" nel caso di copia profonda
    void replace(iterator&,const K&) throw(InvalidOperation);
    int index_size() const;
    //funzione di ricerca
    template<class T>
    QList<int>* find(const functor<T> &func) const
    {
        QList<int>* result=new QList<int>();
        int size=index_size();
        int i=0;
        for(typename Container<K>::smartp it = first; it != last->next; it=it->next)
        {
            if(func(*(it->info)))
                result->push_front(size-i);//size-i identifica l'indice di table a cui corrisponde l'elemento confrontato
            ++i;
        }
        return result;
    }//ritorna una QList<int> che contiene gli indici dei risultati trovati(inverititi rispetto a quelli di container per comodità di lettura secondo l'ordine in cui sono visualizzati in table)
};

/******************DEFINIZIONI TEMPLATE******************************/

/*_____________________SMARTP____________________*/


template <class K>
Container<K>::smartp::smartp(nodo* p): punt(p)
{	if(punt)
        punt->riferimenti++;
}

template <class K>
Container<K>::smartp::smartp(const smartp& s): punt(s.punt)
{ if(punt)
     punt->riferimenti++;
}

template <class K> 
Container<K>::smartp::~smartp() {
    if(punt){
        punt->riferimenti--;
        if(punt->riferimenti == 0)
            delete punt;		//delete standard di nodo richiama ricorsivamente il distruttore di smartp,perchè nodo ha campo next di tipo smartp
    }
}

template <class K> 
Container<K>::smartp::operator bool(){
    bool a= punt;
    return a;
}


template <class K> 
typename Container<K>::smartp& Container<K>::smartp::operator=(const smartp& s){
    if(this != &s){
        nodo* t= punt;// if(t) t->riferimenti++; if(punt) punt->riferimenti--;
        punt= s.punt;//copio in punt,t punta alla lista da deallocare
        if(punt)
            punt->riferimenti++;
        if(t){
            t->riferimenti--;
            if(t->riferimenti == 0)
                delete t;	//delete standard di nodo che quindi richiama ricorsivamente il distruttore di smartp
        }
    }
    return *this;
}

template <class K>
typename Container<K>::nodo& Container<K>::smartp::operator*() const{// trasforma un oggetto s di smartp in L-value di nodo puntato da s.punt
    return *punt;
}

template <class K>
typename Container<K>::nodo* Container<K>::smartp::operator->() const{// ritorna il puntatore convertito da smart a nodo*,se voglio l'oggetto devo dereferenziare ulteriormente,quindi uso -> standard per tipo nodo
    return punt;
}


//boolean

template <class K>
bool Container<K>::smartp::operator ==(const smartp& p) const {
    return (punt == p.punt);
}

template <class K>
bool Container<K>::smartp::operator !=(const smartp& p) const {
    return (punt != p.punt);
}


/*_____________________NODO____________________*/


template <class K>
Container<K>::nodo::nodo(): riferimenti(0){}	//invocazioni info() e next() implicite,per K assumo che abbia il suo costruttore definito

template <class K>
Container<K>::nodo::nodo(const K& i, const smartp& p): info(i), next(p), riferimenti(0){} //next(p) è una chiamata al costruttore di copia ridefinito di smartp,assumo che sia definito operator= e il costruttore di copia per K


/*_____________________ITERATOR____________________*/

template <class K> //PRE=(iterator != NULL)&&(0<=i<=INT_MAX)
typename Container<K>::iterator& Container<K>::iterator::operator +(const int& i){
    int j=i;
    while((j >0)&&(punt->next)){
        punt=punt->next;
        j--;
    }
    return *this;
}
/*
POST=(0<=nodiK<=INT_MAX,0<=OldposIterator<=INT_MAX,0<=NewposIterator<=INT_MAX)&&
(i<=(nodiK - OldposIterator) -> NewposIterator=(OldposIterator + i)&&(i>(nodiK - OldposIterator)-> ((OldposIterator + i)-> NewposIterator=nodiK));*/

template <class K> 
typename Container<K>::iterator& Container<K>::iterator::operator++(){
    if(punt)
        punt= punt->next;
    return *this;
}

template <class K>
typename Container<K>::iterator Container<K>::iterator::operator ++(int){
    iterator aux;
    aux.punt= punt;
    if(punt)
        punt= punt->next;
    return aux;
}

//boolean

template <class K>
bool Container<K>::iterator::operator== (const iterator& i) const{
    return (punt == i.punt);
}

template <class K>
bool Container<K>::iterator::operator!= (const iterator& i) const{
    return (punt != i.punt);
}

template <class K>
Container<K>::iterator::operator bool(){
    bool a= punt;
    return a;
}

//public:  ITERATOR

template <class K>
typename Container<K>::iterator Container<K>::begin() const{
    iterator aux;
    aux.punt = first;// per amicizia Container<K> può accedere a punt
    return aux;
}

template <class K>
typename Container<K>::iterator Container<K>::end() const{
    iterator aux;
    aux.punt = last;// per amicizia Container<K> può accedere a punt
    return aux;
}

template <class K>//PRE=non può essere invocato su un Container vuoto
K& Container<K>::operator [](Container<K>::iterator& it) const throw(InvalidOperation)
try
{
    if(it)
        return it.punt->info; //per amicizia posso accedere ai campi di iterator e quindi utilizzare la classe tramite Container<K>
    else
    {
        throw InvalidOperation();
        return last->info;
    }
}//POST=(it!=NULL -> ritorna l'info del nodo puntato)&&(it=NULL -> ritorna l'info del nodo puntato da last)
catch(InvalidOperation e)
{
cout<<"INVALID OPERATION,last one returned "<<endl;
}
/*_____________________Container____________________*/


template <class K>
bool Container<K>::empty() const{
    return first == 0;
}

template <class K> 
void Container<K>::clear(){
    first=last=0;
}

template <class K>
void Container<K>::push_front(const K& k){
    first=new nodo(k,first);
    if(!last)
        last=first;
}

template <class K>
void Container<K>::pop_front() throw(ErrorEmpty)
try
{
    if(first)
    {	if(first == last)
            clear();
        else
            first=first->next;// smartp p= first;prima di first,NON SERVE.CI PENSA L'ASSEGNAZIONE DI FIRST A ELIMINARE IL GARBAGE.
    }//perchè se la lista non è condivisa precedentemente a first-> first era l'unico puntatore a quel nodo-> l'assegnazione chiama il distruttore su quel nodo
    else//!first->la lista è vuota
        throw ErrorEmpty();
}
catch(ErrorEmpty e)
{
    cout <<"The Container is already empty!" <<endl;
}

template <class K>
void Container<K>::push_back(const K& k){
    if(last)
    {
        if(last->next)//nel caso la lista fosse condivisa->devo fare copia profonda fino a last e poi pushare.altrimenti se last è l'ultimo e non ho altri nodi condivisi dopo questo-> non fa side-effect sulle altre liste e devo solo aggiungere
            last= (*this).copy(last);//invocato sull'oggetto di invocazione di push_back
        last->next=new nodo(k,last->next);//costruttore di copia(a 3 parametri) di Nnodo mette riferimenti a 0 e Nnodo next è sempre NULL,l'assegnazione ridefinita mette riferimenti++ su Nnodo
        last=last->next;
    }
    else
    {//diventa una push_front quindi else (*this).push_front(k).Ho preferito riscrivere 2 righe di codice anzichè richiamare push_front
        first= new nodo(k,0);
        last=first;
    }
}

template <class K>
void Container<K>::pop_back() throw(ErrorEmpty)
try
{
    if(last)
    {
        if(last==first)
            clear();
        else{
            smartp x=first,y;
            while(x!=last)
            {	y=x;
                x=x->next;}
            if( !(last->next) || (last->riferimenti == 3) )//nel caso la lista non fosse condivisa e/o non avessi smartp che puntano al vecchio last(quindi rif==3:perchè ho last,next del nodo puntato da y e x)
                y->next=0;//devo eliminare il restante puntatore(della vecchia lista)all'ultimo nodo
            last=y;
        }//qui viene deallocato x e quindi distrutto il vecchio last
    }
    else
        throw ErrorEmpty();
}
catch(ErrorEmpty e)
{
    cout <<"The Container is already empty!" <<endl;
}

template <class K>
void Container<K>::insert_after(iterator& t,const K& k) throw(InvalidOperation)
try
{
    if(t)
    {
        if(t.punt==last)
            (*this).push_back(k);
        else{
            smartp l=(*this).copy(t.punt);
            l->next= new nodo(k,t.punt->next);
            t.punt=l;
        }//sposto l'iteratore sul nodo della nuova lista
    }
    else
        throw InvalidOperation();
}
catch(InvalidOperation e){
    cout<<"NULL POINTER, invalid operation!"<<endl;
}

template <class K>
void Container<K>::erase_after(iterator& t) throw(InvalidOperation)
try
{
    if((t.punt)&&(t.punt!=last))//se il puntatore non è NULL ed è diverso da last -> posso eseguire l'erase senza
    {	if(t.punt->next==last)	//interferenze con altre liste condivise,sicuramente t.punt->next esiste ed è un nodo della lista
            (*this).pop_back();
        else
        {	smartp l=(*this).copy(t.punt);
            l->next=t.punt->next->next;
            t.punt=l;//sposto l'iteratore sul nodo della nuova lista
        }//distrugge tutta la vecchia lista restante se non è condivisa
    }
    else
       throw InvalidOperation();
}
catch(InvalidOperation e){
    cout<<"invalid operation!"<<endl;
}

template <class K>
void Container<K>::replace(iterator& t,const K& k) throw(InvalidOperation)
try
{
    if(t){//se t è last o first è OK perchè ci pensa copy
        smartp r=(*this).copy(t.punt);
        r->info= k;//replace
        r->next= t.punt->next;
        if(t.punt ==last)
            last=r;//metto a posto last
        t.punt= r;//distrugge il resto della lista vecchia se non è condivisa,sposto l'iteratore sul nodo della nuova lista
    }
    else
        throw InvalidOperation();
}
catch(InvalidOperation e){
    cout<<"NULL POINTER, invalid operation!"<<endl;
}

template <class K>
int Container<K>::index_size() const{
    int i=0;
    Container<K>::smartp p=first;
    while(p != last)
    {    p= p->next;
        ++i;
    }
    return i;
}

//metodi di utilità:
//copy:COPIA PROFONDA FINO AL NODO CHE VIENE PASSATO(compreso) 
//E RITORNA IL PUNTATORE ALL'ULTIMO NUOVO NODO DELLA NUOVA LISTA
template <class K>
typename Container<K>::smartp& Container<K>::copy(const smartp& s){
    smartp old= first,q,prev;
    q=first= new nodo(old->info,0);
    while(old != s)//copio fino a s
    {
        q->next=new nodo(old->next->info,old->next->next);
        old=old->next;
        prev=q;
        q=q->next;
    }
    if(prev)
    {
        q->next=0;//ultimo della nuova lista,il campo info è quello di s ma il next è 0 perchè lo slaccio dalla vecchia lista
        return prev->next;
    }
    else
        return first;
}//first e q ora puntano alla nuova lista copiata,vengono distrutti i puntatori q,old e prev;
#endif
