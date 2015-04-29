#ifndef FUNCTOR_H
#define FUNCTOR_H
#include "alchemist.h"
#include "berserker.h"
#include "golem.h"

template <class T> class functor//mi serve per avere un parametro generico per find() di container
{
protected:
    T f;
    functor(T value): f(value) {}
public:
    bool equal(const T& p) const { return p==f;}
    virtual bool operator() (const smartCharacter& sc) const =0;
    virtual ~functor() {}
};

class name: public functor<string> {
public:
    name(const string& s): functor<string>(s) {}
    bool operator() (const smartCharacter& sc) const {return equal(sc->getName());}
};

class type: public functor<string> {
public:
    type(const string& s): functor<string>(s) {}
    bool operator() (const smartCharacter& sc) const {
        if(f=="Golem")
        {
            golem* p=dynamic_cast<golem*>(&(*sc));
            if(p)
                return true;
        }
        else
        {
            if(f=="Alchemist")
            {
                alchemist* p=dynamic_cast<alchemist*>(&(*sc));
                if(p)
                    return true;
            }
            else
            {
                if(f=="Berserker")
                {
                    berserker* p=dynamic_cast<berserker*>(&(*sc));
                    if(p)
                        return true;
                }
            }
        }
        return false;
    }
};

class hp: public functor<short> {
public:
    hp(const short& s): functor<short>(s) {}
    bool operator() (const smartCharacter& sc) const { return equal(sc->getHP());}
};

class mp: public functor<short> {
    public:
    mp(const short& s): functor<short>(s) {}
    bool operator() (const smartCharacter& sc) const {
        human* p=dynamic_cast<human*>(&(*sc));
        if(p)
            return equal(p->getMP());
        else
            return false;
    }
};

class lv: public functor<short> {
public:
    lv(const short& s): functor<short>(s) {}
    bool operator() (const smartCharacter& sc) const { return equal(sc->getLV());}
};

class strength: public functor<short> {
public:
    strength(const short& s): functor<short>(s) {}
    bool operator() (const smartCharacter& sc) const { return equal(sc->getStrength());}
};

class constitution: public functor<short> {
public:
    constitution(const short& s): functor<short>(s) {}
    bool operator() (const smartCharacter& sc) const { return equal(sc->getConstitution());}
};

class wisdom: public functor<short> {
public:
    wisdom(const short& s): functor<short>(s) {}
    bool operator() (const smartCharacter& sc) const {
        human* p=dynamic_cast<human*>(&(*sc));
        if(p)
            return equal(p->getWisdom());
        else
            return false;
    }
};
#endif // FUNCTOR_H
