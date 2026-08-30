/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateattachmentutilstest.h"
#include "core/textautogenerateattachmentutils.h"
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateAttachmentUtilsTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAttachmentUtilsTest::TextAutoGenerateAttachmentUtilsTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateAttachmentUtilsTest::shouldGenerateAttachmentType()
{
    QFETCH(QByteArray, mimetype);
    QFETCH(TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType, attachmentType);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateAttachmentUtils::generateAttachmentType(mimetype), attachmentType);
}

void TextAutoGenerateAttachmentUtilsTest::shouldGenerateAttachmentType_data()
{
    QTest::addColumn<QByteArray>("mimetype");
    QTest::addColumn<TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType>("attachmentType");
    QTest::newRow("unknown") << QByteArray() << TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Unknown;
    QTest::newRow("image1") << "image/png"_ba << TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Image;
    QTest::newRow("audio1") << "audio/png"_ba << TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Audio;
    QTest::newRow("video1") << "video/png"_ba << TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Video;
}

void TextAutoGenerateAttachmentUtilsTest::shouldHaveAttachmentElementInfoDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo w;
    QVERIFY(!w.isValid());
    QCOMPARE(w.attachmentType, TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Unknown);
    QVERIFY(w.mimeType.isEmpty());
    QVERIFY(w.content.isEmpty());
}

void TextAutoGenerateAttachmentUtilsTest::shouldGenerateAttachmentFromAttachmentElementInfo()
{
    {
        // Empty
        const TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo info;
        const TextAutoGenerateText::TextAutoGenerateAttachment att =
            TextAutoGenerateText::TextAutoGenerateAttachmentUtils::generateAttachmentFromAttachmentElementInfo(info);
        QVERIFY(!info.isValid());
        QVERIFY(att.mimeType().isEmpty());
        QVERIFY(att.name().isEmpty());
        QVERIFY(att.content().isEmpty());
        QCOMPARE(att.attachmentType(), TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Unknown);
    }
    {
        // Invalid
        TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo info;
        info.content = "foo"_ba;
        info.mimeType = "bla/bla"_ba;
        info.name = u"kde"_s;
        const TextAutoGenerateText::TextAutoGenerateAttachment att =
            TextAutoGenerateText::TextAutoGenerateAttachmentUtils::generateAttachmentFromAttachmentElementInfo(info);
        QVERIFY(!info.isValid());
        QVERIFY(att.mimeType().isEmpty());
        QVERIFY(att.name().isEmpty());
        QVERIFY(att.content().isEmpty());
        QCOMPARE(att.attachmentType(), TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Unknown);
    }
    {
        // Valid
        TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo info;
        info.content = "foo"_ba;
        info.mimeType = "bla/bla"_ba;
        info.name = u"kde"_s;
        info.attachmentType = TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Audio;
        const TextAutoGenerateText::TextAutoGenerateAttachment att =
            TextAutoGenerateText::TextAutoGenerateAttachmentUtils::generateAttachmentFromAttachmentElementInfo(info);
        QVERIFY(info.isValid());
        QCOMPARE(att.mimeType(), info.mimeType);
        QCOMPARE(att.name(), info.name);
        QCOMPARE(att.content(), info.content);
        QCOMPARE(att.attachmentType(), TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Audio);
    }
}

#include "moc_textautogenerateattachmentutilstest.cpp"
