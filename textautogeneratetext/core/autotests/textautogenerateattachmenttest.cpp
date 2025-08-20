/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateattachmenttest.h"
#include "core/textautogenerateattachment.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateAttachmentTest)

TextAutoGenerateAttachmentTest::TextAutoGenerateAttachmentTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAttachmentTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateAttachment att;
    QVERIFY(att.base64().isEmpty());
    QVERIFY(att.mimeType().isEmpty());
    QCOMPARE(att.attachmentType(), TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Unknown);
    QVERIFY(!att.isValid());
}

#include "moc_textautogenerateattachmenttest.cpp"
