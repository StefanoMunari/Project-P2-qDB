#ifndef _alchemist_H
#define _alchemist_H
#include "human.h"

class alchemist: public human {
public:
    alchemist(string="alchemist",short lv=1,short s=2,short c=3,short mp=10,short w=5);
    virtual alchemist* clone() const;//uso covarianza sul tipo di ritorno.metodo ereditato da character->human;
    //attacchi fisici
    virtual character* attack(character*,const short& Mdp=0) throw(Error);//se invocato direttamente si riferisce ad un attacco fisico
    //magie
    character* sulfur(character*);
    character* cure(character*);
};
#endif
/*alchemist è una classe concreta derivata da human. alchemist implementa i metodi virtuali puri dichiarati in character(classe base astratta della gerarchia)*/
