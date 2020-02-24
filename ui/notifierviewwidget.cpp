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

#include "notifierviewwidget.h"
#include <QDebug>

namespace rn {

NotifierViewWidget::NotifierViewWidget(Notifier *notifier, QWidget *parent)
    : QWidget(parent), notifier(notifier)
{
    setupUi(this);
    subreddit->setText(notifier->getSubreddit());
    sort->setCurrentText(notifier->getSort());
    interval->setValue(notifier->getInterval());

    // Connect value changes to button enabler
    connect(subreddit, &QLineEdit::textChanged, this, &NotifierViewWidget::edited);
    connect(sort, &QComboBox::currentTextChanged, this, &NotifierViewWidget::edited);
    connect(interval, &QSpinBox::textChanged, this, &NotifierViewWidget::edited);
    connect(saveButton, &QPushButton::clicked, this, &NotifierViewWidget::saveNotifier);
    connect(removeButton, &QPushButton::clicked, this, &NotifierViewWidget::removeNotifier);
}

void NotifierViewWidget::edited(QVariant value)
{
    Q_UNUSED(value);
    saveButton->setEnabled(true);
}

void NotifierViewWidget::saveNotifier()
{
    qDebug() << "Saved";
    saveButton->setEnabled(false);
}

void NotifierViewWidget::removeNotifier()
{
    qDebug() << "Should be removed now";
}

}
