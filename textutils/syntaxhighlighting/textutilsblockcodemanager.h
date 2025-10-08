/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textutils_export.h"
#include <QMap>
#include <QString>
namespace TextUtils
{
class TEXTUTILS_EXPORT TextUtilsBlockCodeManager
{
public:
    static TextUtilsBlockCodeManager *self();
    void insert(const QString &identifier, const QString &blockCode);
    [[nodiscard]] QString blockCode(const QString &identifier) const;

private:
    QMap<QString, QString> mCacheBlockCode;
};
}
