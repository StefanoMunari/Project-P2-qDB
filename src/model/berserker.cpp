#include "berserker.h"

berserker::berserker(string n,short lv,short s,short c,short mp,short w): human(n,lv,s,c,mp,w) {}

berserker* berserker::clone() const{
    return new berserker(*this);
}

character* berserker::attack(character* enemy,const short& Mdp) throw(Error)
try
{
    short hp;
    if(enemy->getHP() && isAlive())
    {
        if(Mdp>=0 && enemy!=this)//se è un attacco offensivo non è possibile autoinfliggerselo
            hp=enemy->getHP()-(getDP()+Mdp+getStrength());
        else
        {	if(Mdp<0)//attacco con effetto curativo
                hp=enemy->getHP()-Mdp;
            else//Mdp>=0 && enemy==this
            {	
                throw Error();
                return NULL;
            }
        }
        enemy->setHP(hp);
    }
    return enemy;
}
catch(Error e){
    cout<<"Invalid target "<<endl;
}

bool berserker::trance(){//aumenta wisdom al valore massimo
    if(isAlive()){
        short MPcost(10);
        short maxStat=getLV()*5;
        short idStat=2;
        return spell(NULL,MPcost,maxStat,idStat);
    }
    else
        return NULL;
}

character* berserker::iperfury(character* enemy){
    if(isAlive()){
        short MPcost(20);
        short iperfuryDP=(getWisdom()+MPcost*15/3);
        return spell(enemy,MPcost,iperfuryDP);
    }
    else
        return NULL;
}
