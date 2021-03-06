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

#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include "notifierviewwidget.h"
#include <QVBoxLayout>
#include <QMap>

namespace rn {

class ConfigController : public QObject
{
    Q_OBJECT

public:
    ConfigController(QVBoxLayout *container);

public slots:
    void notifierAdded(Notifier *notifier);
    void notifierRemoved(Notifier *notifier);

private slots:
    void newNotifierCreated();

private:
    QVBoxLayout *container;
    Notifier *newNotifier;
    NotifierViewWidget *newNotifierWidget;
    QMap<Notifier*, NotifierViewWidget*> notifierWidgetList;

};

}

#endif
