/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpservertest.h"
#include "core/textautogeneratetextmcpserver.h"
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextMcpServerTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextMcpServerTest::TextAutoGenerateTextMcpServerTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateTextMcpServerTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextMcpServer w;
    QVERIFY(w.serverUrl().isEmpty());
    QVERIFY(w.enabled());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.identifier().isEmpty());
    QVERIFY(!w.isValid());
}

void TextAutoGenerateTextMcpServerTest::shouldVerifyValidValue()
{
    TextAutoGenerateText::TextAutoGenerateTextMcpServer w;
    QVERIFY(!w.isValid());

    w.setName(u"foo"_s);
    QVERIFY(!w.isValid());

    w.setIdentifier("bla"_ba);
    QVERIFY(!w.isValid());

    w.setServerUrl(QUrl(u"bla"_s));
    QVERIFY(w.isValid());
}

#include "moc_textautogeneratetextmcpservertest.cpp"
