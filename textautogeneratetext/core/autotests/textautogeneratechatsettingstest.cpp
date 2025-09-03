/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsettingstest.h"
#include "core/textautogeneratechatsettings.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateChatSettingsTest)
TextAutoGenerateChatSettingsTest::TextAutoGenerateChatSettingsTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateChatSettingsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info;
    QVERIFY(info.text.isEmpty());
    QCOMPARE(info.scrollbarPosition, -1);
    QVERIFY(!info.isValid());

    const TextAutoGenerateText::TextAutoGenerateChatSettings settings;
    QVERIFY(settings.isEmpty());
}

void TextAutoGenerateChatSettingsTest::shouldAddInfos()
{
    TextAutoGenerateText::TextAutoGenerateChatSettings settings;
    {
        const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info{.text = u"blo"_s, .scrollbarPosition = 2};
        settings.add("foo1"_ba, info);
    }
    QCOMPARE(settings.count(), 1);
    {
        const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info{.text = u"blo"_s, .scrollbarPosition = 2};
        settings.add("foo2"_ba, info);
    }
    QCOMPARE(settings.count(), 2);
    // Change element
    {
        const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info{.text = u"blo2"_s, .scrollbarPosition = 2};
        settings.add("foo2"_ba, info);
    }
    QCOMPARE(settings.count(), 2);
}

#include "moc_textautogeneratechatsettingstest.cpp"
