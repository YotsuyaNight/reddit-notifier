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

#ifndef WATCHER_H
#define WATCHER_H

#include "post.h"
#include <QString>
#include <QRegularExpression>
#include <QVector>

namespace rn {

class Watcher
{
public:
    Watcher(const QString &subreddit, const QString &sort);
    bool addFilter(const QString &pattern, QString *error = nullptr);
    QVector<Post> filter(const QVector<Post> &list); 

private:
    QString subreddit;
    QString sort;
    QVector<QRegularExpression> filters;

};

}

#endif
