/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskheaderwidget.h"
#include "core/textautogeneratemanager.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QToolButton>

using namespace TextAutoGenerateText;
TextAutoGenerateQuickAskHeaderWidget::TextAutoGenerateQuickAskHeaderWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mManager(manager)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mainLayout->addStretch(1);
    auto configureButton = new QToolButton(this);
    configureButton->setObjectName(QStringLiteral("configureButton"));
    configureButton->setIcon(QIcon::fromTheme(QStringLiteral("settings-configure")));
    configureButton->setToolTip(i18nc("@info:tooltip", "Configure…"));
    mainLayout->addWidget(configureButton);
}

TextAutoGenerateQuickAskHeaderWidget::~TextAutoGenerateQuickAskHeaderWidget() = default;

#include "moc_textautogeneratequickaskheaderwidget.cpp"
