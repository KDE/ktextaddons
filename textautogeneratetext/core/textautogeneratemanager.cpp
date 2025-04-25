/*
SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanager.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogenerateengineutil.h"

#include <KConfigGroup>
#include <QRegularExpression>

using namespace TextAutogenerateText;
TextAutogenerateManager::TextAutogenerateManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateChatModel(new TextAutoGenerateChatModel(this))
{
    loadHistory();
}

TextAutogenerateManager::~TextAutogenerateManager()
{
    saveHistory();
    qDebug() << " XCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
}

TextAutogenerateManager *TextAutogenerateManager::self()
{
    static TextAutogenerateManager s_self;
    return &s_self;
}

void TextAutogenerateManager::ask(const QString &msg)
{
    Q_EMIT sendMessageRequested(msg);
}

TextAutoGenerateChatModel *TextAutogenerateManager::textAutoGenerateChatModel() const
{
    return mTextAutoGenerateChatModel;
}

void TextAutogenerateManager::loadHistory()
{
    QList<TextAutoGenerateMessage> messages;
    KSharedConfig::Ptr config;
    const QStringList keyGroups = keyRecorderList(config);

    for (const QString &groupName : keyGroups) {
        KConfigGroup group = config->group(groupName);
        TextAutoGenerateMessage message;

        message.setContent(group.readEntry(QStringLiteral("Content")));
        message.setSender(static_cast<TextAutoGenerateMessage::Sender>(group.readEntry(QStringLiteral("Sender")),
                                                                       static_cast<TextAutoGenerateMessage::Sender>(TextAutoGenerateMessage::Sender::Unknown)));
        message.setDateTime(group.readEntry(QStringLiteral("DateTime"), 0));
        message.setUuid(group.readEntry(QStringLiteral("Uuid"), QByteArray()));
        message.setAnswerUuid(group.readEntry(QStringLiteral("AnswerUuid"), QByteArray()));
        message.setTopic(group.readEntry(QStringLiteral("Topic"), QString()));

        messages.append(std::move(message));
    }
    mTextAutoGenerateChatModel->setMessages(messages);
}

void TextAutogenerateManager::saveHistory()
{
    const QList<TextAutoGenerateMessage> messages = mTextAutoGenerateChatModel->messages();
    KSharedConfig::Ptr config;
    const QStringList filterGroups = keyRecorderList(config);

    for (const QString &group : filterGroups) {
        config->deleteGroup(group);
    }
    for (int i = 0, total = messages.count(); i < total; ++i) {
        const QString groupName = QStringLiteral("DKIM Key Record #%1").arg(i);
        KConfigGroup group = config->group(groupName);
        const TextAutoGenerateMessage &info = messages.at(i);
        group.writeEntry(QStringLiteral("Content"), info.content());
        group.writeEntry(QStringLiteral("Sender"), static_cast<int>(info.sender()));
        group.writeEntry(QStringLiteral("DateTime"), info.dateTime());
        group.writeEntry(QStringLiteral("Uuid"), info.uuid());
        group.writeEntry(QStringLiteral("AnswerUuid"), info.answerUuid());
        group.writeEntry(QStringLiteral("Topic"), info.topic());
    }
}

QStringList TextAutogenerateManager::keyRecorderList(KSharedConfig::Ptr &config) const
{
    config = KSharedConfig::openConfig(TextAutogenerateEngineUtil::defaultConfigFileName(), KConfig::NoGlobals);
    const QStringList keyGroups = config->groupList().filter(QRegularExpression(QStringLiteral("AutoGenerate #\\d+")));
    return keyGroups;
}

#include "moc_textautogeneratemanager.cpp"
