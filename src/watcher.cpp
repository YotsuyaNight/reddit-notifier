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
#include "watcher.h"
#include <QDebug>

namespace rn {

Watcher::Watcher()
{
    Notifier a("linux", "new", 2);
    a.addFilter(".*");
    notifiers.append(a);
    Notifier b("manga", "new", 6);
    b.addFilter(".*");
    notifiers.append(b);

    connect(&timer, &QTimer::timeout, this, &Watcher::query);
    timer.start(1000);
    query();
}

void Watcher::query()
{
    for (Notifier n : notifiers) {
        QTime current = QTime::currentTime();
        if (nextCheck.value(n) <= current) {
            QSharedPointer<RedditQuery> query(new RedditQuery(n.getSubreddit(), n.getSort()));
            connect(&(*query), &RedditQuery::done, [this, n, query](){
                redditQueryCallback(query, n);
            });
            query->fire();
            nextCheck.insert(n, current.addSecs(n.getInterval()));
            qDebug() << "Fired query for " << n.getSubreddit() << "/" << n.getSort();
        }
    }
}

void Watcher::redditQueryCallback(QSharedPointer<RedditQuery> query, const Notifier &n)
{
    qDebug() << "Called callback for " << n.getSubreddit() << "/" << n.getSort();
    PostParser parser(query->getData());
    if (parser.isValid()) {
        QVector<Post> list = parser.parse();
        QSharedPointer<QVector<Post>> matching(new QVector<Post>(n.filter(list)));
        if (matching->size() > 0) {
            emit foundMatchingPosts(matching);
        }
    }
}

}
