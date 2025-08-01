/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
#include <QJsonArray>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextRequest
{
    Q_GADGET
public:
    TextAutoGenerateTextRequest();
    ~TextAutoGenerateTextRequest();

    [[nodiscard]] QString message() const;
    void setMessage(const QString &newMessage);

    [[nodiscard]] bool operator==(const TextAutoGenerateTextRequest &other) const;

    [[nodiscard]] QString model() const;
    void setModel(const QString &newModel);

    [[nodiscard]] QJsonArray messages() const;
    void setMessages(const QJsonArray &newMessages);

private:
    QJsonArray mMessages;
    QString mMessage;
    QString mModel;
};
}
QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextRequest &t);
