/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QList>
#include <QSharedData>
#include <TextAutoGenerateText/TextAutoGenerateAttachment>
class QDebug;
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateAttachments class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAttachments : public QSharedData
{
public:
    TextAutoGenerateAttachments();
    ~TextAutoGenerateAttachments();
    explicit TextAutoGenerateAttachments(const TextAutoGenerateAttachments &other);

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] QList<TextAutoGenerateAttachment> messageAttachments() const;
    void setMessageAttachments(const QList<TextAutoGenerateAttachment> &newMessageAttachments);

    [[nodiscard]] bool operator==(const TextAutoGenerateAttachments &other) const;

    [[nodiscard]] static QJsonArray serialize(const TextAutoGenerateAttachments &attachments);
    [[nodiscard]] static TextAutoGenerateAttachments *deserialize(const QJsonArray &o, const QByteArray &messageId);

private:
    QList<TextAutoGenerateAttachment> mMessageAttachments;
};
}

TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAttachments &t);
