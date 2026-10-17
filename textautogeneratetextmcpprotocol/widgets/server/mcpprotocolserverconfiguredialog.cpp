/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverconfiguredialog.h"
#include "server/mcpprotocolserverconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
McpProtocolServerConfigureDialog::McpProtocolServerConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mMcpProtocolServerConfigureWidget(new McpProtocolServerConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Server Configuration"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mMcpProtocolServerConfigureWidget->setObjectName(u"mMcpProtocolServerConfigureWidget"_s);
    mainLayout->addWidget(mMcpProtocolServerConfigureWidget);
}

McpProtocolServerConfigureDialog::~McpProtocolServerConfigureDialog() = default;

#include "moc_mcpprotocolserverconfiguredialog.cpp"
