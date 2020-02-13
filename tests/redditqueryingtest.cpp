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

#include "redditquery.h"
#include "postparser.h"
#include <catch2/catch.hpp>
#include <QSignalSpy>
#include <QDebug>

using namespace rn;

RedditQuery query("manga", "new");

TEST_CASE("Query subreddit for data and parse it")
{

    SECTION("RedditQuery test")
    {
        QSignalSpy spy(&query, &RedditQuery::done);
        query.fire();
        spy.wait(10000);
        REQUIRE(query.getStatus() == 200);
        REQUIRE(query.getData().size() > 0);
    }

    SECTION("RedditQuery invalid link test")
    {
        RedditQuery invalidquery("ojhiowfbeioufjewnfoe", "wqdqwdq");
        QSignalSpy spy(&invalidquery, &RedditQuery::done);
        invalidquery.fire();
        spy.wait(10000);
        REQUIRE(invalidquery.getStatus() == 302);
    }

    SECTION("PostParser test")
    {
        QByteArray data = query.getData();
        PostParser parser(data);
        REQUIRE(parser.isValid() == true);
        QVector<Post> posts = parser.parse();
        for (int i = 0; i < posts.size(); i++) {
            REQUIRE(posts[i].getTitle() != "");
        }
    }

    SECTION("PostParser invalid data test")
    {
        QByteArray data("This is some invalid JSON data", 31);
        PostParser parser(data);
        REQUIRE(parser.isValid() == false);
    }

}
