#include "golem.h"

golem::golem(string n,short lv,short s,short c): demon(n,lv,s,c) {}

golem* golem::clone() const{
    return new golem(*this);
}


character* golem::attack(character* enemy,const short& plusDP) throw(Error)
try
{//metodo ereditato
    short hp;
    if(enemy->getHP() && isAlive())
    {
        if(enemy!=this)//se è un attacco offensivo non è possibile autoinfliggerselo
            hp=enemy->getHP()-(getDP()+plusDP+getStrength());
        else//enemy==this;non esistono attacchi curativi per i tipi demon
        {	
            throw Error();
            return NULL;
        }
        enemy->setHP(hp);
    }
    return enemy;
}
catch(Error e){
    cout<<"Invalid target "<<endl;
}

character* golem::attack(character* enemy){
	if(getHP()<=((getLV()*getMaxfactor()+getLV()+getConstitution()/3)/4))//se HP è minore di una certa soglia->l'attacco aumenta
		return attack(enemy,getConstitution());
	else
		return attack(enemy,0);
}
