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

#include <catch2/catch.hpp>
#include <QFile>
#include "notifierconfig.h"

using namespace rn;

TEST_CASE("Testing NotifierConfig config files")
{
    NotifierConfig *nc = NotifierConfig::get();
    QFile configFile(nc->getFilename());
    REQUIRE(configFile.size() == 0);

    // Testing save
    Notifier *n1 = new Notifier("linux", "new", 10);
    Notifier *n2 = new Notifier("manga", "hot", 20);
    n1->addFilter(".*");
    n1->addFilter("Test1");
    n2->addFilter(".*");
    n2->addFilter("Test2");
    nc->addNotifier(n1);
    nc->addNotifier(n2);

    REQUIRE(nc->getNotifiers().size() == 2);
    REQUIRE(nc->getNotifiers()[0]->getFilters().size() == 2);
    REQUIRE(nc->getNotifiers()[1]->getFilters().size() == 2);
    
    int sizeWithTwoNotifiers = configFile.size();
    REQUIRE(sizeWithTwoNotifiers > 0);

    // Testing load
    REQUIRE(nc->getNotifiers().size() == 2);
    REQUIRE(nc->getNotifiers()[0]->getFilters().size() == 2);
    REQUIRE(nc->getNotifiers()[1]->getFilters().size() == 2);

    // Testing removal
    nc->removeNotifier(nc->getNotifiers()[0]);
    REQUIRE(nc->getNotifiers().size() == 1);

    REQUIRE(configFile.remove() == true);

}
