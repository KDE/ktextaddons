/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratereplytest.h"
#include "core/textautogeneratereply.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateReplyTest)
using namespace Qt::Literals::StringLiterals;
class CustomTextAutoGenerateReply : public TextAutoGenerateText::TextAutoGenerateReply
{
    Q_OBJECT
public:
    using TextAutoGenerateReply::TextAutoGenerateReply;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply::Response readResponse() const override;

    [[nodiscard]] QList<ToolCallArgumentInfo> testParseToolCalls(const QJsonArray &array) const
    {
        return parseToolCallsOllama(array);
    }

    [[nodiscard]] QList<ToolCallArgumentInfo> testParseToolCallsOpenAI(const QJsonArray &array) const
    {
        return parseToolCallsOpenAI(array);
    }
};

TextAutoGenerateText::TextAutoGenerateReply::Response CustomTextAutoGenerateReply::readResponse() const
{
    return {};
}

TextAutoGenerateReplyTest::TextAutoGenerateReplyTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateReplyTest::shouldHaveDefaultValues()
{
    const CustomTextAutoGenerateReply w(nullptr, TextAutoGenerateText::TextAutoGenerateReply::RequestTypes::ShowModelInfo);
    QCOMPARE(w.requestType(), TextAutoGenerateText::TextAutoGenerateReply::RequestTypes::ShowModelInfo);
}

void TextAutoGenerateReplyTest::shouldParseToolCalls()
{
    QFETCH(QByteArray, toolCallsArray);
    QFETCH(QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo>, result);

    const QJsonDocument doc = QJsonDocument::fromJson(toolCallsArray);
    const QJsonArray array = doc.array();

    const CustomTextAutoGenerateReply w(nullptr, TextAutoGenerateText::TextAutoGenerateReply::RequestTypes::ShowModelInfo);
    QCOMPARE(w.testParseToolCalls(array), result);
}

void TextAutoGenerateReplyTest::shouldParseToolCalls_data()
{
    QTest::addColumn<QByteArray>("toolCallsArray");
    QTest::addColumn<QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo>>("result");
    QTest::addRow("empty") << QByteArray() << QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo>();

    {
        const QByteArray ba(R"([{"function":{"arguments":{"city":"Grenoble"},"name":"example_tool"}}])"_ba);
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> infos;
        TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo i;
        i.toolName = "example_tool"_ba;
        i.index = -1;
        i.toolCallArgument = {{
            .keyTool = u"city"_s,
            .value = u"Grenoble"_s,
        }};
        infos.append(i);
        QTest::addRow("return-1") << ba << infos;
    }
    {
        const QByteArray ba(R"([{"function":{"arguments":{"city":"Grenoble"},"name":"example_tool"},"index":2}])"_ba);
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> infos;
        TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo i;
        i.toolName = "example_tool"_ba;
        i.index = 2;
        i.toolCallArgument = {{
            .keyTool = u"city"_s,
            .value = u"Grenoble"_s,
        }};
        infos.append(i);
        QTest::addRow("return-index") << ba << infos;
    }
    {
        const QByteArray ba(R"([{"function":{"arguments":{"count":3,"enabled":true},"name":"example_tool"},"index":5}])"_ba);
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> infos;
        TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo i;
        i.toolName = "example_tool"_ba;
        i.index = 5;
        i.toolCallArgument = {
            {
                .keyTool = u"count"_s,
                .value = u"3"_s,
            },
            {
                .keyTool = u"enabled"_s,
                .value = u"true"_s,
            },
        };
        infos.append(i);
        QTest::addRow("return-non-string-values") << ba << infos;
    }
}

void TextAutoGenerateReplyTest::shouldParseToolCallsOpenAI()
{
    QFETCH(QByteArray, toolCallsArray);
    QFETCH(QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo>, result);

    const QJsonDocument doc = QJsonDocument::fromJson(toolCallsArray);
    const QJsonArray array = doc.array();

    const CustomTextAutoGenerateReply w(nullptr, TextAutoGenerateText::TextAutoGenerateReply::RequestTypes::ShowModelInfo);
    QCOMPARE(w.testParseToolCallsOpenAI(array), result);
}

void TextAutoGenerateReplyTest::shouldParseToolCallsOpenAI_data()
{
    QTest::addColumn<QByteArray>("toolCallsArray");
    QTest::addColumn<QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo>>("result");
    QTest::addRow("openai-empty") << QByteArray() << QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo>();

    {
        const QByteArray ba(R"([{"function":{"arguments":"{\"currentdatetime\":\"time\"}","name":"current_date_time_tool"},"index":0}])"_ba);
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> infos;
        TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo i;
        i.toolName = "current_date_time_tool"_ba;
        i.index = 0;
        i.toolCallArgument = {{
            .keyTool = u"currentdatetime"_s,
            .value = u"time"_s,
        }};
        infos.append(i);
        QTest::addRow("openai-string-arguments") << ba << infos;
    }

    {
        const QByteArray ba(R"([{"function":{"arguments":{"currentdatetime":"time"},"name":"current_date_time_tool"},"index":1}])"_ba);
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> infos;
        TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo i;
        i.toolName = "current_date_time_tool"_ba;
        i.index = 1;
        i.toolCallArgument = {{
            .keyTool = u"currentdatetime"_s,
            .value = u"time"_s,
        }};
        infos.append(i);
        QTest::addRow("openai-object-arguments") << ba << infos;
    }
    {
        const QByteArray ba(R"([{"function":{"arguments":{"currentdatetime":"time","count":3,"enabled":true},"name":"current_date_time_tool"},"index":2}])"_ba);
        QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> infos;
        TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo i;
        i.toolName = "current_date_time_tool"_ba;
        i.index = 2;
        i.toolCallArgument = {
            {
                .keyTool = u"count"_s,
                .value = u"3"_s,
            },
            {
                .keyTool = u"currentdatetime"_s,
                .value = u"time"_s,
            },
            {
                .keyTool = u"enabled"_s,
                .value = u"true"_s,
            },
        };
        infos.append(i);
        QTest::addRow("openai-object-non-string-values") << ba << infos;
    }
}

#include "moc_textautogeneratereplytest.cpp"
#include "textautogeneratereplytest.moc"
