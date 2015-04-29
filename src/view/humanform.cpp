#include "humanform.h"
#include "alchemist.h"
#include "berserker.h"
#include <QApplication>

humanform::humanform(const QString& s,QWidget *parent): form(s,parent,6)
{
    label_4 = new QLabel(layoutWidget);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    gridLayout1->addWidget(label_4, 2, 0, 1, 1);
    input[4] = new QLineEdit(layoutWidget);
    input[4]->setObjectName(QString::fromUtf8("lineEdit_4"));
    gridLayout1->addWidget(input[4], 2, 1, 1, 1);
    label_5 = new QLabel(layoutWidget1);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    gridLayout->addWidget(label_5, 2, 0, 1, 1);
    input[5] = new QLineEdit(layoutWidget1);
    input[5]->setObjectName(QString::fromUtf8("lineEdit_5"));
    gridLayout->addWidget(input[5], 2, 1, 1, 1);
    label_4->setText(QApplication::translate("humanform", "Magic Points", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("humanform", "Wisdom", 0, QApplication::UnicodeUTF8));
    input[4]->setPlaceholderText("insert an integer between 0 and 999");
    input[5]->setPlaceholderText("insert an integer between 0 and 495");
//espressioni regolari per limitare il range di valori inseribili
    QRegExp re("^([1-9][0-9][0-9])?^0?$");
    input[4]->setValidator(new QRegExpValidator(re, this));
    re.setPattern("^0?^([1-9][0-9])?^([1-3][0-9][0-9])?^(4[0-9][0-5])?$");
    input[5]->setValidator(new QRegExpValidator(re, this));
}

void humanform::submitForm()
{
    bool completed=true;
    checkfields(completed,6);
    if(completed)
    {
        if(type=="Alchemist")
            emit validForm(new alchemist(input[0]->text().toStdString(),input[1]->text().toShort(),input[2]->text().toShort(),input[3]->text().toShort(),input[4]->text().toShort(),input[5]->text().toShort()),type);
        else{
            if(type=="Berserker")
                emit validForm(new berserker(input[0]->text().toStdString(),input[1]->text().toShort(),input[2]->text().toShort(),input[3]->text().toShort(),input[4]->text().toShort(),input[5]->text().toShort()),type);
        }
         this->close();
    }
}
