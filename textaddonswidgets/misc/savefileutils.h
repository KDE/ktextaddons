/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QString>

class QWidget;
class QUrl;
namespace TextAddonsWidgets
{
namespace SaveFileUtils
{
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QString querySaveFileName(QWidget *parent, const QString &title, const QUrl &fileToSave);
TEXTADDONSWIDGETS_EXPORT void saveFile(QWidget *parent, const QString &filePath, const QString &title);
}
}
