/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesamplingdialogtest.h"
#include "widgets/mcp/textautogeneratesamplingdialog.h"
#include <QDialogButtonBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QTest>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequest>
QTEST_MAIN(TextAutoGenerateSamplingDialogTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
TextAutoGenerateSamplingDialogTest::TextAutoGenerateSamplingDialogTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSamplingDialogTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateSamplingDialog d;
    QVERIFY(!d.windowTitle().isEmpty());

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mLabel = d.findChild<QLabel *>(u"mLabel"_s);
    QVERIFY(mLabel);
    QVERIFY(mLabel->wordWrap());
    QVERIFY(!mLabel->text().isEmpty());

    auto mMessages = d.findChild<QPlainTextEdit *>(u"mMessages"_s);
    QVERIFY(mMessages);
    QVERIFY(mMessages->isReadOnly());
    QVERIFY(mMessages->toPlainText().isEmpty());

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);
}

void TextAutoGenerateSamplingDialogTest::shouldShowRequest()
{
    McpProtocolTextContent text;
    text.setText(u"Hello"_s);
    McpProtocolSamplingMessage user;
    user.setRole(McpProtocolUtils::Role::User);
    user.setContent(text);
    McpProtocolSamplingMessage image;
    image.setRole(McpProtocolUtils::Role::Assistant);
    image.setContent(McpProtocolImageContent());
    McpProtocolCreateMessageRequestParams params;
    params.setSystemPrompt(u"Be short"_s);
    params.setMessages({user, image});
    McpProtocolCreateMessageRequest request;
    request.setParams(params);

    const QString requestText = TextAutoGenerateText::TextAutoGenerateSamplingDialog::requestText(request);
    QVERIFY(requestText.contains(u"Be short"_s));
    QVERIFY(requestText.contains(u"Hello"_s));
    QVERIFY(requestText.indexOf(u"Be short"_s) < requestText.indexOf(u"Hello"_s));
    QVERIFY(TextAutoGenerateText::TextAutoGenerateSamplingDialog::requestText({}).isEmpty());

    TextAutoGenerateText::TextAutoGenerateSamplingDialog d;
    d.setServerName(u"My Server"_s);
    d.setRequest(request);
    QVERIFY(d.findChild<QLabel *>(u"mLabel"_s)->text().contains(u"My Server"_s));
    QCOMPARE(d.findChild<QPlainTextEdit *>(u"mMessages"_s)->toPlainText(), requestText);
}

#include "moc_textautogeneratesamplingdialogtest.cpp"
