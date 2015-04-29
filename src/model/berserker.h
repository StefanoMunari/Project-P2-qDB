#ifndef _berserker_H
#define _berserker_H
#include "human.h"

class berserker:public human {
public:
    berserker(string="berserker",short lv=1,short s=5,short c=4,short mp=10,short w=2);
    virtual berserker* clone() const;
    virtual character* attack(character*,const short& Mdp=0) throw(Error);
    //magie
    bool trance();//ritorna true se va a buon fine,false altrimenti.Magia di tipo Modifica-Stat
    character* iperfury(character*);//Magia di tipo offensivo
};

#endif
