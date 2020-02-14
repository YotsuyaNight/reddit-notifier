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

#include "postdelegate.h"
#include <QPainter>

namespace rn {

PostDelegate::PostDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{
}


void PostDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    int padding = 3;
    int voffset = option.rect.y();
    int width = option.rect.width();
    int height = option.rect.height();

    QColor color(64, 64, 64);
    if (index.row() % 2 == 0)
        color = QColor(0, 0, 0);

    painter->fillRect(0 + padding,
                      0 + voffset + padding,
                      width - padding,
                      height - padding,
                      QBrush(color));

    painter->drawText(padding + 20, voffset + padding + 20, index.data().toString());
}

QSize PostDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    return QSize(300, 50);
}

}
