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

#include "postviewcontroller.h"

namespace rn {

PostViewController::PostViewController(QVBoxLayout *container)
    : container(container)
{
}

PostViewController::~PostViewController()
{
    QVector<PostViewWidget*>::Iterator it = postWidgetList.begin();
    while (it != postWidgetList.end()) {
        delete (*it);
        it++;
    }
}

void PostViewController::watcherFoundMatchingPosts(QSharedPointer<QVector<Post>> list)
{
    QSharedPointer<QVector<Post>> newPostsList(new QVector<Post>());
    for (Post p : *list) {
        if (postList.indexOf(p) == -1) {
            newPostsList->append(p);
            PostViewWidget *widget = new PostViewWidget(p);
            container->addWidget(widget);
        }
    }
    if (newPostsList->size() > 0) {
        postList.append(*newPostsList);
        emit newPosts(newPostsList);
    }
}

}
