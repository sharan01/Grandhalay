#ifndef BOOKINFOONLINE_H
#define BOOKINFOONLINE_H

#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
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
    std::vector<QString> vec;

    void processJson(QString d);

public:
    explicit BookInfoOnline();
    ~BookInfoOnline();
    void fetchBookInfo(QString isbn);
     std::vector<QString> getInfo();
signals:
    void infoFetched();
public slots:
    void finishedSlot(QNetworkReply* reply);
};

#endif // BOOKINFOONLINE_H
