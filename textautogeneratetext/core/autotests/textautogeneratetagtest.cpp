/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetagtest.h"
#include "core/tags/textautogeneratetag.h"
#include <QColor>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTagTest)

TextAutoGenerateTagTest::TextAutoGenerateTagTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTagTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTag tag;
    QVERIFY(!tag.identifier().isEmpty());
    QVERIFY(tag.name().isEmpty());
    QVERIFY(!tag.color().isValid());
}

#include "moc_textautogeneratetagtest.cpp"
