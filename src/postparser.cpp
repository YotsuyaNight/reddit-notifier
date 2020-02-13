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

#include "postparser.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

namespace rn {

PostParser::PostParser(const QByteArray &data)
{
    document = QJsonDocument::fromJson(data, &error);
}

bool PostParser::isValid()
{
    return !document.isNull();
}

QString PostParser::errorMessage()
{
    return error.errorString();
}

QVector<Post> PostParser::parse()
{
    QJsonArray posts = document.object().find("data").value().toObject()
                                        .find("children").value().toArray();

    QVector<Post> postList = QVector<Post>();
    for (QJsonArray::Iterator it = posts.begin(); it != posts.end(); it++) {
        QJsonObject post = it->toObject().find("data").value().toObject();
        Post item(
            post.find("title").value().toString(),
            post.find("author").value().toString(),
            post.find("selftext").value().toString(),
            QUrl(post.find("url").value().toString()),
            QUrl(QStringLiteral("http://www.reddit.com") + post.find("permalink").value().toString())
        );
        postList.append(item);
    }
    return postList;
}

}
