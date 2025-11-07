/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateattachmentutilstest.h"
#include "core/textautogenerateattachmentutils.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateAttachmentUtilsTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAttachmentUtilsTest::TextAutoGenerateAttachmentUtilsTest(QObject *parent)
    : QObject{parent}
{
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
    QTest::newRow("image1") << QByteArray("image/png") << TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Image;
    QTest::newRow("audio1") << QByteArray("audio/png") << TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Audio;
    QTest::newRow("video1") << QByteArray("video/png") << TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Video;
}

#include "moc_textautogenerateattachmentutilstest.cpp"
