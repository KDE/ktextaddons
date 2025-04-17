/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
namespace TextAutogenerateText
{
class TextAutoGenerateHistoryModel;
class TextAutoGenerateChatModel;
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateManager : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateManager(QObject *parent = nullptr);
    ~TextAutogenerateManager() override;

    static TextAutogenerateManager *self();

    [[nodiscard]] TextAutoGenerateChatModel *textAutoGenerateChatModel() const;

    [[nodiscard]] TextAutoGenerateHistoryModel *textAutoGenerateHistoryModel() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadHistory();
    TEXTAUTOGENERATETEXT_NO_EXPORT void saveHistory();
    TextAutoGenerateChatModel *const mTextAutoGenerateChatModel;
    TextAutoGenerateHistoryModel *const mTextAutoGenerateHistoryModel;
};
}
