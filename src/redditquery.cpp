/*
* This file is part of "Reddit Notifier".
* 
* Copyright 2020 Marcin Dłubakowski <marcin@dlubakowski.pl>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "redditquery.h"
#include "postparser.h"
#include <QUrl>
#include <QDebug>

namespace rn {

QNetworkAccessManager RedditQuery::nam;

RedditQuery::RedditQuery(const QString &subreddit, const QString &sort, const QString &before)
    : subreddit(subreddit), sort(sort), before(before)
{
}

void RedditQuery::fire()
{
    QUrl url(QString("https://www.reddit.com/r/%1/%2/.json").arg(subreddit).arg(sort));
    reply = nam.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &RedditQuery::replyFinished);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
            this, &RedditQuery::replyError);
}

int RedditQuery::getStatus()
{
    return status;
}

QVector<Post> RedditQuery::getData()
{
    return data;
}

void RedditQuery::replyFinished()
{
    QByteArray rawData = reply->readAll();
    PostParser parser(rawData);
    if (parser.isValid()) {
        data = parser.parse();
    }
    status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    reply->deleteLater();
    emit done();
}

void RedditQuery::replyError(QNetworkReply::NetworkError code)
{
    status = code;
    reply->deleteLater();
    emit done();
}

}
