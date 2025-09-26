/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "emoticonwidgetactionwidgetgui.h"
#include <qapplication.h>

EmoticonWidgetActionWidgetGui::EmoticonWidgetActionWidgetGui(QWidget *parent)
    : QWidget{parent}
{
}

EmoticonWidgetActionWidgetGui::~EmoticonWidgetActionWidgetGui() = default;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EmoticonWidgetActionWidgetGui window;

    window.show();
    return app.exec();
}
