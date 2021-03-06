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
           const QString &subreddit, const QUrl &post, const QUrl &comments)
    : title(title), author(author), selfText(selfText), 
      subreddit(subreddit), post(post), comments(comments)
{
}

QString Post::getTitle() const
{
    return title;
}

QString Post::getAuthor() const
{
    return author;
}

QString Post::getSelfText() const
{
    return selfText;
}

QString Post::getSubreddit() const
{
    return subreddit;
}

QUrl Post::getComments() const
{
    return comments;
}

QUrl Post::getPost() const
{
    return post;
}

bool Post::operator==(const Post &other)
{
    return (title == other.title && author == other.author);
}

}
