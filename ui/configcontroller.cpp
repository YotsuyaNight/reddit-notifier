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

#include "configcontroller.h"
#include "notifierconfig.h"
#include <QLabel>

namespace rn {

ConfigController::ConfigController(QVBoxLayout *container)
    : container(container)
{
    // Connect NotifierConfig signals
    NotifierConfig *config = NotifierConfig::get();
    connect(config, &NotifierConfig::notifierAdded, this, &ConfigController::notifierAdded);
    connect(config, &NotifierConfig::notifierRemoved, this, &ConfigController::notifierRemoved);

    // Prepare new Notifier widget
    QLabel *newNotifierLabel = new QLabel();
    QLabel *existingNotifiersLabel = new QLabel();
    QFont font;
    font.setPointSize(18);
    newNotifierLabel->setFont(font);
    existingNotifiersLabel->setFont(font);
    newNotifierLabel->setText("Add new notifier:");
    existingNotifiersLabel->setText("Active notifiers:");

    newNotifier = new Notifier("", "new");
    newNotifierWidget = new NotifierViewWidget(newNotifier);

    container->addWidget(newNotifierLabel);
    container->addWidget(newNotifierWidget);
    container->addWidget(existingNotifiersLabel);

    connect(newNotifier, &Notifier::updated, this, &ConfigController::newNotifierCreated);

    // Add all preexisting notifiers
    for (Notifier *n : config->getNotifiers()) {
        notifierAdded(n);
    }
}

void ConfigController::newNotifierCreated()
{
    // Store pointers to old elements
    Notifier *prevNewNotifier = newNotifier;
    NotifierViewWidget *prevNewNotifierWidget = newNotifierWidget;
    // Replace them with new versions
    newNotifier = new Notifier("", "new");
    newNotifierWidget = new NotifierViewWidget(newNotifier);
    container->replaceWidget(prevNewNotifierWidget, newNotifierWidget);
    connect(newNotifier, &Notifier::updated, this, &ConfigController::newNotifierCreated);
    delete prevNewNotifierWidget;
    NotifierConfig::get()->addNotifier(prevNewNotifier);
}

void ConfigController::notifierAdded(Notifier *notifier)
{
    NotifierViewWidget *widget = new NotifierViewWidget(notifier);
    notifierWidgetList.insert(notifier, widget);
    container->addWidget(widget);
}

void ConfigController::notifierRemoved(Notifier *notifier)
{
    NotifierViewWidget *widget = notifierWidgetList.value(notifier);
    container->removeWidget(widget);
    notifierWidgetList.remove(notifier);
    delete widget;
}


}
