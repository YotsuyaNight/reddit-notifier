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

#include "notifier.h"
#include <QDebug>

namespace rn {

Notifier::Notifier(const QString &subreddit, const QString &sort, int interval)
    : subreddit(subreddit), sort(sort), interval(interval)
{
}

bool Notifier::addFilter(const QString &pattern, QString *error)
{
    QRegularExpression expr(pattern);
    if (!expr.isValid() && error != nullptr) {
        *error = expr.errorString();
        return false;
    }
    filters.append(expr);
    return true;
}

QVector<Post> Notifier::filter(const QVector<Post> &list) const
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

QString Notifier::getSubreddit() const
{
    return subreddit;
}

QString Notifier::getSort() const
{
    return sort;
}

int Notifier::getInterval() const
{
    return interval;
}

QVector<QRegularExpression> Notifier::getFilters() const
{
    return filters;
}

}
