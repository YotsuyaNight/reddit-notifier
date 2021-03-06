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

#include "notifierconfig.h"
#include <QDebug>

namespace rn {

NotifierConfig *NotifierConfig::instance = nullptr;

NotifierConfig* NotifierConfig::get()
{
    if (instance == nullptr) {
        instance = new NotifierConfig();
    }
    return instance;
}

NotifierConfig::NotifierConfig()
{
    load();
}

void NotifierConfig::notifierUpdated()
{
    save();
}

void NotifierConfig::addNotifier(Notifier *notifier)
{
    notifierList.append(notifier);
    connect(notifier, &Notifier::updated, this, &NotifierConfig::notifierUpdated);
    save();
    emit notifierAdded(notifier);
}

void NotifierConfig::removeNotifier(Notifier *notifier)
{
    notifierList.removeAll(notifier);
    save();
    emit notifierRemoved(notifier);
    delete notifier;
}

QVector<Notifier*> NotifierConfig::getNotifiers() const
{
    return notifierList;
}

void NotifierConfig::load()
{
    // Return early in case list is initialized alredy
    if (notifierList.size() > 0)
        return;

    int count = settings.beginReadArray("Notifiers");
    for (int i = 0; i < count; i++) {
        settings.setArrayIndex(i);
        Notifier *n = new Notifier(
            settings.value("subreddit").toString(),
            settings.value("sort").toString(),
            settings.value("interval").toInt()
        );
        int filtersCount = settings.beginReadArray("Filters");
        for (int j = 0; j < filtersCount; j++) {
            settings.setArrayIndex(j);
            n->addFilter(settings.value("pattern").toString());
        }
        settings.endArray();
        notifierList.append(n);
        connect(n, &Notifier::updated, this, &NotifierConfig::notifierUpdated);
    }
    settings.endArray();
}

void NotifierConfig::save()
{
    settings.beginWriteArray("Notifiers");
    for (int i = 0; i < notifierList.size(); i++) {
        settings.setArrayIndex(i);
        Notifier *n = notifierList.at(i);
        settings.setValue("subreddit", n->getSubreddit());
        settings.setValue("sort", n->getSort());
        settings.setValue("interval", n->getInterval());
        settings.beginWriteArray("Filters");
        for (int j = 0; j < n->getFilters().size(); j++) {
            settings.setArrayIndex(j);
            settings.setValue("pattern", n->getFilters()[j].pattern());
        }
        settings.endArray();
    }
    settings.endArray();
    settings.sync();
}

QString NotifierConfig::getFilename() const
{
    return settings.fileName();
}

}
