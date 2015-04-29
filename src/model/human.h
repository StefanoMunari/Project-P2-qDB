#ifndef _human_H
#define _human_H
#include "character.h"

class human: public character{
    friend QString* smartCharacter::setter(QString *, const short &);
private:
    short MP;//magic points
    //stats
    short wisdom;//id=2,influenza MP
protected:
    virtual void chooseStat(const short&,const short&);
    human(string,short,short,short,short,short);
    character* spell(character*,const short&,const short&,const short& id=0) throw(Error);
public:
    virtual void setStat(short& t,const short&);
    short getMP() const;
    short getWisdom() const;
};
#endif
/*La classe Human rappresenta un personaggio umano,che rispetto a un personaggio generico implementa l'uso della magia(metodo spell()).
La classe è astratta in quanto estende Character e ne eredita i metodi virtuali puri.Non è quindi possibile dichiarare oggetti della
classe Human.*/
