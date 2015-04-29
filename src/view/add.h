#ifndef ADD_H
#define ADD_H

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>
#include <QCloseEvent>

class add: public QDialog
{
   Q_OBJECT
private:
    QGroupBox *groupBox;
    QRadioButton **radioArray;
    QLabel *labelD;
    QLabel *labelH;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton0;
    QPushButton *pushButton1;
public:
    add(QWidget* parent=0);
    void closeEvent(QCloseEvent* event);
private slots:
    void closeDialog();
    void submit() const;
signals:
    void addOK(const QString&,const bool&,QWidget*) const;
};

#endif // ADD_H
