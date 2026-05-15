/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextreplyinfotest.h"
#include <QTest>
#include <TextAutoGenerateText/TextAutoGenerateTextReplyInfo>
QTEST_GUILESS_MAIN(TextAutoGenerateTextReplyInfoTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextReplyInfoTest::TextAutoGenerateTextReplyInfoTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextReplyInfoTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextReplyInfo info;
    QCOMPARE(info.completionTokens, 0);
    QCOMPARE(info.promptTokens, 0);
    QCOMPARE(info.promptEvalTokenCount, 0);
    QCOMPARE(info.tokenCount, 0);
    QVERIFY(!info.isValid());
    // TODO
}

void TextAutoGenerateTextReplyInfoTest::shouldConvertReplyTypeToString()
{
    QCOMPARE(
        TextAutoGenerateText::TextAutoGenerateTextReplyInfo::convertReplyTypeToString(TextAutoGenerateText::TextAutoGenerateTextReplyInfo::ReplyType::Unknown),
        QString{});
    QCOMPARE(
        TextAutoGenerateText::TextAutoGenerateTextReplyInfo::convertReplyTypeToString(TextAutoGenerateText::TextAutoGenerateTextReplyInfo::ReplyType::Ollama),
        u"ollama"_s);
    QCOMPARE(
        TextAutoGenerateText::TextAutoGenerateTextReplyInfo::convertReplyTypeToString(TextAutoGenerateText::TextAutoGenerateTextReplyInfo::ReplyType::OpenAI),
        u"openai"_s);
}

void TextAutoGenerateTextReplyInfoTest::shouldConvertReplyTypeFromString()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextReplyInfo::convertReplyTypeFromString(u"ollama"_s),
             TextAutoGenerateText::TextAutoGenerateTextReplyInfo::ReplyType::Ollama);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextReplyInfo::convertReplyTypeFromString(u"openai"_s),
             TextAutoGenerateText::TextAutoGenerateTextReplyInfo::ReplyType::OpenAI);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextReplyInfo::convertReplyTypeFromString(u"kde"_s),
             TextAutoGenerateText::TextAutoGenerateTextReplyInfo::ReplyType::Unknown);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextReplyInfo::convertReplyTypeFromString(QString()),
             TextAutoGenerateText::TextAutoGenerateTextReplyInfo::ReplyType::Unknown);
}

#include "moc_textautogeneratetextreplyinfotest.cpp"
