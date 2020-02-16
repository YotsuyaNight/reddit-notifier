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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "post.h"
#include "postlistmodel.h"
#include <QListView>
#include <QVector>
#include <QSharedPointer>

namespace rn {

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    QListView* getPostViewWidget();

public slots:
    void watcherFoundMatchingPosts(QSharedPointer<QVector<Post>> list);

signals:
    void newPosts(QSharedPointer<QVector<Post>> list);

private:
    PostListModel *model;
    QVector<Post> postList;

};

}

#endif