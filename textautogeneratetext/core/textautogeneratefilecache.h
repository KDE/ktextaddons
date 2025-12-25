/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QString>

namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateFileCache
{
public:
    TextAutoGenerateFileCache();
    ~TextAutoGenerateFileCache();
    [[nodiscard]] QString cacheFilePath(const QByteArray &attachmentId);
};
}
