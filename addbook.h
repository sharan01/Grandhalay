#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QWidget>
#include <QtGui>

class AddBook : public QDialog
{
    Q_OBJECT
public:
    QLabel *info;
    QLabel *bookNo;
    QLabel *title;
    QLabel *author;
    QLabel *copies;
    QLabel *branch;
    QLabel *price;

    QLineEdit *bookNoInput;
    QLineEdit *titleInput;
    QLineEdit *authorInput;
    QLineEdit *copiesInput;
    QLineEdit *priceInput;

    QComboBox *branchInput;

    QPushButton *ok;
    QPushButton *edit;
    QPushButton *cancel;

    QVBoxLayout *mainlayout;
    QFormLayout *formLayout;
    QHBoxLayout *buttonLayout;

    explicit AddBook(int, QWidget *parent);
    int currentID;

    
signals:
    
public slots:
    
};

#endif // ADDBOOK_H
