/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesamplingdialog.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequest>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
using namespace TextAutoGenerateTextMcpProtocolCore;

namespace
{
template<typename Content>
QString contentBlockText(const Content &content)
{
    if (const auto text = std::get_if<McpProtocolTextContent>(&content)) {
        return text->text();
    }
    if (std::holds_alternative<McpProtocolImageContent>(content)) {
        return i18n("[Image]");
    }
    if (std::holds_alternative<McpProtocolAudioContent>(content)) {
        return i18n("[Audio]");
    }
    if (std::holds_alternative<McpProtocolToolUseContent>(content)) {
        return i18n("[Tool call]");
    }
    if (std::holds_alternative<McpProtocolToolResultContent>(content)) {
        return i18n("[Tool result]");
    }
    return {};
}

QString contentText(const McpProtocolUtils::CreateMessageResultContent &content)
{
    if (const auto blocks = std::get_if<QList<McpProtocolUtils::SamplingMessageContentBlock>>(&content)) {
        QStringList texts;
        for (const auto &block : *blocks) {
            texts.append(contentBlockText(block));
        }
        return texts.join(u'\n');
    }
    return contentBlockText(content);
}
}

TextAutoGenerateSamplingDialog::TextAutoGenerateSamplingDialog(QWidget *parent)
    : QDialog(parent)
    , mLabel(new QLabel(this))
    , mMessages(new QPlainTextEdit(this))
{
    setWindowTitle(i18nc("@title:window", "Sampling Request from MCP Server"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mLabel->setObjectName(u"mLabel"_s);
    mLabel->setWordWrap(true);
    mainLayout->addWidget(mLabel);

    mMessages->setObjectName(u"mMessages"_s);
    mMessages->setReadOnly(true);
    mainLayout->addWidget(mMessages);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(u"button"_s);
    button->button(QDialogButtonBox::Ok)->setText(i18nc("@action:button", "Send to LLM"));
    button->button(QDialogButtonBox::Cancel)->setText(i18nc("@action:button", "Reject"));
    mainLayout->addWidget(button);

    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateSamplingDialog::accept);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateSamplingDialog::reject);
    setServerName({});
}

TextAutoGenerateSamplingDialog::~TextAutoGenerateSamplingDialog() = default;

void TextAutoGenerateSamplingDialog::setServerName(const QString &serverName)
{
    mLabel->setText(
        i18n("The MCP server \"%1\" wants to send the following messages to the LLM. The generated answer will be returned to the server.", serverName));
}

void TextAutoGenerateSamplingDialog::setRequest(const McpProtocolCreateMessageRequest &request)
{
    mMessages->setPlainText(requestText(request));
}

QString TextAutoGenerateSamplingDialog::requestText(const McpProtocolCreateMessageRequest &request)
{
    const McpProtocolCreateMessageRequestParams params = request.params();
    QStringList parts;
    if (const QString systemPrompt = params.systemPrompt().value_or(QString()); !systemPrompt.isEmpty()) {
        parts.append(i18n("System prompt:\n%1", systemPrompt));
    }
    const QList<McpProtocolSamplingMessage> messages = params.messages();
    for (const auto &message : messages) {
        const QString text = contentText(message.content());
        parts.append(message.role() == McpProtocolUtils::Role::Assistant ? i18n("Assistant:\n%1", text) : i18n("User:\n%1", text));
    }
    return parts.join(u"\n\n"_s);
}

#include "moc_textautogeneratesamplingdialog.cpp"
