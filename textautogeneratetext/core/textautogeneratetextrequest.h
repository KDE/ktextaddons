/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QJsonArray>
class QDebug;
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateTextRequest class
 * @author Laurent Montel <montel@kde.org>
 */
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

    [[nodiscard]] QList<QByteArray> tools() const;
    void setTools(const QList<QByteArray> &newTools);

private:
    QList<QByteArray> mTools;
    QJsonArray mMessages;
    QString mMessage;
    QString mModel;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextRequest &t);
