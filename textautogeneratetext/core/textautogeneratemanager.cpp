/*
SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemanager.h"
#include "core/textautogenerateengineutil.h"
#include "core/textautogeneratemessagesmodel.h"

#include <KConfigGroup>
#include <QRegularExpression>

using namespace TextAutoGenerateText;
TextAutoGenerateManager::TextAutoGenerateManager(QObject *parent)
    : QObject{parent}
    , mTextAutoGenerateChatModel(new TextAutoGenerateMessagesModel(this))
{
}

TextAutoGenerateManager::~TextAutoGenerateManager() = default;

TextAutoGenerateManager *TextAutoGenerateManager::self()
{
    static TextAutoGenerateManager s_self;
    return &s_self;
}

void TextAutoGenerateManager::ask(const QString &msg)
{
    Q_EMIT askMessageRequested(msg);
}

TextAutoGenerateMessagesModel *TextAutoGenerateManager::textAutoGenerateChatModel() const
{
    return mTextAutoGenerateChatModel;
}

void TextAutoGenerateManager::filterListMessages(QList<TextAutoGenerateMessage> &messages, bool archived) const
{
    std::sort(messages.begin(), messages.end(), [archived](const TextAutoGenerateMessage &left, const TextAutoGenerateMessage &right) {
        /*
        if (archived) {
            if (!left.archived() || !right.archived()) {
                return false;
            }
        } else {
            if (left.archived() || right.archived()) {
                return false;
            }
        }
        */
        if (left.dateTime() == right.dateTime()) {
            if (left.sender() == TextAutoGenerateMessage::Sender::User) {
                return true;
            }
        }
        return left.dateTime() < right.dateTime();
    });
}

bool TextAutoGenerateManager::showArchived() const
{
    return mShowArchived;
}

void TextAutoGenerateManager::setShowArchived(bool newShowArchived)
{
    mShowArchived = newShowArchived;
}

void TextAutoGenerateManager::loadHistory()
{
    QList<TextAutoGenerateMessage> messages;
    KSharedConfig::Ptr config;
    const QStringList keyGroups = keyRecorderList(config);

    for (const QString &groupName : keyGroups) {
        KConfigGroup group = config->group(groupName);
        TextAutoGenerateMessage message;

        message.setContent(group.readEntry(QStringLiteral("Content")));
        const int sender = group.readEntry(QStringLiteral("Sender"), 0);
        message.setSender(static_cast<TextAutoGenerateMessage::Sender>(sender));
        message.setDateTime(group.readEntry(QStringLiteral("DateTime"), 0));
        message.setUuid(group.readEntry(QStringLiteral("Uuid"), QByteArray()));
        message.setAnswerUuid(group.readEntry(QStringLiteral("AnswerUuid"), QByteArray()));
        message.setTopic(group.readEntry(QStringLiteral("Topic"), QString()));
        message.setArchived(group.readEntry(QStringLiteral("Archived"), false));
        message.setEngineName(group.readEntry(QStringLiteral("EngineName")));
        message.setModelName(group.readEntry(QStringLiteral("ModelName")));

        messages.append(std::move(message));
    }
    filterListMessages(messages, mShowArchived);
    mTextAutoGenerateChatModel->setMessages(messages);
}

void TextAutoGenerateManager::saveHistory()
{
    const QList<TextAutoGenerateMessage> messages = mTextAutoGenerateChatModel->messages();
    KSharedConfig::Ptr config;
    const QStringList filterGroups = keyRecorderList(config);

    for (const QString &group : filterGroups) {
        config->deleteGroup(group);
    }
    for (int i = 0, total = messages.count(); i < total; ++i) {
        const QString groupName = QStringLiteral("AutoGenerate #%1").arg(i);
        KConfigGroup group = config->group(groupName);
        const TextAutoGenerateMessage &info = messages.at(i);
        group.writeEntry(QStringLiteral("Content"), info.content());
        group.writeEntry(QStringLiteral("Sender"), static_cast<int>(info.sender()));
        group.writeEntry(QStringLiteral("DateTime"), info.dateTime());
        group.writeEntry(QStringLiteral("Uuid"), info.uuid());
        group.writeEntry(QStringLiteral("AnswerUuid"), info.answerUuid());
        group.writeEntry(QStringLiteral("Topic"), info.topic());
        group.writeEntry(QStringLiteral("Archived"), info.archived());
        group.writeEntry(QStringLiteral("EngineName"), info.engineName());
        group.writeEntry(QStringLiteral("ModelName"), info.modelName());
    }
    config->sync();
}

QStringList TextAutoGenerateManager::keyRecorderList(KSharedConfig::Ptr &config) const
{
    config = KSharedConfig::openConfig(TextAutoGenerateEngineUtil::defaultConfigFileName(), KConfig::NoGlobals);
    const QStringList keyGroups = config->groupList().filter(QRegularExpression(QStringLiteral("AutoGenerate #\\d+")));
    return keyGroups;
}

#include "moc_textautogeneratemanager.cpp"
