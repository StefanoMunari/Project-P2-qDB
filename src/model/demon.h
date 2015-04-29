#ifndef _demon_H
#define _demon_H
#include "character.h"

class demon:public character {
private:
    bool oneHit;
protected:
    demon(string,short,short,short,bool hit=false);
public:
    virtual void setHP(const short&);
    void reborn();
}; 
#endif
/*La classe demon rappresenta un personaggio demone generico.demon è una classe astratta in quanto contiene almeno
un metodo virtuale puro(ereditato da character).Non è possibile dichiarare oggetti della classe demon*/
