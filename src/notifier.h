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

#ifndef NOFITIER_H
#define NOTIFIER_H

#include "post.h"
#include <QString>
#include <QRegularExpression>
#include <QVector>
#include <QTime>

namespace rn {

class Notifier
{
public:
    Notifier(const QString &subreddit, const QString &sort, int interval = 60);
    bool addFilter(const QString &pattern, QString *error = nullptr);
    QVector<Post> filter(const QVector<Post> &list) const;
    QString getSubreddit() const;
    QString getSort() const;
    int getInterval() const;

private:
    QString subreddit;
    QString sort;
    QVector<QRegularExpression> filters;
    int interval;

};

inline bool operator<(const Notifier &one, const Notifier &two)
{
    return one.getSubreddit() < two.getSubreddit();
}

}

#endif
