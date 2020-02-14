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

#include <QApplication>
#include "mainwindow.h"
#include "traycontroller.h"
#include "redditquery.h"

#include "post.h"
#include "postparser.h"
#include "postlistmodel.h"
#include "postdelegate.h"
#include <QVector>
#include <QTimer>
#include <QDebug>

using namespace rn; 

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    rn::MainWindow mw;
    TrayController tray(&app, &mw);

    PostListModel *model = new PostListModel(&mw);
    PostDelegate *delegate = new PostDelegate(&mw);
    mw.getPostViewWidget()->setModel(model);
    mw.getPostViewWidget()->setItemDelegate(delegate);

    RedditQuery query("linux", "new");
    QObject::connect(&query, &RedditQuery::done, [&query, model](){
        PostParser parser(query.getData());
        qDebug() << "Query returned status " << query.getStatus();
        QVector<Post> data = parser.parse();
        qDebug() << "Number of entries arrived: " << data.size();
        model->postListUpdated(data);
    });

    QTimer::singleShot(0, [&query](){
        qDebug() << "Firing query!";
        query.fire();
    });

    mw.show();

    return app.exec();
}
