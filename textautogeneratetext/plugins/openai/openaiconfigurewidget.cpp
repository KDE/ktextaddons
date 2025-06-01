/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openaiconfigurewidget.h"
#include <KAuthorized>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KPasswordLineEdit>
#include <QFormLayout>

OpenAIConfigureWidget::OpenAIConfigureWidget(QWidget *parent)
    : TextAutoGenerateText::NetworkConfigureWidget{parent}
{
}

OpenAIConfigureWidget::~OpenAIConfigureWidget() = default;

#include "moc_openaiconfigurewidget.cpp"
