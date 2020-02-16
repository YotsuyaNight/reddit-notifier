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

#include "traycontroller.h"
#include <QIcon>

namespace rn {

TrayController::TrayController(QApplication *app, MainWindow *mainWindow) 
    : app(app), mainWindow(mainWindow)
{
    // Setup context menu
    menu = new QMenu();
    menu->addAction("Show", mainWindow, &MainWindow::show);
    menu->addAction("Exit", app, &QApplication::quit);

    // Setup icon
    icon.setIcon(QIcon(":icon.png"));
    icon.show();
    icon.setContextMenu(menu);

    // Setup notification connection
    connect(mainWindow, &MainWindow::newPosts, this, &TrayController::newPostsNotification);
}

TrayController::~TrayController()
{
    delete menu;
}

void TrayController::newPostsNotification(QSharedPointer<QVector<Post>> list)
{
    if (list->size() == 1) {
        icon.showMessage(
            QStringLiteral("New post in /r/") + list->at(0).getSubreddit(),
            "\"" + list->at(0).getTitle() + "\" by " + list->at(0).getAuthor()
        );
    } else {
        icon.showMessage(
            QString::number(list->size()) + QStringLiteral(" new posts"),
            "Check them out now!"
        );
    }
}

}