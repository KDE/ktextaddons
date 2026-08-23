/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "whatsnewngutilstest.h"
#include "whatsnewng/whatsnewngutils.h"
#include <KAboutData>
#include <QTest>

void initLocale()
{
#ifndef Q_OS_WIN
    qputenv("LC_ALL", "en_US.utf-8");
#else
    QLocale::setDefault(QLocale(u"en_US"_s));
#endif
}

Q_CONSTRUCTOR_FUNCTION(initLocale)

QTEST_GUILESS_MAIN(WhatsNewNgUtilsTest)
using namespace Qt::Literals::StringLiterals;
WhatsNewNgUtilsTest::WhatsNewNgUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void WhatsNewNgUtilsTest::shouldHaveDefaultValues()
{
    QCOMPARE(TextAddonsWidgets::WhatsNewNgUtils::allVersion(), -1);
}

void WhatsNewNgUtilsTest::shouldGenerateCreateMD5()
{
    {
        const QString foo = u"kde"_s;
        QCOMPARE(TextAddonsWidgets::WhatsNewNgUtils::createMD5(foo), u"GGzyi3byJk6f6o/PkctPXQ=="_s);
    }
    {
        const QString foo = u"été?"_s;
        QCOMPARE(TextAddonsWidgets::WhatsNewNgUtils::createMD5(foo), u"2Io+1R/a7zqqckvcwqVl1A=="_s);
    }
    {
        const QString foo = u"ete?"_s;
        QCOMPARE(TextAddonsWidgets::WhatsNewNgUtils::createMD5(foo), u"eCXMrP5HOSHKOMYmiUofrw=="_s);
    }
}

void WhatsNewNgUtilsTest::shouldGenerateChangelog()
{
    const QString appxmlfile = QLatin1StringView(TEXTADDONSWIDGETS_DATA_DIR) + "/org.kde.coreaddons.test-app.xml"_L1;
    auto aboutData = KAboutData::fromAppStreamFile(appxmlfile);
    const auto releases = aboutData.releases();
    QVERIFY(!releases.isEmpty());
    QCOMPARE(releases.count(), 2);
    QCOMPARE(
        TextAddonsWidgets::WhatsNewNgUtils::generateChangelog(releases, TextAddonsWidgets::WhatsNewNgUtils::allVersion()),
        u"<qt><h1>What's New History</h1><h3><i>What's New in Version 25.12.1 (Released: 1/8/26)</i></h3><ul><li>Patch release change 1.</li><li>Patch release change 2 &amp; 3.</li></ul><h3><i>What's New in Version 25.12.0 (Released: 12/11/25)</i></h3><p>&quot;Cool&quot; (untranslated) Features:</p><ul><li><em>Important</em> untranslated feature release change 1.</li><li>Not so <em>important</em> untranslated feature release change 2.</li><li>Feature release change 3.</li></ul><b><i><a href=\"https://kde.org/announcements/gear/25.12.0/\">Release Note</a></i></b></qt>"_s);

    QCOMPARE(
        TextAddonsWidgets::WhatsNewNgUtils::generateChangelog(releases, 0),
        u"<h3><i>What's New in Version 25.12.1 (Released: 1/8/26)</i></h3><ul><li>Patch release change 1.</li><li>Patch release change 2 &amp; 3.</li></ul>"_s);

    QCOMPARE(
        TextAddonsWidgets::WhatsNewNgUtils::generateChangelog(releases, 1),
        u"<h3><i>What's New in Version 25.12.0 (Released: 12/11/25)</i></h3><p>&quot;Cool&quot; (untranslated) Features:</p><ul><li><em>Important</em> untranslated feature release change 1.</li><li>Not so <em>important</em> untranslated feature release change 2.</li><li>Feature release change 3.</li></ul><b><i><a href=\"https://kde.org/announcements/gear/25.12.0/\">Release Note</a></i></b>"_s);
}
#include "moc_whatsnewngutilstest.cpp"
