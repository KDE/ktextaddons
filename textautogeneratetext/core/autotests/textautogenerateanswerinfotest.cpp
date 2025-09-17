/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateanswerinfotest.h"
#include "core/textautogenerateanswerinfo.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateAnswerInfoTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAnswerInfoTest::TextAutoGenerateAnswerInfoTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAnswerInfoTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateAnswerInfo info;
    QVERIFY(info.engineName().isEmpty());
    QVERIFY(info.instanceName().isEmpty());
    QVERIFY(info.modelName().isEmpty());
    QVERIFY(info.tools().isEmpty());
    QVERIFY(!info.isValid());
}

void TextAutoGenerateAnswerInfoTest::shouldSaveLoadAnswerInfo()
{
    {
        TextAutoGenerateText::TextAutoGenerateAnswerInfo info;
        info.setEngineName(u"engine1"_s);
        info.setInstanceName(u"instance2"_s);
        info.setModelName(u"llmana2"_s);
        QJsonObject obj;
        TextAutoGenerateText::TextAutoGenerateAnswerInfo::serialize(info, obj);
        TextAutoGenerateText::TextAutoGenerateAnswerInfo *deserialize = TextAutoGenerateText::TextAutoGenerateAnswerInfo::deserialize(obj);
        QCOMPARE(info, *deserialize);
        delete deserialize;
    }

    // With tools
    {
        TextAutoGenerateText::TextAutoGenerateAnswerInfo info;
        info.setEngineName(u"engine1"_s);
        info.setInstanceName(u"instance2"_s);
        info.setModelName(u"llmana2"_s);
        info.setTools({"boo"_ba, "fla"_ba});
        QJsonObject obj;
        TextAutoGenerateText::TextAutoGenerateAnswerInfo::serialize(info, obj);
        TextAutoGenerateText::TextAutoGenerateAnswerInfo *deserialize = TextAutoGenerateText::TextAutoGenerateAnswerInfo::deserialize(obj);
        QCOMPARE(info, *deserialize);
        delete deserialize;
    }
}

#include "moc_textautogenerateanswerinfotest.cpp"
