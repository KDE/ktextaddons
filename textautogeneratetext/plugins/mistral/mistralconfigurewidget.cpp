/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralconfigurewidget.h"
#include <KAuthorized>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <KPasswordLineEdit>
#include <QFormLayout>

MistralConfigureWidget::MistralConfigureWidget(QWidget *parent)
    : TextAutoGenerateText::NetworkPluginConfigureWidget{parent}
{
}

MistralConfigureWidget::~MistralConfigureWidget() = default;

#include "moc_mistralconfigurewidget.cpp"
