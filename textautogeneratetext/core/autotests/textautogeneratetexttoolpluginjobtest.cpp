/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginjobtest.h"
#include "core/tools/textautogeneratetexttoolpluginjob.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateTextToolPluginJobTest)
TextAutoGenerateTextToolPluginJobTest::TextAutoGenerateTextToolPluginJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextToolPluginJobTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextToolPluginJob w;
    QVERIFY(w.toolArguments().isEmpty());
    QVERIFY(w.requiredArguments().isEmpty());
    QVERIFY(!w.canStart());
    QVERIFY(w.messageUuid().isEmpty());
    QVERIFY(w.toolIdentifier().isEmpty());
    QVERIFY(!w.verifyRequiredArguments());
    QVERIFY(w.chatId().isEmpty());
}

void TextAutoGenerateTextToolPluginJobTest::shouldVerifyRequiredArguments_data()
{
    QTest::addColumn<const QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty>>("properties");
    QTest::addColumn<QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument>>("toolArguments");
    QTest::addColumn<bool>("result");
    {
        const QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> properties;
        const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> tt;
        QTest::addRow("empty") << properties << tt << false;
    }
    {
        QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> properties;
        {
            TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty p;
            p.setName(u"foo"_s);
            properties.append(p);
        }
        {
            TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty p;
            p.setName(u"bla"_s);
            properties.append(p);
        }
        const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> tt;
        QTest::addRow("no tools") << properties << tt << false;
    }
    {
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> tt;
        TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument tool;
        tool.keyTool = u"jrt"_s;
        tool.value = u"result"_s;
        tt.append(tool);

        QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> properties;
        {
            TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty p;
            p.setName(u"foo"_s);
            properties.append(p);
        }
        {
            TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty p;
            p.setName(u"bla"_s);
            properties.append(p);
        }

        QTest::addRow("no some many tools") << properties << tt << false;
    }
    {
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> tt;
        {
            TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument tool;
            tool.keyTool = u"foo"_s;
            tool.value = u"result"_s;
            tt.append(tool);
        }
        {
            TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument tool;
            tool.keyTool = u"bla"_s;
            tool.value = u"result1"_s;
            tt.append(tool);
        }
        QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> properties;
        {
            TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty p;
            p.setName(u"foo"_s);
            properties.append(p);
        }
        {
            TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty p;
            p.setName(u"bla"_s);
            properties.append(p);
        }
        QTest::addRow("ok") << properties << tt << true;
    }
}

void TextAutoGenerateTextToolPluginJobTest::shouldVerifyRequiredArguments()
{
    QFETCH(const QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty>, properties);
    QFETCH(QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument>, toolArguments);
    QFETCH(bool, result);
    TextAutoGenerateText::TextAutoGenerateTextToolPluginJob w;
    w.setProperties(properties);
    w.setToolArguments(toolArguments);
    QCOMPARE(w.verifyRequiredArguments(), result);
}

#include "moc_textautogeneratetexttoolpluginjobtest.cpp"
