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

#include "watcher.h"
#include <QDebug>

namespace rn {

Watcher::Watcher(const QString &subreddit, const QString &sort)
    : subreddit(subreddit), sort(sort)
{
}

bool Watcher::addFilter(const QString &pattern, QString *error)
{
    QRegularExpression expr(pattern);
    if (!expr.isValid()) {
        *error = expr.errorString();
        return false;
    }
    filters.append(expr);
    return true;
}

QVector<Post> Watcher::filter(const QVector<Post> &list)
{
    QVector<Post> filtered;
    for (Post post : list) {
        for (QRegularExpression expr : filters) {
            QRegularExpressionMatch match = expr.match(post.getTitle());
            if (match.hasMatch()) {
                filtered.append(post);
            }
        }
    }
    return filtered;
}

}