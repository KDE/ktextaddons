/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextcore_private_export.h"
#include <QString>

namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT TextAutoGenerateFileCache
{
public:
    TextAutoGenerateFileCache();
    ~TextAutoGenerateFileCache();
    [[nodiscard]] static QString cacheFilePath(const QByteArray &attachmentId);
};
}
