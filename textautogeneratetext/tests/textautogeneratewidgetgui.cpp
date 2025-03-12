/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratewidgetgui.h"
#include <QHBoxLayout>
#include <QPushButton>

TextAutoGenerateWidgetGui::TextAutoGenerateWidgetGui(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins({});
}

TextAutoGenerateWidgetGui::~TextAutoGenerateWidgetGui() = default;

#include "moc_textautogeneratewidgetgui.cpp"
