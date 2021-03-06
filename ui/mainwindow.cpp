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
#include <QDebug>

namespace rn {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    pvc = new PostViewController(postView);
    connect(this, &MainWindow::watcherFoundMatchingPosts,
            pvc, &PostViewController::watcherFoundMatchingPosts);
    connect(pvc, &PostViewController::newPosts,
            this, &MainWindow::newPosts);
    pvc = new PostViewController(postView);
    cfc = new ConfigController(notifiersView);
}

MainWindow::~MainWindow()
{
    delete pvc;
    delete cfc;
}

}
