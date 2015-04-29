#ifndef _character_H
#define _character_H
#include <string>
#include <iostream>
#include <QString>
#include "excHierarchy.h"

using std::cout;using std::endl;using std::string;


/*-----------------SMARTCHARACTER--------------*/

class character;

class smartCharacter {
private:
    character* ptr;
public:
    smartCharacter(character* p=0);	//agisce da convertitore implicito
    smartCharacter(const smartCharacter&);
    ~smartCharacter();
    operator bool();
    smartCharacter& operator=(const smartCharacter&);
    character& operator* () const;
    character* operator-> () const;
    QString* setter(QString*,const short&);
};


/*-----------------CHARACTER--------------*/

class character {
    friend QString* smartCharacter::setter(QString *, const short &);
private:
    string name;
    static short maxfactor;
    short HP;//health points
    short DP;//damage points
    short LV;//level
    //stats
    short strength;//id=0
    short constitution;//id=1
    //metodi di utilità
    void setLV(const short&);
    void setDP();
protected:
    bool isAlive() const;
    virtual void chooseStat(const short&,const short&);
    character(string,short,short,short);//name,LV,strength,constitution
public:
    //setHP dipende da setLV. DP influenza attack().
    void setName(const string&);
    virtual void setStat(short&,const short&);
    virtual void setHP(const short&);
    string getName() const;
    short getMaxfactor() const;
    short getHP() const;//current HP
    short getDP() const;
    short getLV() const;
    short getStrength() const;
    short getConstitution() const;
    virtual character* attack(character*,const short&) throw(Error) =0;//non usa MP,attaccante come oggetto di invocazione,attaccato come parametro.ritorna l'attaccato con valori aggiornati.
    //NB:il metodo NON è const perchè esistono dei casi in cui l'attaccante può attaccare se stesso(ad esempio con magie curative)
    virtual character* clone() const =0;//costruzione di copia in una base polimorfa astratta
    virtual ~character() {}
};
#endif
/*La classe Character rappresenta un personaggio generico.Character è una classe astratta in quanto contiene almeno
un metodo virtuale puro che sarà definito nelle classi derivate.Non è possibile dichiarare oggetti della classe Character*/
