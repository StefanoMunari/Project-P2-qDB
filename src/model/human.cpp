#include "human.h"

human::human(string n,short lv,short s,short c,short mp,short w): character(n,lv,s,c) {
    setStat(MP,mp);
    character::setStat(wisdom,w);
}

void human::chooseStat(const short& val,const short& id){
    if(id==2)
        character::setStat(wisdom,val);
    else
        character::chooseStat(val,id);
}

void human::setStat(short& t,const short& value){
    if(value>=0 && value<=(getLV()*10+getLV()/10))//il valore massimo varia in base al LV,sarà sempre <=999
        t=value;
    else{
        if(value<0)
            t=0;
        else
            t=getLV()*10+getLV()/10;
    }
}

short human::getMP() const { return MP;}

short human::getWisdom() const { return wisdom;}

character* human::spell(character* enemy,const short& mpReq,const short& dp,const short& id) throw(Error)
try
{
    if(mpReq <= MP)
    {
        MP= MP-mpReq;
        if(enemy==NULL)//sentinella che indica che si tratta di una magia che modifica le statistiche,NON ESISTONO ALTRE MAGIE CON enemy==NULL
        {	chooseStat(dp,id);//in questo caso uso dp come valore a cui settare la statistica il cui nome corrisponde ad id.assumo che id sia sempre un id valido
            return this;}
        else//è una magia offensiva oppure curativa
            return attack(enemy,dp);
    }
    throw Error();
    return NULL;
}
catch(Error e){
    cout<<"the spell requires more MP "<<endl;
}
