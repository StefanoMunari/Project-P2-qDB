#ifndef _golem_H
#define _golem_H
#include "demon.h"

class golem: public demon{
private:
    virtual character* attack(character*,const short&) throw(Error);
public:
    golem(string n="golem",short lv=1,short s=3,short c=5);
    virtual golem* clone() const;//uso covarianza sul tipo di ritorno.metodo ereditato da character->demon;
    character* attack(character*);
};

#endif
