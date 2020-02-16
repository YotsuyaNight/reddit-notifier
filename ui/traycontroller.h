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

#ifndef TRAY_H
#define TRAY_H

#include "mainwindow.h"
#include "post.h"
#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>

namespace rn {

class TrayController : public QObject
{
Q_OBJECT

public:
    explicit TrayController(QApplication *app, MainWindow *mainWindow);
    virtual ~TrayController();

public slots:
    void newPostsNotification(QSharedPointer<QVector<Post>> list);

private:
    QApplication *app;
    MainWindow *mainWindow;
    QMenu *menu;
    QSystemTrayIcon icon;

};

}

#endif