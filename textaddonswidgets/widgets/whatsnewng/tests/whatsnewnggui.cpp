/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "whatsnewnggui.h"
#include <QApplication>
#include <QStandardPaths>

WhatsNewNgGui::WhatsNewNgGui(QWidget *parent)
    : QWidget{parent}
{
}

WhatsNewNgGui::~WhatsNewNgGui() = default;

int main(int argc, char *argv[])
{
    const QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);

    WhatsNewNgGui w;
    w.show();
    return app.exec();
}

#include "moc_whatsnewnggui.cpp"
