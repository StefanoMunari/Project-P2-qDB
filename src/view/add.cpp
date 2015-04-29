#include "add.h"
#include <QApplication>

add::add(QWidget* parent): QDialog(parent)
{
		radioArray=new QRadioButton*[3];
        groupBox = new QGroupBox(this);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 20, 450, 300));
        for(short i=0;i<3;++i)
        	radioArray[i] = new QRadioButton(groupBox);

        radioArray[0]->setObjectName(QString::fromUtf8("radioButton"));
        radioArray[0]->setGeometry(QRect(140, 60, 260, 50));
        QFont font;
        font.setPointSize(13);
        radioArray[0]->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/alchemist.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioArray[0]->setIcon(icon);
        radioArray[0]->setIconSize(QSize(30, 30));
        radioArray[0]->setChecked(true);

        radioArray[1]->setObjectName(QString::fromUtf8("radioButton1"));
        radioArray[1]->setGeometry(QRect(140, 130, 240, 50));
        radioArray[1]->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/berserker.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioArray[1]->setIcon(icon1);
        radioArray[1]->setIconSize(QSize(30, 30));

        radioArray[2]->setObjectName(QString::fromUtf8("radioButton2"));
        radioArray[2]->setGeometry(QRect(140, 210, 220, 30));
        radioArray[2]->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/golem.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioArray[2]->setIcon(icon2);
        radioArray[2]->setIconSize(QSize(30, 30));

        labelD = new QLabel(groupBox);
        labelD->setObjectName(QString::fromUtf8("labelD"));
        labelD->setGeometry(QRect(40, 80, 60, 220));
        labelD->setFont(font);
        labelH = new QLabel(groupBox);
        labelH->setObjectName(QString::fromUtf8("labelH"));
        labelH->setGeometry(QRect(40, 40, 60, 60));
        labelH->setFont(font);

        layoutWidget = new QWidget(this);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(290, 330, 190, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton0 = new QPushButton(layoutWidget);
        pushButton0->setObjectName(QString::fromUtf8("pushButton0"));
        pushButton1 = new QPushButton(layoutWidget);
        pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
        horizontalLayout->addWidget(pushButton0);
        horizontalLayout->addWidget(pushButton1);

        setWindowTitle(QApplication::translate("add", "Add a new character", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("add", "Character", 0, QApplication::UnicodeUTF8));
        radioArray[0]->setText(QApplication::translate("add", "Alchemist", 0, QApplication::UnicodeUTF8));
        radioArray[1]->setText(QApplication::translate("add", "Berserker", 0, QApplication::UnicodeUTF8));
        labelD->setText(QApplication::translate("add", "Demon:", 0, QApplication::UnicodeUTF8));
        labelH->setText(QApplication::translate("add", "Human:", 0, QApplication::UnicodeUTF8));
        radioArray[2]->setText(QApplication::translate("add", "Golem", 0, QApplication::UnicodeUTF8));
        pushButton0->setText(QApplication::translate("add", "Cancel", 0, QApplication::UnicodeUTF8));
        pushButton1->setText(QApplication::translate("add", "OK", 0, QApplication::UnicodeUTF8));
        pushButton1->setDefault(true);

        connect(pushButton0,SIGNAL(clicked()),this,SLOT(close()));
        connect(pushButton1,SIGNAL(clicked()),this,SLOT(submit()));
        connect(this,SIGNAL(addOK(QString,bool,QWidget*)),parent,SLOT(actionForm(QString,bool,QWidget*)));
}

void add::closeDialog(){
    for(short i=0;i<3;++i)
        delete radioArray[i];
    delete [] radioArray;
}

void add::closeEvent(QCloseEvent* event){
    closeDialog();
    event->accept();
}

void add::submit() const{
    short i=0;
    bool human=true;//se true->è stata selezionata una sottoclasse di human,altrimenti->sottoclasse demon
    while(!(radioArray[i]->isChecked()))
        i++;
    QString s=radioArray[i]->text();
    if(i>1)//è una sottoclasse di demon
        human=false;
    emit addOK(s,human,const_cast<add*>(this));
}
