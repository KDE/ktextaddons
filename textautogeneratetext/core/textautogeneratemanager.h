/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <KSharedConfig>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutoGenerateMessagesModel;
class TextAutoGenerateLocalDatabaseManager;
class TextAutoGenerateChatsModel;
/**
 * @brief The TextAutoGenerateManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateManager(QObject *parent = nullptr);
    ~TextAutoGenerateManager() override;

    void ask(const QString &msg);

    [[nodiscard]] TextAutoGenerateMessagesModel *textAutoGenerateMessagesModel() const;

    void loadHistory();

    [[nodiscard]] bool showArchived() const;
    void setShowArchived(bool newShowArchived);

    [[nodiscard]] TextAutoGenerateChatsModel *textAutoGenerateChatsModel() const;
Q_SIGNALS:
    void sendMessageRequested(const QString &str);
    void askMessageRequested(const QString &str);

private:
    TextAutoGenerateMessagesModel *const mTextAutoGenerateMessagesModel;
    TextAutoGenerateChatsModel *const mTextAutoGenerateChatsModel;
    std::unique_ptr<TextAutoGenerateLocalDatabaseManager> mDatabaseManager;
    bool mShowArchived = false;
};
}
