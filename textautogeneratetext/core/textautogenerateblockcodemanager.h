/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QMap>
#include <QString>
namespace TextAutoGenerateText
{
class TextAutoGenerateBlockCodeManager
{
public:
    static TextAutoGenerateBlockCodeManager *self();
    void insert(const QString &identifier, const QString &blockCode);
    [[nodiscard]] QString blockCode(const QString &identifier) const;

private:
    QMap<QString, QString> mCacheBlockCode;
};
}
