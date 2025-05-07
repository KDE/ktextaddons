/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratemessage.h"
#include "textautogeneratetext_export.h"
#include <QAbstractListModel>
namespace TextAutogenerateText
{
/**
 * @brief The TextAutoGenerateChatModel class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ChatRoles : uint16_t {
        MessageRole = Qt::UserRole + 1,
        SenderRole,
        FinishedRole,
        DateTimeRole,
        DateTimeStrRole,
        UuidRole,
        TopicRole,
        MouseHoverRole,
        ArchivedRole,
        EditingRole,
        SectionRole,
        WaitingAnswerRole,
        ModelInfoRole,
    };

    enum class SectionHistory : uint8_t {
        Today,
        LessThanSevenDays,
        LessThanThirtyDays,
        Later,
        Unknown,
        NSections,
    };

    explicit TextAutoGenerateChatModel(QObject *parent = nullptr);
    ~TextAutoGenerateChatModel() override;

    [[nodiscard]] int rowCount(const QModelIndex & = {}) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    [[nodiscard]] QList<TextAutoGenerateMessage> messages() const;
    void setMessages(const QList<TextAutoGenerateMessage> &newMessages);

    [[nodiscard]] QModelIndex refreshAnswer(const QByteArray &uuid) const;

    void resetConversation();

    void addMessage(const TextAutoGenerateMessage &msg);

    void removeDiscussion(const QByteArray &uuid);

    void replaceContent(const QByteArray &uuid, const QString &content);
    void changeInProgress(const QByteArray &uuid, bool inProgress);
    [[nodiscard]] QByteArray editMessage(const QByteArray &uuid, const QString &str);
    [[nodiscard]] QModelIndex indexForUuid(const QByteArray &uuid) const;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;
    [[nodiscard]] bool cancelRequest(const QModelIndex &index);
    [[nodiscard]] static QString sectionName(TextAutoGenerateChatModel::SectionHistory sectionId);

Q_SIGNALS:
    void conversationCleared();

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT TextAutoGenerateChatModel::SectionHistory section(const TextAutoGenerateMessage &m) const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT bool waitingAnswer(const TextAutoGenerateMessage &message) const;
    QList<TextAutoGenerateMessage> mMessages;
};
}
