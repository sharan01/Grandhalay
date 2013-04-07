#ifndef ADDMEMBERWIZARD_H
#define ADDMEMBERWIZARD_H

#include <QWizard>
#include <QLayout>
#include <QtWidgets>
#include <QtSql>
class AddMemberWizard : public QWizard
{
    Q_OBJECT
public:
    explicit AddMemberWizard(QWidget *parent = 0);
    void accept();
    
signals:
    
public slots:
    
};
 // =============================== //
// first page
class MembersPage : public QWizardPage
{
    Q_OBJECT

public:
    MembersPage(QWidget *parent = 0);
public slots:


private:
    QLabel *rollLabel;
    QLabel *nameLabel;
    QLabel *branchLabel;
    QLabel *phoneLabel;
    QLabel *emailLabel;

    QLineEdit *rollEdit;
    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
    QLineEdit *emailEdit;

    QComboBox *branchSelector;


    QGridLayout *layout;


    void createWidgets();
    void createLayout();
    void registerFields();
};



#endif // ADDMEMBERWIZARD_H
