/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetoolpluginconfigurewidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
TextAutoGenerateToolPluginConfigureWidget::TextAutoGenerateToolPluginConfigureWidget(QWidget *parent)
    : QWidget{parent}
{
}

TextAutoGenerateToolPluginConfigureWidget::~TextAutoGenerateToolPluginConfigureWidget() = default;

#include "moc_textautogeneratetoolpluginconfigurewidget.cpp"
