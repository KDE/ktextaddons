/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <QString>
class KAboutRelease;
namespace TextAddonsWidgets::WhatsNewNgUtils
{
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QString createMD5(const QString &str);
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QString generateUrl(const KAboutRelease &release);
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QString generateVersionHeader(const KAboutRelease &release);
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QString generateStartEndHtml(const QString &str);
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QString generateChangelog(const QList<KAboutRelease> &releases, int type);
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT int allVersion();
}
