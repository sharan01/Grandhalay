#include "bookinfoonline.h"
#include <iostream>
using namespace std;

BookInfoOnline::BookInfoOnline()
{
    nam = new QNetworkAccessManager(this);

    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),this, SLOT(finishedSlot(QNetworkReply*)));

}
void BookInfoOnline::fetchBookInfo(QString isbn)
{
    QString link = "https://www.googleapis.com/books/v1/volumes?q=isbn:" + isbn;
    qDebug() << link;
    url.setUrl(link);
    reply = nam->get(QNetworkRequest(url));

}
void BookInfoOnline::processJson(QString d)
{
    qDebug() << d;
    QJsonDocument doc = QJsonDocument::fromJson(d.toUtf8());
    qDebug() << doc.isNull();


    QJsonObject jsonobj = doc.object();

    QJsonValue jv  = jsonobj.value("items");
    //return vec

    if(!jv.isUndefined()){

        QJsonValue fvalue = jv.toArray().first();
        QJsonObject itemobj = fvalue.toObject();

        QJsonObject volumeInfo = itemobj.value("volumeInfo").toObject();
        QString title =  volumeInfo.value("title").toString();
        QString author = volumeInfo.value("authors").toArray().first().toString();
        QString publishedDate = volumeInfo.value("publishedDate").toString();
        QString publisher = volumeInfo.value("publisher").toString();

        qDebug() << title << author << publisher << publishedDate;
        vec.push_back(title);
        vec.push_back(author);
        vec.push_back(publisher);
        vec.push_back(publishedDate);

    }else{
        qDebug() << "items is undefined";
        for(int i=0; i<4; i++){
            vec.push_back("");
        }
    }
}

std::vector<QString> BookInfoOnline::getInfo()
{
    return vec;
}

// slots ============
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

        //qDebug() << stri;
        //process json(data)
        processJson(stri);

        emit infoFetched();

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
