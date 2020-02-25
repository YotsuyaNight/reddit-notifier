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

namespace rn {

ConfigController::ConfigController(QVBoxLayout *container)
    : container(container)
{
    newNotifier = new Notifier("", "");
    newNotifierWidget = new NotifierViewWidget(newNotifier);
    connect(newNotifier, &Notifier::updated, this, &ConfigController::addNewNotifier);

    connect(NotifierConfig::get(), &NotifierConfig::notifiersChanged,
            this, &ConfigController::notifiersChanged);
    notifiersChanged();
}

void ConfigController::addNewNotifier()
{
    // Store objects for reference
    Notifier *addedNotifier = newNotifier;
    NotifierViewWidget *oldWidget = newNotifierWidget;
    // Create new objects for replacement
    newNotifier = new Notifier("", "");
    newNotifierWidget = new NotifierViewWidget(newNotifier);
    // Update config with new notifier
    NotifierConfig *config = NotifierConfig::get();
    config->addNotifier(addedNotifier);
    // Delete
    connect(newNotifier, &Notifier::updated, this, &ConfigController::addNewNotifier);
    delete oldWidget;
}

void ConfigController::notifiersChanged()
{
    // Clear container
    while (container->count() > 0) {
        QLayoutItem *item = container->takeAt(0);
        container->removeItem(item);
        delete item;
    }
    // New notifier widget
    container->addWidget(newNotifierWidget);
    // Widgets for notifiers
    NotifierConfig *config = NotifierConfig::get();
    for (Notifier *n : config->getNotifiers()) {
        NotifierViewWidget *widget = new NotifierViewWidget(n);
        container->addWidget(widget);
    }

}

}
