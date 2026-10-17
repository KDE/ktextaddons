/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverconfiguretokenwidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
McpProtocolServerConfigureTokenWidget::McpProtocolServerConfigureTokenWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto label = new QLabel(i18n("Token:"), this);
    label->setObjectName(u"label"_s);
    mainLayout->addWidget(label);

    auto resultToken = new QLabel(this);
    resultToken->setObjectName(u"resultToken"_s);
    resultToken->setTextInteractionFlags(Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
    mainLayout->addWidget(resultToken);

    auto regenerateTokenButton = new QPushButton(i18nc("@action:button", "Regenerate"), this);
    regenerateTokenButton->setObjectName(u"regenerateTokenButton"_s);
    connect(regenerateTokenButton, &QPushButton::clicked, this, [this]() {
        // TODO
    });
    mainLayout->addWidget(regenerateTokenButton);

    // TODO
}

McpProtocolServerConfigureTokenWidget::~McpProtocolServerConfigureTokenWidget() = default;

#include "moc_mcpprotocolserverconfiguretokenwidget.cpp"
