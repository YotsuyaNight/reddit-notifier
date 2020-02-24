/*
* This file is part of "Reddit Notifier".
* 
* Copyright 2020 Marcin Dłubakowski <marcin@dlubakowski.pl>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version->
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "notifierconfig.h"
#include "redditquery.h"
#include "watcher.h"
#include <QDebug>

namespace rn {

Watcher::Watcher()
{
    NotifierConfig cfg;
    notifiers.append(cfg.getNotifiers());
    connect(&timer, &QTimer::timeout, this, &Watcher::query);
    timer.start(30000);
    query();
}

void Watcher::query()
{
    if (queries.size() == 0) {
        QTime current = QTime::currentTime();
        for (Notifier *n : notifiers) {
            if (nextCheck.value(n) <= current) {
                queries.insert(n, new RedditQuery(n->getSubreddit(), n->getSort()));
            }
        }
        if (queries.size() > 0) {
            barrierCount = queries.size();
            qDebug() << "Initialized barrier with count=" << barrierCount;
            QMap<Notifier*, RedditQuery*>::Iterator it = queries.begin();
            while (it != queries.end()) {
                connect(*it, &RedditQuery::done, this, &Watcher::reachBarrier);
                (*it)->fire();
                nextCheck.insert(it.key(), current.addSecs(it.key()->getInterval()));
                it++;
            }
        }
    } else {
        qDebug() << "Previous queries are still pending, skipping this iteration";
    }
}

void Watcher::reachBarrier()
{
    barrierCount -= 1;
    qDebug() << "Arrived at barrier, current count =" << barrierCount;
    if (barrierCount == 0) {
        QSharedPointer<QVector<Post>> newPosts(new QVector<Post>());
        QMap<Notifier*, RedditQuery*>::Iterator it = queries.begin();
        while (it != queries.end()) {
            QVector<Post> filteredPosts = it.key()->filter((*it)->getData());
            newPosts->append(filteredPosts);
            delete (*it);
            it++;
        }
        emit foundMatchingPosts(newPosts);
        queries.clear();
    }
}

}
