#include "bookinfoonline.h"
#include <iostream>
using namespace std;

BookInfoOnline::BookInfoOnline()
{
    nam = new QNetworkAccessManager(this);


}
void BookInfoOnline::fetchBookInfo(QString isbn)
{
    QString link = "https://www.googleapis.com/books/v1/volumes?q=isbn:" + isbn;
    qDebug() << link;
    url.setUrl(link);
    reply = nam->get(QNetworkRequest(url));

    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedSlot(QNetworkReply*)));

}

void BookInfoOnline::finishedSlot(QNetworkReply* reply)
{
    // Reading attributes of the reply
    // e.g. the HTTP status code
    QVariant statusCodeV =
    reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    // Or the target URL if it was a redirect:
    QVariant redirectionTargetUrl =
    reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    // see CS001432 on how to handle this

    // no error received?
    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here

        // Example 1: Creating QImage from the reply
       // QImageReader imageReader(reply);
        //QImage pic = imageReader.read();

        // Example 2: Reading bytes form the reply
        data = reply->readAll();  // bytes
        QString stri(data); // string

        qDebug() << stri;
    }
    // Some http error received
    else
    {
        // handle errors here
    }

    // We receive ownership of the reply object
    // and therefore need to handle deletion.
    delete reply;
}
