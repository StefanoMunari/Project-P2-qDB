#ifndef EXCVIEW_H
#define EXCVIEW_H

#include <QString>

class Mod{};//errore di modifica del file in corso
class EmptyData{};//errore di dati non presenti
class ErrorSearch{};//errore durante la ricerca
class OnlyRead{}; //se il file aperto è in sola lettura allora non è possibile sovrascriverlo
class ErrorOpen{
private:
    QString error;
 public:
    ErrorOpen(QString e):error(e){}
    const QString& Error() const{return error;}
};

class ErrorSave{};//errori durante il salvataggio
class Max{};      //errore di limite massimo di elementi inseribili
#endif
