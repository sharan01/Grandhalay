#ifndef BOOKINFOONLINE_H
#define BOOKINFOONLINE_H

#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
class BookInfoOnline : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager* nam;
    QNetworkReply* reply;
    QUrl url;
    QByteArray data;
public:
    explicit BookInfoOnline();
    void fetchBookInfo(QString isbn);
public slots:
    void finishedSlot(QNetworkReply* reply);
};

#endif // BOOKINFOONLINE_H
