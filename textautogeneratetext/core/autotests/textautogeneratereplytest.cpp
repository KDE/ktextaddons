/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
        return parseToolCalls(array);
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
    const CustomTextAutoGenerateReply w(nullptr, TextAutoGenerateText::TextAutoGenerateReply::RequestTypes::Show);
    QCOMPARE(w.requestType(), TextAutoGenerateText::TextAutoGenerateReply::RequestTypes::Show);
}

void TextAutoGenerateReplyTest::shouldParseToolCalls()
{
    QFETCH(QByteArray, toolCallsArray);
    QFETCH(QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo>, result);

    const QJsonDocument doc = QJsonDocument::fromJson(toolCallsArray);
    const QJsonArray array = doc.array();

    const CustomTextAutoGenerateReply w(nullptr, TextAutoGenerateText::TextAutoGenerateReply::RequestTypes::Show);
    QCOMPARE(w.testParseToolCalls(array), result);
}

void TextAutoGenerateReplyTest::shouldParseToolCalls_data()
{
    QTest::addColumn<QByteArray>("toolCallsArray");
    QTest::addColumn<QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo>>("result");
    QTest::addRow("empty") << QByteArray() << QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo>();
    // TODO
}

#include "textautogeneratereplytest.moc"

#include "moc_textautogeneratereplytest.cpp"
