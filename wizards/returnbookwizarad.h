#ifndef RETURNBOOKWIZARAD_H
#define RETURNBOOKWIZARAD_H

#include <QWizard>
#include <QtWidgets>
#include <QtSql>



class SelectBookPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit SelectBookPage(QWidget *parent = 0);
    void setMember(const QString &roll);
    int nextId() const;
private:
    QString memberID;
    QLabel rollLabel;
    QLabel nameLabel;
    QLabel branchLabel;


    QLabel booksTaken;

    QLineEdit roll;
    QLineEdit name;
    QLineEdit branch;

    QLineEdit selectedBookEdit; // invisible


    QTableView issuedBooksTable;
    QSqlRelationalTableModel model;




    QGridLayout layout;
private slots:
    void rowSelected(const QModelIndex &index);



};
// =========================== //
class ReturnFinalPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit ReturnFinalPage(QWidget *parent = 0);

private:
    QLabel infoLabel;
    QVBoxLayout layout;

};


/// ======================//
class ReturnBookWizarad : public QWizard
{
    Q_OBJECT
public:
    explicit ReturnBookWizarad(QWidget *parent = 0);
    void setMemberRoll(const QString &roll);
    QString memberRoll() const { return m_memberRoll; }
    void accept();

private:
    QString m_memberRoll;
    SelectBookPage sbp;
    ReturnFinalPage rfp;
signals:
    
    
};

#endif // RETURNBOOKWIZARAD_H
