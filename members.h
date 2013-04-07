#ifndef MEMBERS_H
#define MEMBERS_H

#include <QtWidgets>
#include <QtSql>
#include "addmemberwizard.h"

class Members : public QWidget
{
    Q_OBJECT
private:



    //top widgets
    QComboBox *branchSelector;
    QPushButton *addMemberButton;
    QLineEdit *searchBar;
    QRadioButton *searchRadioRoll;
    QRadioButton *searchRadioName;
    QPushButton *searchButton;

    QTableView *membersTable;


    QSqlRelationalTableModel *model;
    QSortFilterProxyModel *proxyModel;


    QAction *editMemberAction;
    QAction *deleteMemberAction;
    QAction *returBookAction;
    QAction *viewSummaryAction;

    AddMemberWizard *amw;

    QGridLayout *searchLayout;
    QHBoxLayout *memberTopLayout;
    QVBoxLayout *memberLayout;

    void createModels();
    void createWidgets();
    void createLayout();
    void createConnections();


public:
    explicit Members(QWidget *parent);



signals:

public slots:

    void filterMembers(QString);
    void searchMembers();
    void addMember();
   // void editMember();
    //void deleteMember();

   // void returnBook();

    //void viewSummary();

};

#endif // MEMBERS_H
