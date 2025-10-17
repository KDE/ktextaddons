/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QByteArray>
#include <QObject>
namespace TextAutoGenerateText
{
class TextAutoGenerateMessagesModel;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateSearchMessageSettings : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchMessageSettings(TextAutoGenerateMessagesModel *model, QObject *parent = nullptr);
    ~TextAutoGenerateSearchMessageSettings() override;

    void next();
    void previous();

    [[nodiscard]] QByteArray currentMessageIdentifier() const;
    void setCurrentMessageIdentifier(const QByteArray &newCurrentMessageIdentifier);

    [[nodiscard]] int currentSearchIndex() const;
    void setCurrentSearchIndex(int newCurrentSearchIndex);

    void clear();

    [[nodiscard]] int foundSearchCount() const;
    void setFoundSearchCount(int newFoundSearchCount);

Q_SIGNALS:
    void refreshMessage(const QByteArray &identifier, const QByteArray &previousIdentifier, int index);
    void updateNextPreviousButtons(bool nextEnabled, bool previousEnabled);

private:
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT bool canSearchMessage() const;
    TEXTAUTOGENERATETEXT_NO_EXPORT void lastMessageUuid();
    TextAutoGenerateMessagesModel *const mMessageModel;
    QByteArray mCurrentMessageIdentifier;
    int mCurrentSearchIndex = -1;
    int mFoundSearchCount = -1;
};
}
