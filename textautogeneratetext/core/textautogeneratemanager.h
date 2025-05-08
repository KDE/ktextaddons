/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <KSharedConfig>
#include <QObject>
#include <TextAutogenerateText/TextAutoGenerateMessage>
namespace TextAutogenerateText
{
class TextAutoGenerateMessagesModel;
/**
 * @brief The TextAutogenerateManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManager(QObject *parent = nullptr);
    ~TextAutoGenerateManager() override;

    static TextAutoGenerateManager *self();

    void ask(const QString &msg);

    [[nodiscard]] TextAutoGenerateMessagesModel *textAutoGenerateChatModel() const;

    virtual void loadHistory();
    virtual void saveHistory();

    [[nodiscard]] bool showArchived() const;
    void setShowArchived(bool newShowArchived);

Q_SIGNALS:
    void sendMessageRequested(const QString &str);
    void askMessageRequested(const QString &str);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QStringList keyRecorderList(KSharedConfig::Ptr &config) const;
    TEXTAUTOGENERATETEXT_NO_EXPORT void filterListMessages(QList<TextAutoGenerateMessage> &messages, bool archived) const;
    TextAutoGenerateMessagesModel *const mTextAutoGenerateChatModel;
    bool mShowArchived = false;
};
}
