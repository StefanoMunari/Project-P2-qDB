#include "demon.h"

demon::demon(string n,short lv,short s,short c ,bool hit): character(n,lv,s,c), oneHit(hit) {}

void demon::setHP(const short& hp){
    short old=getHP();
    character::setHP(hp);
    short maxHP=(getLV()*getMaxfactor()+getLV()+getConstitution()/3<=9999? getLV()*getMaxfactor()+getLV()+getConstitution()/3: 9999);
    if(getHP()==0 && old==maxHP)
        oneHit=true;
}

void demon::reborn(){//posso usare questa mossa solamente una volta per ogni personaggio demone
    if(oneHit)      //se il demone è stato ucciso con 1 solo colpo ritorna in vita con 1/4 dei totali HP
        setHP((getLV()*getMaxfactor()+getLV()+getConstitution()/3)/4);
    oneHit=false;
}
