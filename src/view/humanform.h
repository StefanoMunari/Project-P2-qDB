#ifndef HUMANFORM_H
#define HUMANFORM_H

#include "form.h"

class humanform: public form
{
    Q_OBJECT
private:
    QLabel *label_4;
    QLabel *label_5;
public:
    humanform(const QString&,QWidget *parent =0);
private slots:
    virtual void submitForm();
};
#endif
