#include "character.h"
#include "human.h"

using namespace std;

/*-----------------SMARTCHARACTER--------------*/

smartCharacter::smartCharacter(character* p): ptr(p) {}

smartCharacter::smartCharacter(const smartCharacter& s): ptr(s.ptr->clone()) {}

smartCharacter::~smartCharacter(){
    delete ptr;
}

smartCharacter::operator bool(){ 
    bool b= ptr; 
    return b;
}

smartCharacter& smartCharacter::operator=(const smartCharacter& c) {
    if(this != &c){
        delete ptr;//distruzione virtuale
        ptr= c.ptr->clone();
    }
    return *this;
}

character& smartCharacter::operator* () const { return *ptr;}

character* smartCharacter::operator-> () const { return ptr;}

QString* smartCharacter::setter(QString* v,const short& size){
    QString* confirmedValues=new QString[size];
    ptr->name=v[0].toStdString();
    ptr->setLV(v[1].toShort());
    ptr->setStat(ptr->strength,v[2].toShort());//setStrength
    confirmedValues[1]=QString::number(ptr->getStrength());
    ptr->setStat(ptr->constitution,v[3].toShort());//setConstitution
    confirmedValues[2]=QString::number(ptr->getConstitution());
    ptr->setHP(ptr->LV*ptr->maxfactor+ptr->LV+ptr->constitution/3);//HP:ricalcolo il valore ogni volta in base a LV,come quando costruisco l'oggetto
    confirmedValues[0]=QString::number(ptr->getHP());
    human* h=dynamic_cast<human*>(ptr);
    if(h)
    {
        h->setStat(h->MP,v[4].toShort());
        confirmedValues[3]=QString::number(h->getMP());
        h->setStat(h->wisdom,v[5].toShort());
        confirmedValues[4]=QString::number(h->getWisdom());
    }
    return confirmedValues;
}

/*-----------------CHARACTER--------------*/


short character::maxfactor=100;

character::character(string n,short lv,short s,short c): name(n){
    setLV(lv);
    setStat(strength,s);
    setStat(constitution,c);
    setHP(LV*maxfactor+LV+constitution/3);
}

void character::setLV(const short& lv){
    if(lv>0 && lv<=99)
        LV=lv;
    else{
        if(lv<1)
            LV=1;
        else
            LV=99;
    }
    setDP();
}

void character::setDP(){
    DP=LV*maxfactor+LV/7;
}

bool character::isAlive() const{
 return HP>0;
}

void character::chooseStat(const short& val,const short& id){
    if(id==0)
        setStat(strength,val);
    else//potrebbe essere constitution,devo controllare in quanto è possibile che estendendo la gerarchia si aggiungano altre statistiche.Se avessi molte statistiche converrebbe usare un costrutto di controllo diverso(switch)
        if(id==1)
            setStat(constitution,val);
}

void character::setName(const string& s){
    name=s;
}

void character::setStat(short& t,const short& value){
    if(value>=0 && value<=LV*5)//il valore massimo varia in base al LV,sarà sempre >=0 && <=495
        t=value;
    else{
        if(value<0)
            t=0;
        else
            t=LV*5;
    }
}

void character::setHP(const short& hp){//LV>0 -> il costruttore di character garantisce HP>0;HP <=0 solo in caso di attacco
    short maxHP= LV*maxfactor+LV+constitution/3<=9999 ? LV*maxfactor+LV+constitution/3 : 9999;
    if (hp>0 && hp<=maxHP)
        HP=hp;
    else
    {   if(hp<=0)//<=0
            HP=0;
        else//effetto curativo > maxHP
            HP=maxHP;
    }
}

string character::getName() const{ return name;}
short character::getMaxfactor() const{ return maxfactor;}
short character::getHP() const { return HP;}//current HP
short character::getDP() const { return DP;}
short character::getLV() const { return LV;}
short character::getStrength() const { return strength;}
short character::getConstitution() const { return constitution;}
