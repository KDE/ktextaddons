/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "converttexttest.h"
using namespace Qt::Literals::StringLiterals;

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
        const QString str(u"foo"_s);
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), u"foo"_s);
    }
    {
        const QString str(u"numérique"_s);
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), u"numerique"_s);
    }
    {
        const QString str(u"téléphone"_s);
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), u"telephone"_s);
    }
    {
        const QString str(u"noël"_s);
        QCOMPARE(TextUtils::ConvertText::normalize(QStringView(str)), u"noel"_s);
    }
}

void ConvertTextTest::testUpperCase_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("result");
    QTest::addColumn<int>("startcursorposition");
    QTest::addColumn<int>("endcursorposition");
    QTest::newRow("onelinewithoutselection") << u"foo"_s << u"foo"_s << -1 << -1;
    QTest::newRow("onelinewithselection") << u"foo"_s << u"FOO"_s << 0 << 3;
    QTest::newRow("onelinewithselectionuppercase") << u"FOO"_s << u"FOO"_s << 0 << 3;
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
    QTest::newRow("onelinewithoutselection") << u"foo"_s << u"foo"_s << -1 << -1;
    QTest::newRow("onelinewithselection") << u"foo"_s << u"foo"_s << 0 << 3;
    QTest::newRow("onelinewithselectionuppercase") << u"FOO"_s << u"foo"_s << 0 << 3;
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
    QTest::newRow("onelinewithoutselection") << u"foo"_s << u"foo"_s << -1 << -1;
    QTest::newRow("onelinewithselection") << u"foo"_s << u"Foo"_s << 0 << 3;
    QTest::newRow("bigline") << u"foo bla foo.\nddd"_s << u"Foo bla foo.\nDdd"_s << 0 << 16;
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
    QTest::newRow("onelinewithoutselection") << u"foo"_s << u"foo"_s << -1 << -1;
    QTest::newRow("onelinewithselection") << u"foo"_s << u"FOO"_s << 0 << 3;
    QTest::newRow("reverseCase") << u"fOo bla\tfOO"_s << u"FoO BLA\tFoo"_s << 0 << 12;
    QTest::newRow("notallineselected") << u"fOo bla\tfOO"_s << u"FoO bla\tfOO"_s << 0 << 3;
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
