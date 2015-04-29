#include "alchemist.h"

alchemist::alchemist(string n,short lv,short s,short c,short mp,short w): human(n,lv,s,c,mp,w) {}

alchemist* alchemist::clone() const{
    return new alchemist(*this);
}

character* alchemist::attack(character* enemy,const short& Mdp) throw(Error)
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

character* alchemist::sulfur(character* enemy){//devo calcolare l'aumento di DP attraverso le stat di Wisdom essendo una magia
    if(isAlive()){
        short MPcost(7);//l'incremento di DP deve dipendere anche dal costo della magia altrimenti non riesco a discriminare bene tra le diverse magie in termini di effetto
        short sulfurDP=(getWisdom()+(MPcost*15)/3);
        return spell(enemy,MPcost,sulfurDP);}
    else
        return NULL;
}

character* alchemist::cure(character* fellow){
    if(isAlive()){
        short MPcost(5);//MPcost>0
        short cureP(-(getWisdom()*5+(MPcost*15)/3));//CurePoints il cui valore è negativo,quindi cureP è un valore opposto a DP
        return spell(fellow,MPcost,cureP);
    }
    else
        return NULL;
}
