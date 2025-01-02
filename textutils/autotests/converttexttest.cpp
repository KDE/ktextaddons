/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "converttexttest.h"
#include "converttext.h"
#include <QTest>
#include <QTextDocument>

QTEST_GUILESS_MAIN(ConvertTextTest)
ConvertTextTest::ConvertTextTest(QObject *parent)
    : QObject{parent}
{
}

void ConvertTextTest::shouldHaveDefaultValues()
{
    {
        const QString str(QStringLiteral("foo"));
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), QStringLiteral("foo"));
    }
    {
        const QString str(QStringLiteral("numérique"));
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), QStringLiteral("numerique"));
    }
    {
        const QString str(QStringLiteral("téléphone"));
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), QStringLiteral("telephone"));
    }
    {
        const QString str(QStringLiteral("noël"));
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), QStringLiteral("noel"));
    }
}

void ConvertTextTest::testUpperCase_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("startcursorposition");
    QTest::addColumn<int>("endcursorposition");
    QTest::newRow("onelinewithoutselection") << QStringLiteral("foo") << QStringLiteral("foo") << -1 << -1;
    QTest::newRow("onelinewithselection") << QStringLiteral("foo") << QStringLiteral("FOO") << 0 << 3;
    QTest::newRow("onelinewithselectionuppercase") << QStringLiteral("FOO") << QStringLiteral("FOO") << 0 << 3;
}

void ConvertTextTest::testUpperCase()
{
    QFETCH(QString, input);
    QFETCH(QString, result);
    QFETCH(int, startcursorposition);
    QFETCH(int, endcursorposition);
    auto document = new QTextDocument(this);
    document->setPlainText(input);
    QTextCursor textCursor(document);
    if (startcursorposition != -1 && endcursorposition != -1) {
        textCursor.setPosition(startcursorposition);
        textCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, endcursorposition - startcursorposition);
    }
    TextUtils::ConvertText::upperCase(textCursor);
    QCOMPARE(textCursor.document()->toPlainText(), result);
    delete document;
}

void ConvertTextTest::testLowerCase_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("startcursorposition");
    QTest::addColumn<int>("endcursorposition");
    QTest::newRow("onelinewithoutselection") << QStringLiteral("foo") << QStringLiteral("foo") << -1 << -1;
    QTest::newRow("onelinewithselection") << QStringLiteral("foo") << QStringLiteral("foo") << 0 << 3;
    QTest::newRow("onelinewithselectionuppercase") << QStringLiteral("FOO") << QStringLiteral("foo") << 0 << 3;
}

void ConvertTextTest::testLowerCase()
{
    QFETCH(QString, input);
    QFETCH(QString, result);
    QFETCH(int, startcursorposition);
    QFETCH(int, endcursorposition);
    auto document = new QTextDocument(this);
    document->setPlainText(input);
    QTextCursor textCursor(document);
    if (startcursorposition != -1 && endcursorposition != -1) {
        textCursor.setPosition(startcursorposition);
        textCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, endcursorposition - startcursorposition);
    }
    TextUtils::ConvertText::lowerCase(textCursor);
    QCOMPARE(textCursor.document()->toPlainText(), result);
    delete document;
}

void ConvertTextTest::testSentenceCase_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("startcursorposition");
    QTest::addColumn<int>("endcursorposition");
    QTest::newRow("onelinewithoutselection") << QStringLiteral("foo") << QStringLiteral("foo") << -1 << -1;
    QTest::newRow("onelinewithselection") << QStringLiteral("foo") << QStringLiteral("Foo") << 0 << 3;
    QTest::newRow("bigline") << QStringLiteral("foo bla foo.\nddd") << QStringLiteral("Foo bla foo.\nDdd") << 0 << 16;
}

void ConvertTextTest::testSentenceCase()
{
    QFETCH(QString, input);
    QFETCH(QString, result);
    QFETCH(int, startcursorposition);
    QFETCH(int, endcursorposition);
    auto document = new QTextDocument(this);
    document->setPlainText(input);
    QTextCursor textCursor(document);
    if (startcursorposition != -1 && endcursorposition != -1) {
        textCursor.setPosition(startcursorposition);
        textCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, endcursorposition - startcursorposition);
    }
    TextUtils::ConvertText::sentenceCase(textCursor);
    QCOMPARE(textCursor.document()->toPlainText(), result);
    delete document;
}

void ConvertTextTest::testReverseCase_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("startcursorposition");
    QTest::addColumn<int>("endcursorposition");
    QTest::newRow("onelinewithoutselection") << QStringLiteral("foo") << QStringLiteral("foo") << -1 << -1;
    QTest::newRow("onelinewithselection") << QStringLiteral("foo") << QStringLiteral("FOO") << 0 << 3;
    QTest::newRow("reverseCase") << QStringLiteral("fOo bla\tfOO") << QStringLiteral("FoO BLA\tFoo") << 0 << 12;
    QTest::newRow("notallineselected") << QStringLiteral("fOo bla\tfOO") << QStringLiteral("FoO bla\tfOO") << 0 << 3;
}

void ConvertTextTest::testReverseCase()
{
    QFETCH(QString, input);
    QFETCH(QString, result);
    QFETCH(int, startcursorposition);
    QFETCH(int, endcursorposition);

    auto document = new QTextDocument(this);
    document->setPlainText(input);
    QTextCursor textCursor(document);
    if (startcursorposition != -1 && endcursorposition != -1) {
        textCursor.setPosition(startcursorposition);
        textCursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, endcursorposition - startcursorposition);
    }
    TextUtils::ConvertText::reverseCase(textCursor);
    QCOMPARE(textCursor.document()->toPlainText(), result);
    delete document;
}

#include "moc_converttexttest.cpp"
