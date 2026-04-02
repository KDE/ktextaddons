/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratefilecache.h"

#include <QDir>
#include <QStandardPaths>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateFileCache::TextAutoGenerateFileCache() = default;

TextAutoGenerateFileCache::~TextAutoGenerateFileCache() = default;

QString TextAutoGenerateFileCache::cacheFilePath(const QByteArray &attachmentId)
{
    if (attachmentId.isEmpty()) {
        return {};
    }
    const QString cachePath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + u"/ai-attachments/"_s;
    QDir().mkpath(cachePath);
    return cachePath + QString::fromLatin1(attachmentId);
}
