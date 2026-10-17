/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverconfigurewidget.h"
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
McpProtocolServerConfigureWidget::McpProtocolServerConfigureWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    // TODO configure it.
}

McpProtocolServerConfigureWidget::~McpProtocolServerConfigureWidget() = default;

#include "moc_mcpprotocolserverconfigurewidget.cpp"
