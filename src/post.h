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

#ifndef POST_H
#define POST_H

#include <QString>
#include <QUrl>

namespace rn {

class Post
{
public:
    Post() = default;
    Post(const Post &other) = default;
    Post(const QString &title, const QString &author, const QString &selfText,
         const QString &subreddit, const QUrl &post, const QUrl &comments);
    QString getTitle() const;
    QString getAuthor() const;
    QString getSelfText() const;
    QString getSubreddit() const;
    QUrl getPost() const;
    QUrl getComments() const;
    bool operator==(const Post &other);

private:
    QString title;
    QString author;
    QString selfText;
    QString subreddit;
    QUrl post;
    QUrl comments;

};

}

#endif
