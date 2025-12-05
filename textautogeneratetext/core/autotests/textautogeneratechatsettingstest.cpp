/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsettingstest.h"
#include "core/textautogeneratechatsettings.h"
#include <QJsonObject>
#include <QTest>

using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateChatSettingsTest)
TextAutoGenerateChatSettingsTest::TextAutoGenerateChatSettingsTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateChatSettingsTest::shouldHaveDefaultValues()
{
    {
        const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info;
        QVERIFY(info.text.isEmpty());
        QCOMPARE(info.scrollbarPosition, -1);
        QVERIFY(!info.isValid());
        QVERIFY(!info.hasPendingMessageTyped());
        QVERIFY(info.tools.isEmpty());

        const TextAutoGenerateText::TextAutoGenerateChatSettings settings(nullptr);
        QVERIFY(settings.isEmpty());
    }
    {
        TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo infoIsValid;
        QVERIFY(!infoIsValid.isValid());

        infoIsValid.text = u"bla"_s;
        QVERIFY(infoIsValid.isValid());

        infoIsValid.text.clear();
        QVERIFY(!infoIsValid.isValid());

        infoIsValid.scrollbarPosition = 5;
        QVERIFY(infoIsValid.isValid());

        infoIsValid.scrollbarPosition = -1;
        QVERIFY(!infoIsValid.isValid());

        infoIsValid.tools = QList<QByteArray>() << "foo"_ba;
        QVERIFY(infoIsValid.isValid());
        infoIsValid.tools.clear();
        QVERIFY(!infoIsValid.isValid());
    }
}

void TextAutoGenerateChatSettingsTest::shouldAddInfos()
{
    TextAutoGenerateText::TextAutoGenerateChatSettings settings(nullptr);
    {
        const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info{.text = u"blo"_s, .scrollbarPosition = 2, .tools = {}};
        settings.add("foo1"_ba, info);
    }
    QCOMPARE(settings.count(), 1);
    {
        const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info{.text = u"blo"_s, .scrollbarPosition = 2, .tools = {}};
        settings.add("foo2"_ba, info);
    }
    QCOMPARE(settings.count(), 2);
    // Change element
    {
        const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info{.text = u"blo2"_s, .scrollbarPosition = 2, .tools = {}};
        settings.add("foo2"_ba, info);
    }
    QCOMPARE(settings.count(), 2);
    settings.remove("foo2"_ba);
    QVERIFY(!settings.isEmpty());

    // Unknown
    settings.remove("foo5"_ba);
    QVERIFY(!settings.isEmpty());
    QCOMPARE(settings.count(), 1);

    settings.remove("foo1"_ba);
    QVERIFY(settings.isEmpty());
}

void TextAutoGenerateChatSettingsTest::shouldSerializeDeserialize()
{
    {
        TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info;
        info.scrollbarPosition = 3;
        info.text = u"bla"_s;

        QCOMPARE(TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo::deserialize(
                     TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo::serialize(info)),
                 info);
    }

    {
        TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info;
        info.scrollbarPosition = 3;

        QCOMPARE(TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo::deserialize(
                     TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo::serialize(info)),
                 info);
    }
    {
        TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info;
        QList<QByteArray> tools = {"bla"_ba, "foo"_ba, "zoo"_ba};
        info.tools = tools;

        QCOMPARE(TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo::deserialize(
                     TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo::serialize(info)),
                 info);
    }
}

#include "moc_textautogeneratechatsettingstest.cpp"
