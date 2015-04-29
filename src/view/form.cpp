#include "form.h"
#include <QApplication>

form::form(const QString& s,QWidget* parent,const short& numLines): QDialog(parent),lines(numLines),type(s)
{
    input=new QLineEdit*[numLines];

    groupBox = new QGroupBox(this);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(10, 10, 480, 480));
    QFont font;
    font.setPointSize(14);
    groupBox->setFont(font);

    pushButton_sub = new QPushButton(groupBox);
    pushButton_sub->setObjectName(QString::fromUtf8("pushButton_sub"));
    pushButton_sub->setGeometry(QRect(340, 430, 110, 35));
    pushButton_canc = new QPushButton(groupBox);
    pushButton_canc->setObjectName(QString::fromUtf8("pushButton_canc"));
    pushButton_canc->setGeometry(QRect(200, 430, 110, 35));

    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(60, 240, 70, 30));
    QFont font1;
    font1.setPointSize(15);
    font1.setItalic(true);
    label->setFont(font1);

    layoutWidget1 = new QWidget(groupBox);
    layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
    layoutWidget1->setGeometry(QRect(80, 80, 370, 115));
    gridLayout1 = new QGridLayout(layoutWidget1);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    gridLayout1->setContentsMargins(0, 0, 0, 0);
    label_0 = new QLabel(layoutWidget1);
    label_0->setObjectName(QString::fromUtf8("label_0"));
    gridLayout1->addWidget(label_0, 0, 0, 1, 1);
    input[0] = new QLineEdit(layoutWidget1);
    input[0]->setObjectName(QString::fromUtf8("lineEdit_0"));
    gridLayout1->addWidget(input[0], 0, 1, 1, 1);
    label_1 = new QLabel(layoutWidget1);
    label_1->setObjectName(QString::fromUtf8("label_1"));
    gridLayout1->addWidget(label_1, 1, 0, 1, 1);
    input[1] = new QLineEdit(layoutWidget1);
    input[1]->setObjectName(QString::fromUtf8("lineEdit_1"));
    gridLayout1->addWidget(input[1], 1, 1, 1, 1);
    layoutWidget = new QWidget(groupBox);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(60, 290, 390, 90));
    gridLayout = new QGridLayout(layoutWidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    label_2 = new QLabel(layoutWidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    gridLayout->addWidget(label_2, 0, 0, 1, 1);
    input[2] = new QLineEdit(layoutWidget);
    input[2]->setObjectName(QString::fromUtf8("lineEdit_2"));
    gridLayout->addWidget(input[2], 0, 1, 1, 1);
    label_3 = new QLabel(layoutWidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    gridLayout->addWidget(label_3, 1, 0, 1, 1);
    input[3] = new QLineEdit(layoutWidget);
    input[3]->setObjectName(QString::fromUtf8("lineEdit_3"));
    gridLayout->addWidget(input[3], 1, 1, 1, 1);
//text e placeholder
    setWindowTitle(QApplication::translate("form", "Insert a new character", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("form",s.toStdString().c_str(),0,QApplication::UnicodeUTF8));
    pushButton_sub->setText(QApplication::translate("form", "Submit", 0, QApplication::UnicodeUTF8));
    pushButton_canc->setText(QApplication::translate("form", "Cancel", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("form", "Stats:", 0, QApplication::UnicodeUTF8));
    label_0->setText(QApplication::translate("form", "Name", 0, QApplication::UnicodeUTF8));
    label_1->setText(QApplication::translate("form", "Level", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("form", "Strength", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("form", "Constitution", 0, QApplication::UnicodeUTF8));
    input[0]->setPlaceholderText("insert a string");
    input[1]->setPlaceholderText("insert an integer between 1 and 99");
    input[2]->setPlaceholderText("insert an integer between 0 and 495");
    input[3]->setPlaceholderText("insert an integer between 0 and 495");
    pushButton_sub->setDefault(true);
//espressioni regolari per limitare il range di valori inseribili
    QRegExp re("^\\S+(\\s*\\S*)*$");
    input[0]->setValidator(new QRegExpValidator(re, this));
    re.setPattern("^[1-9][0-9]?$");
    input[1]->setValidator(new QRegExpValidator(re, this));
    re.setPattern("^0?^([1-9][0-9])?^([1-3][0-9][0-9])?^(4[0-9][0-5])?$");
    input[2]->setValidator(new QRegExpValidator(re, this));
    input[3]->setValidator(new QRegExpValidator(re, this));
//connect
    connect(pushButton_canc,SIGNAL(clicked()),this,SLOT(close()));
    connect(pushButton_sub,SIGNAL(clicked()),this,SLOT(submitForm()));
}

void form::closeDialog(){
    for(short i=0;i<lines;++i)
        delete input[i];
    delete [] input;
}

void form::closeEvent(QCloseEvent* event){
    closeDialog();
    event->accept();
}

void form::submitForm()
{
    bool completed=true;
    checkfields(completed,4);
    if(completed)
    {
        if(type=="Golem")
            emit validForm(new golem(input[0]->text().toStdString(),input[1]->text().toShort(),input[2]->text().toShort(),input[3]->text().toShort()),type);
        this->close();
    }
}

void form::checkfields(bool& completed,short size) const
{
    for(short i=0;i<size;++i)
    {
        if(input[i]->text().isEmpty())
        {
            completed=false;
            input[i]->setPalette(Qt::red);
        }
        else
            input[i]->setPalette(Qt::gray);
    }
}
