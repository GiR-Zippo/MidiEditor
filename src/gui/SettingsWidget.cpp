/*
 * MidiEditor
 * Copyright (C) 2010  Markus Schwenk
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SettingsWidget.h"
#include "Appearance.h"

#include <QFrame>
#include <QLabel>
#include <QString>

SettingsWidget::SettingsWidget(QString title, QWidget* parent)
    : QWidget(parent)
{
    _title = title;
}

bool SettingsWidget::accept()
{
    return true;
}

QString SettingsWidget::title()
{
    return _title;
}

QWidget* SettingsWidget::createInfoBox(QString info)
{
    QLabel* label = new QLabel(info, this);
    QColor bgColor = Appearance::infoBoxBackgroundColor();
    QColor textColor = Appearance::infoBoxTextColor();
    QString styleSheet = QString("color: rgb(%1, %2, %3); background-color: rgb(%4, %5, %6); padding: 5px")
                        .arg(textColor.red()).arg(textColor.green()).arg(textColor.blue())
                        .arg(bgColor.red()).arg(bgColor.green()).arg(bgColor.blue());
    label->setStyleSheet(styleSheet);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignJustify);
    label->setOpenExternalLinks(true);
    return label;
}

QWidget* SettingsWidget::separator()
{
    QFrame* f0 = new QFrame(this);
    f0->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    return f0;
}

QIcon SettingsWidget::icon()
{
    return QIcon();
}
