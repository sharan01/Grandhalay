#ifndef SUMMARYWIZARD_H
#define SUMMARYWIZARD_H

#include <QWizard>
#include <QtWidgets>
#include <QtSql>

 // ============================================ //
class summaryWizardPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit summaryWizardPage(QString bid, QWidget *parent = 0);
    QString bookID;

    QLabel totalCopiesLabel;
    QLabel availbleCopiesLabel;

    QLabel booksIssuedLabel;

    QLineEdit totalCopiesEdit;
    QLineEdit availbleCopiesEdit;

    QTableView issuedTable;

    QSqlRelationalTableModel model;

    QGridLayout layout;

};
// ==========================================//
class summaryWizard : public QWizard
{
    Q_OBJECT
public:
    explicit summaryWizard(QString bID, QWidget *parent = 0);

    summaryWizardPage swp;




signals:

public slots:

};
#endif // SUMMARYWIZARD_H
