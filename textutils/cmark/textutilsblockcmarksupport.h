/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textutils_export.h"
#include <QString>
namespace TextUtils
{
class TEXTUTILS_EXPORT TextUtilsBlockCMarkSupport
{
public:
    TextUtilsBlockCMarkSupport();
    virtual ~TextUtilsBlockCMarkSupport();
    [[nodiscard]] QString convertMessageText(const QString &str, const QByteArray &uuid, const QString &searchText);

protected:
    [[nodiscard]] virtual QString
    addHighlighter(const QString &str, const QString &language, const QString &searchText, const QByteArray &uuid, int &blockCodeIndex) = 0;
};
}
