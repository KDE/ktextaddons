/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textutils_export.h"
#include <QString>
#include <memory>
class QTemporaryFile;

namespace TextUtils
{
class TEXTUTILS_EXPORT TextUtilsCopyBlockIconCache
{
public:
    static TextUtilsCopyBlockIconCache *self();
    void clear();

    [[nodiscard]] QString copyBlockUrl();

private:
    TEXTUTILS_NO_EXPORT void saveIconToTempFile(const QString &iconName);
    QString mCopyBlockUrl;
    std::unique_ptr<QTemporaryFile> mTemporaryFile;
};
}
