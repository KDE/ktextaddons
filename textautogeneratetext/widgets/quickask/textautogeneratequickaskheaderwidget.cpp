/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskheaderwidget.h"
using namespace Qt::Literals::StringLiterals;

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
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mainLayout->addStretch(1);
    auto configureButton = new QToolButton(this);
    configureButton->setAutoRaise(true);
    configureButton->setObjectName(u"configureButton"_s);
    configureButton->setIcon(QIcon::fromTheme(u"settings-configure"_s));
    configureButton->setToolTip(i18nc("@info:tooltip", "Configure…"));
    mainLayout->addWidget(configureButton);
    connect(configureButton, &QToolButton::clicked, this, &TextAutoGenerateQuickAskHeaderWidget::configureRequested);
}

TextAutoGenerateQuickAskHeaderWidget::~TextAutoGenerateQuickAskHeaderWidget() = default;

#include "moc_textautogeneratequickaskheaderwidget.cpp"
