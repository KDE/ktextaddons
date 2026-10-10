/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateelicitationdialog.h"
#include "widgets/mcp/textautogenerateelicitationwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequest>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateElicitationDialog::TextAutoGenerateElicitationDialog(QWidget *parent)
    : QDialog(parent)
    , mTextAutoGenerateElicitationWidget(new TextAutoGenerateElicitationWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Request from MCP Server"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mTextAutoGenerateElicitationWidget->setObjectName(u"mTextAutoGenerateElicitationWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateElicitationWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->button(QDialogButtonBox::Ok)->setText(i18nc("@action:button", "Accept"));
    button->setObjectName(u"button"_s);
    auto declineButton = new QPushButton(i18nc("@action:button", "Decline"), this);
    declineButton->setObjectName(u"button"_s);
    button->addButton(declineButton, QDialogButtonBox::ActionRole);
    mainLayout->addWidget(button);

    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateElicitationDialog::slotAccepted);
    connect(declineButton, &QPushButton::clicked, this, &TextAutoGenerateElicitationDialog::slotDeclined);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateElicitationDialog::slotRejected);
}

TextAutoGenerateElicitationDialog::~TextAutoGenerateElicitationDialog() = default;

void TextAutoGenerateElicitationDialog::setRequest(const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &request)
{
    mTextAutoGenerateElicitationWidget->setRequest(request);
}

void TextAutoGenerateElicitationDialog::setServerName(const QString &serverName)
{
    setWindowTitle(i18nc("@title:window", "Request from %1", serverName));
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult TextAutoGenerateElicitationDialog::elicitResult() const
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult result;
    result.setAction(mAction);
    // TODO assign content of form when action is Accept
    return result;
}

void TextAutoGenerateElicitationDialog::slotAccepted()
{
    mAction = TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Accept;
    accept();
}

void TextAutoGenerateElicitationDialog::slotDeclined()
{
    mAction = TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Decline;
    accept();
}

void TextAutoGenerateElicitationDialog::slotRejected()
{
    mAction = TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Cancel;
    reject();
}

#include "moc_textautogenerateelicitationdialog.cpp"
