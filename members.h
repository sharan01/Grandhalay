#ifndef MEMBERS_H
#define MEMBERS_H

#include <QtWidgets>
#include <QtSql>

class Members : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *memberTopLayout;
    QVBoxLayout *memberLayout;


    //top widgets
    QComboBox *branchSelector;
    QPushButton *addMemberButton;
    QLineEdit *searchBar;

    QTableView *membersTable;


    QSqlRelationalTableModel *model;
    QSortFilterProxyModel *proxyModel;


    QAction *editMemberAction;
    QAction *deleteMemberAction;
    QAction *returBookAction;
    QAction *viewSummaryAction;


    void createModels();
    void createWidgets();
    void createLayout();
    void createConnections();


public:
    explicit Members(QWidget *parent);



signals:

public slots:

    void filterMembers(QString);
    void searchMembers(QString s);
 //   void addMember();
   // void editMember();
    //void deleteMember();

   // void returnBook();

    //void viewSummary();

};

#endif // MEMBERS_H
