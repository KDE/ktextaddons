/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QSharedData>

namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateMessage class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateImage : public QSharedData
{
public:
    TextAutoGenerateImage();
    ~TextAutoGenerateImage();
    explicit TextAutoGenerateImage(const TextAutoGenerateImage &other);

    [[nodiscard]] QByteArray image() const;
    void setImage(const QByteArray &newImage);

    [[nodiscard]] bool operator==(const TextAutoGenerateImage &other) const;

private:
    QByteArray mImage;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateImage &t);
