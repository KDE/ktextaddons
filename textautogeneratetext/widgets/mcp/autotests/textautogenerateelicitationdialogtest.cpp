/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateelicitationdialogtest.h"
#include "widgets/mcp/textautogenerateelicitationdialog.h"
#include "widgets/mcp/textautogenerateelicitationwidget.h"
#include <QDialogButtonBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequest>
QTEST_MAIN(TextAutoGenerateElicitationDialogTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateElicitationDialogTest::TextAutoGenerateElicitationDialogTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateElicitationDialogTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateElicitationDialog d;
    QVERIFY(!d.windowTitle().isEmpty());

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mTextAutoGenerateElicitationWidget = d.findChild<TextAutoGenerateText::TextAutoGenerateElicitationWidget *>(u"mTextAutoGenerateElicitationWidget"_s);
    QVERIFY(mTextAutoGenerateElicitationWidget);

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);

    auto declineButton = d.findChild<QPushButton *>(u"declineButton"_s);
    QVERIFY(declineButton);

    QCOMPARE(d.elicitResult().action(), TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Cancel);
}

void TextAutoGenerateElicitationDialogTest::shouldReturnElicitResult()
{
    const QJsonObject params{{"mode"_L1, u"form"_s},
                             {"message"_L1, u"Name?"_s},
                             {"requestedSchema"_L1,
                              QJsonObject{{"type"_L1, u"object"_s},
                                          {"properties"_L1, QJsonObject{{"name"_L1, QJsonObject{{"type"_L1, u"string"_s}}}}},
                                          {"required"_L1, QJsonArray{u"name"_s}}}}};
    const auto request = TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest::fromJson(
        QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 1}, {"method"_L1, u"elicitation/create"_s}, {"params"_L1, params}});
    {
        TextAutoGenerateText::TextAutoGenerateElicitationDialog d;
        d.setRequest(request);
        auto acceptButton = d.findChild<QDialogButtonBox *>(u"button"_s)->button(QDialogButtonBox::Ok);
        // Required field is empty
        QVERIFY(!acceptButton->isEnabled());
        d.findChild<QLineEdit *>(u"name"_s)->setText(u"Laurent"_s);
        QVERIFY(acceptButton->isEnabled());
        acceptButton->click();
        const auto result = d.elicitResult();
        QCOMPARE(result.action(), TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Accept);
        QVERIFY(result.content().has_value());
        QCOMPARE(std::get<QString>(result.content()->value(u"name"_s)), u"Laurent"_s);
    }
    {
        TextAutoGenerateText::TextAutoGenerateElicitationDialog d;
        d.setRequest(request);
        d.findChild<QLineEdit *>(u"name"_s)->setText(u"Laurent"_s);
        d.findChild<QPushButton *>(u"declineButton"_s)->click();
        const auto result = d.elicitResult();
        QCOMPARE(result.action(), TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Decline);
        // Content is only sent when user accepts
        QVERIFY(!result.content().has_value());
    }
}
#include "moc_textautogenerateelicitationdialogtest.cpp"
