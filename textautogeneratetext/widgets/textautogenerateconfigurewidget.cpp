/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateconfigurewidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>

using namespace TextAutogenerateText;
TextAutogenerateConfigureWidget::TextAutogenerateConfigureWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
}

TextAutogenerateConfigureWidget::~TextAutogenerateConfigureWidget() = default;
