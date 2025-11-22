/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
#include <QJsonObject>
#include <QMap>
#include <QString>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChatSettings
{
public:
    struct TEXTAUTOGENERATETEXT_EXPORT PendingTypedInfo {
        QString text;
        int scrollbarPosition = -1;
        [[nodiscard]] bool isValid() const;
        [[nodiscard]] bool hasPendingMessageTyped() const;
        [[nodiscard]] static QJsonObject serialize(const PendingTypedInfo &url);
        [[nodiscard]] static PendingTypedInfo deserialize(const QJsonObject &o);
        [[nodiscard]] bool operator==(const PendingTypedInfo &other) const;
    };
    TextAutoGenerateChatSettings();
    ~TextAutoGenerateChatSettings();

    void remove(const QByteArray &chatId);

    void add(const QByteArray &chatId, const PendingTypedInfo &info);

    [[nodiscard]] PendingTypedInfo value(const QByteArray &chatId);

    [[nodiscard]] bool hasPendingMessageTyped(const QByteArray &chatId) const;

    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] int count() const;

private:
    QMap<QByteArray /*ChatId*/, PendingTypedInfo> mPendingTypedTexts;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo &t);
