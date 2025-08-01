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

#include "AboutDialog.h"
#include "Appearance.h"

#include <QApplication>
#include <QFile>
#include <QGridLayout>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QTextBrowser>
#include <QTextStream>
#include <QVariant>

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent) {

    setMinimumWidth(550);
    setMaximumHeight(450);
    setWindowTitle(tr("About"));
    // Note: setWindowIcon doesn't use QAction, so we keep the direct approach
    setWindowIcon(Appearance::adjustIconForDarkMode(":/run_environment/graphics/icon.png"));
    QGridLayout* layout = new QGridLayout(this);

    QLabel* icon = new QLabel();
    QPixmap iconPixmap = Appearance::adjustIconForDarkMode(QPixmap(":/run_environment/graphics/midieditor.png"), "midieditor");
    icon->setPixmap(iconPixmap.scaledToWidth(80, Qt::SmoothTransformation));
    icon->setFixedSize(80, 80);
    layout->addWidget(icon, 0, 0, 3, 1);

    QLabel* title = new QLabel("<h1>" + QApplication::applicationName() + "</h1>", this);
    layout->addWidget(title, 0, 1, 1, 2);
    if (Appearance::shouldUseDarkMode()) {
        title->setStyleSheet("color: white");
    } else {
        title->setStyleSheet("color: black");
    }

    QLabel* version = new QLabel("Version: " + QApplication::applicationVersion() + " (" + QApplication::instance()->property("arch").toString() + "-Bit" + ")", this);
    layout->addWidget(version, 1, 1, 1, 2);
    if (Appearance::shouldUseDarkMode()) {
        version->setStyleSheet("color: #cccccc");
    } else {
        version->setStyleSheet("color: black");
    }

    QScrollArea* a = new QScrollArea(this);
    QString contributors = "<p>";
    QString delim = "";
    foreach (QString contributor, *loadContributors()) {
        contributors = contributors + delim + contributor;
        delim = "<br/>";
    }
    contributors = contributors + "</p>";

    QLabel* content = new QLabel("<html>"
                                 "<body>"
                                 "<h3>Maintained with ♡</h3>"
                                 "<p>"
                                 "Meowchestra - <a href=\"https://ko-fi.com/meowchestra\">ko-fi.com/meowchestra</a> | github.com/Meowchestra<br>"
                                 "GitHub: <a href=\"https://github.com/Meowchestra/MidiEditor\">github.com/Meowchestra/MidiEditor</a><br>"
                                 "</p>"
                                 "<h3>Based on MidiEditor by</h3>"
                                 "<p>"
                                 "Markus Schwenk - github.com/markusschwenk<br>"
                                 "Website: <a href=\"https://midieditor.org/\">midieditor.org</a><br>"
                                 "Email: support@midieditor.org | kontakt@markus-schwenk.de<br>"
                                 "</p>"
                                 "<h3>Contributors</h3>"
                                 + contributors +
                                 "<h3>Credits</h3>"
                                 "<p>"
                                 "3D icons by Double-J Design (http://www.doublejdesign.co.uk)<br>"
                                 "Flat icons designed by Freepik<br>"
                                 "Metronome sound by Mike Koenig<br>"
                                 "</p>"
                                 "<h3>Third party Libraries</h3>"
                                 "<p>"
                                 "RtMidi (Copyright (c) 2003-2014 Gary P. Scavone)"
                                 "</p>"
                                 "</body>"
                                 "</html>");
    a->setWidgetResizable(true);
    a->setWidget(content);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    layout->addWidget(a, 2, 1, 2, 2);

    if (Appearance::shouldUseDarkMode()) {
        content->setStyleSheet("color: white; background-color: #404040; padding: 5px");
        a->setStyleSheet("background-color: #404040");
    } else {
        content->setStyleSheet("color: black; background-color: white; padding: 5px");
        a->setStyleSheet("background-color: white");
    }

    // Ensure the scroll area uses the application style
    a->setStyle(QApplication::style());

    content->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    content->setOpenExternalLinks(true);

    layout->setRowStretch(3, 1);
    layout->setColumnStretch(1, 1);

    QFrame* f = new QFrame(this);
    f->setFrameStyle(QFrame::HLine | QFrame::Sunken);
    layout->addWidget(f, 4, 0, 1, 3);

    QPushButton* close = new QPushButton("Close");
    layout->addWidget(close, 5, 2, 1, 1);
    connect(close, SIGNAL(clicked()), this, SLOT(hide()));
}

QList<QString>* AboutDialog::loadContributors() {

    QList<QString>* list = new QList<QString>();

    QFile file(":/CONTRIBUTORS");
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return list;

    QTextStream in(&file);
    while (!in.atEnd()) {
        list->append(in.readLine());
    }

    return list;
}
