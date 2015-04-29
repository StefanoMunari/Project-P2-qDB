#ifndef _controller_H
#define	_controller_H

#include "container.h"
#include "character.h" //smartCharacter contenuto al suo interno
#include <QString>

class Controller{
private:
	Container<smartCharacter*> model;
public:
    Controller();
    void insert(const smartCharacter* =0);
    bool remove(const int&);
    smartCharacter& getElement() const;
    QString* modify(const int&,QString*,const short&);
    int modelSize() const;
    void clearModel();
    QList<int>* search(QString,const int&) const;
};
#endif
