/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "whatsnewngutils.h"
#include <KAboutData>
#include <KLocalizedString>
#include <QCryptographicHash>
#include <QDate>

QString TextAddonsWidgets::WhatsNewNgUtils::createMD5(const QString &str)
{
    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(str.toUtf8());
    return QLatin1StringView(md5.result().toBase64());
}

QString TextAddonsWidgets::WhatsNewNgUtils::generateUrl(const KAboutRelease &release)
{
    if (release.url().isValid()) {
        return i18n("<b><i><a href=\"%1\">Release Note</a></i></b>", release.url().toString());
    }
    return {};
}

QString TextAddonsWidgets::WhatsNewNgUtils::generateVersionHeader(const KAboutRelease &release)
{
    if (const QDate date = release.date(); date.isValid()) {
        return i18n("<h3><i>What's New in Version %1 (Released: %2)</i></h3>", release.version(), QLocale().toString(date, QLocale::ShortFormat));
    } else {
        return i18n("<h3><i>What's New in Version %1 (Unreleased)</i></h3>", release.version());
    }
}

QString TextAddonsWidgets::WhatsNewNgUtils::generateStartEndHtml(const QString &str)
{
    const QString message = QStringLiteral("<qt>") + str + QStringLiteral("</qt>");
    return message;
}

QString TextAddonsWidgets::WhatsNewNgUtils::generateChangelog(const QList<KAboutRelease> &releases, int type)
{
    if (releases.isEmpty()) {
        return {};
    }
    if (type == TextAddonsWidgets::WhatsNewNgUtils::allVersion()) { // All
        QString message;
        message += i18n("<h1>What's New History</h1>");
        for (int i = 0, total = releases.count(); i < total; ++i) {
            const auto &info = releases.at(i);
            message += generateVersionHeader(info);
            message += info.description();
            message += generateUrl(info);
        }
        return generateStartEndHtml(message);
    } else if (type >= 0 && type < releases.count()) {
        const auto &info = releases.at(type);
        const QString message = generateVersionHeader(info) + info.description() + generateUrl(info);
        return generateStartEndHtml(message);
    }
    return {};
}

int TextAddonsWidgets::WhatsNewNgUtils::allVersion()
{
    return -1;
}
