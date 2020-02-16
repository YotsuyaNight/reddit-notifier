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

#include "mainwindow.h"
#include "postdelegate.h"
#include <QDebug>

namespace rn {

MainWindow::MainWindow()
{
    setupUi(this);
    PostDelegate *delegate = new PostDelegate(this);
    model = new PostListModel(this);
    postView->setItemDelegate(delegate);
    postView->setModel(model);
}

QListView* MainWindow::getPostViewWidget()
{
    return postView;
}

void MainWindow::watcherFoundMatchingPosts(QSharedPointer<QVector<Post>> list)
{
    QSharedPointer<QVector<Post>> newPostsList(new QVector<Post>());
    for (Post p : *list) {
        if (postList.indexOf(p) == -1) {
            newPostsList->append(p);
        }
    }
    if (newPostsList->size() > 0) {
        postList.append(*newPostsList);
        model->postListUpdated(postList);
        emit newPosts(newPostsList);
    }
}

}
