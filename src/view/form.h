#ifndef FORM_H
#define FORM_H

#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QRegExpValidator>
#include <QCloseEvent>
#include "golem.h"

class form: public QDialog
{
    Q_OBJECT
private:
    QGroupBox *groupBox;
    QPushButton *pushButton_sub;
    QPushButton *pushButton_canc;
    QLabel *label;
    QLabel *label_0;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    short lines;
protected:
    QLineEdit ** input;
    QString type;
    QWidget *layoutWidget;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
public:
    form(const QString&,QWidget* parent=0,const short& =4);
    void closeEvent(QCloseEvent* event);
    void checkfields(bool& completed,short size) const;
private slots:
    void closeDialog();
protected slots:
    virtual   void submitForm();

signals:
    void validForm(character*,const QString&);
};
#endif // FORM_H
