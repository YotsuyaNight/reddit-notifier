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

#include "postviewwidget.h"

namespace rn {

PostViewWidget::PostViewWidget(const Post &post, QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    QString titleUrl("/r/%1 <a href='%2'>%3</a>");
    QString titleText = post.getTitle();
    if (titleText.length() > 100) {
        titleText.truncate(100);
        titleText += QStringLiteral("...");
    }
    titleUrl = titleUrl.arg(post.getSubreddit()).arg(post.getPost().url()).arg(titleText);

    QString authorText = QString("posted by /u/%1").arg(post.getAuthor());

    QString commentsUrl = QString("<a href='%1'>Comments</a>").arg(post.getComments().url());

    title->setText(titleUrl);
    authorship->setText(authorText);
    comments->setText(commentsUrl);
}

}
