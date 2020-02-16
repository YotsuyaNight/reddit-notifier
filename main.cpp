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
#include "traycontroller.h"
#include "watcher.h"
#include <QApplication>

using namespace rn; 

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Reddit Notifier");
    app.setApplicationVersion("0.0.1");
    app.setWindowIcon(QIcon(":icon.png"));

    MainWindow mw;
    TrayController tray(&app, &mw);

    Watcher watcher;
    QObject::connect(&watcher, &Watcher::foundMatchingPosts,
                     &mw, &MainWindow::watcherFoundMatchingPosts);

    mw.show();

    return app.exec();
}
