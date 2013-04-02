#ifndef BOOKINFOONLINE_H
#define BOOKINFOONLINE_H

#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QDebug>
#include <vector>
class BookInfoOnline : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager* nam;
    QNetworkReply* reply;
    QUrl url;
    QByteArray data;
    std::vector<QString> processJson(QByteArray d);
public:
    explicit BookInfoOnline();
    void fetchBookInfo(QString isbn);
signals:
    void dataFetched(QByteArray d);
public slots:
    void finishedSlot(QNetworkReply* reply);
};

#endif // BOOKINFOONLINE_H
