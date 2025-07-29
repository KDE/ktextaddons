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

    [[nodiscard]] QByteArray image() const;
    void setImage(const QByteArray &newImage);

private:
    QByteArray mImage;
};
}
