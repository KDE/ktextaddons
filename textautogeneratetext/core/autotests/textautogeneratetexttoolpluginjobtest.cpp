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
}

void TextAutoGenerateTextToolPluginJobTest::shouldVerifyRequiredArguments_data()
{
    QTest::addColumn<QStringList>("requiredArguments");
    QTest::addColumn<QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument>>("toolArguments");
    QTest::addColumn<bool>("result");
    {
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> tt;
        QTest::addRow("empty") << QStringList() << tt << false;
    }
    {
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> tt;
        const QStringList lst{u"foo"_s, u"bla"_s};
        QTest::addRow("no tools") << lst << tt << false;
    }
    {
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> tt;
        TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument tool;
        tool.keyTool = u"jrt"_s;
        tool.value = u"result"_s;
        tt.append(tool);

        const QStringList lst{u"foo"_s, u"bla"_s};
        QTest::addRow("no some many tools") << lst << tt << false;
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

        const QStringList lst{u"foo"_s, u"bla"_s};
        QTest::addRow("ok") << lst << tt << true;
    }
}

void TextAutoGenerateTextToolPluginJobTest::shouldVerifyRequiredArguments()
{
    QFETCH(QStringList, requiredArguments);
    QFETCH(QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument>, toolArguments);
    QFETCH(bool, result);
    TextAutoGenerateText::TextAutoGenerateTextToolPluginJob w;
    w.setRequiredArguments(requiredArguments);
    w.setToolArguments(toolArguments);
    QCOMPARE(w.verifyRequiredArguments(), result);
}

#include "moc_textautogeneratetexttoolpluginjobtest.cpp"
