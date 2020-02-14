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
#include "postlistmodel.h"
#include "postdelegate.h"
#include <QVector>

using namespace rn; 

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    rn::MainWindow mw;
    TrayController tray(&app, &mw);
    
    QVector<Post> posts;
    posts.append(Post(
        QString("Check out this dope app!"),
        QString("Yotsuya"), QString("I made it!"),
        QUrl("/r/linux/comments/f3pc50/which_sites_do_you_follow_to_stay_informed_about/"),
        QUrl("https://github.com/YotsuyaNight/reddit-notifier")));
    posts.append(Post(
        QString("App that is dope AF!"),
        QString("Yotsuya"), QString("I made it!"),
        QUrl("/r/linux/comments/f3pc50/which_sites_do_you_follow_to_stay_informed_about/"),
        QUrl("https://github.com/YotsuyaNight/reddit-notifier")));
    posts.append(Post(
        QString("This is a dope app!"),
        QString("Yotsuya"), QString("I made it!"),
        QUrl("/r/linux/comments/f3pc50/which_sites_do_you_follow_to_stay_informed_about/"),
        QUrl("https://github.com/YotsuyaNight/reddit-notifier")));

    PostListModel *model = new PostListModel(&mw);
    PostDelegate *delegate = new PostDelegate(&mw);
    model->postListUpdated(posts);
    mw.getPostViewWidget()->setModel(model);
    mw.getPostViewWidget()->setItemDelegate(delegate);

    mw.show();

    return app.exec();
}
