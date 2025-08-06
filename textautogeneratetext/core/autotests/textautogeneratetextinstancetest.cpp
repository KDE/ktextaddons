/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancetest.h"
#include "core/textautogeneratetextinstance.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextInstanceTest)

TextAutoGenerateTextInstanceTest::TextAutoGenerateTextInstanceTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextInstanceTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextInstance w;
    QVERIFY(w.pluginName().isEmpty());
    QVERIFY(w.instanceUuid().isEmpty());
    QVERIFY(w.pluginIdentifier().isEmpty());
    QVERIFY(w.currentModel().isEmpty());
    QVERIFY(!w.isValid());
    QVERIFY(w.enabled());
}

#include "moc_textautogeneratetextinstancetest.cpp"
