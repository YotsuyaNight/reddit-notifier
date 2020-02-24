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

#ifndef NOTIFIERVIEWWIDGET_H
#define NOTIFIERVIEWWIDGET_H

#include "ui_notifierviewwidget.h"
#include "notifier.h"
#include <QWidget>

namespace rn {

class NotifierViewWidget : public QWidget, public Ui::NotifierViewWidget
{
    Q_OBJECT

public:
    explicit NotifierViewWidget(Notifier *notifier, QWidget *parent = 0);

private slots:
    void edited(QVariant value);
    void saveNotifier();
    void removeNotifier();

private:
    Notifier *notifier;

};

}

#endif
