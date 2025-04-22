/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
namespace TextAutogenerateText
{
class TextAutoGenerateChatModel;
/**
 * @brief The TextAutogenerateManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateManager(QObject *parent = nullptr);
    ~TextAutogenerateManager() override;

    static TextAutogenerateManager *self();

    void ask(const QString &msg);

    [[nodiscard]] TextAutoGenerateChatModel *textAutoGenerateChatModel() const;

    virtual void loadHistory();
    virtual void saveHistory();

Q_SIGNALS:
    void sendMessageRequested(const QString &str);

private:
    TextAutoGenerateChatModel *const mTextAutoGenerateChatModel;
};
}
