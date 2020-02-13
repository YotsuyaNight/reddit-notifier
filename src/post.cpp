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

#include "post.h"

namespace rn {

Post::Post(const QString &title, const QString &author, const QString &selfText,
           const QUrl &post, const QUrl &comments)
    : title(title), author(author), selfText(selfText), post(post), comments(comments)
{
}

QString Post::getTitle()
{
    return title;
}

QString Post::getAuthor()
{
    return author;
}

QString Post::getSelfText()
{
    return selfText;
}

QUrl Post::getComments()
{
    return comments;
}

QUrl Post::getPost()
{
    return post;
}

}
