/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemcpservertoolsdialog.h"
#include "widgets/mcp/textautogeneratemcpservertoolswidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateMcpServerToolsDialog::TextAutoGenerateMcpServerToolsDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateMcpServerToolsWidget(new TextAutoGenerateMcpServerToolsWidget(manager, this))
{
    setWindowTitle(i18nc("@title:window", "Configure Tools"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTextAutoGenerateMcpServerToolsWidget->setObjectName(u"mTextAutoGenerateMcpServerToolsWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateMcpServerToolsWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateMcpServerToolsDialog::accept);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateMcpServerToolsDialog::reject);
}

TextAutoGenerateMcpServerToolsDialog::~TextAutoGenerateMcpServerToolsDialog() = default;

void TextAutoGenerateMcpServerToolsDialog::setServer(const TextAutoGenerateTextMcpProtocolCore::McpServer &server)
{
    setWindowTitle(i18nc("@title:window", "Configure Tools of %1", server.name()));
    mTextAutoGenerateMcpServerToolsWidget->setServer(server);
}

TextAutoGenerateTextMcpProtocolCore::McpServer TextAutoGenerateMcpServerToolsDialog::server() const
{
    return mTextAutoGenerateMcpServerToolsWidget->server();
}

#include "moc_textautogeneratemcpservertoolsdialog.cpp"
