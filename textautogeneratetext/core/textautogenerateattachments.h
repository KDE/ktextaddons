/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QList>
#include <QSharedData>
#include <TextAutoGenerateText/TextAutoGenerateAttachment>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAttachments : public QSharedData
{
public:
    TextAutoGenerateAttachments();
    ~TextAutoGenerateAttachments();
    explicit TextAutoGenerateAttachments(const TextAutoGenerateAttachments &other);

    [[nodiscard]] bool isEmpty() const;

private:
    QList<TextAutoGenerateAttachment> mMessageAttachments;
};
}
