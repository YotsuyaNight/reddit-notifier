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

#ifndef REDDITQUERY_H
#define REDDITQUERY_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

namespace rn {

class RedditQuery : public QObject
{
    Q_OBJECT

public:
    RedditQuery(const QString &subreddit, const QString &sort, const QString &before = "");
    void fire();

private slots:
    void replyFinished();
    void replyError(QNetworkReply::NetworkError code);

private:
    static QNetworkAccessManager nam;
    QString subreddit;
    QString sort;
    QString before;
    QNetworkReply *reply;

};

}

#endif
