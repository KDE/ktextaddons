/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateelicitationwidgettest.h"
#include "widgets/mcp/textautogenerateelicitationwidget.h"
#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDoubleSpinBox>
#include <QJsonArray>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QSignalSpy>
#include <QSpinBox>
#include <QTest>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequest>
QTEST_MAIN(TextAutoGenerateElicitationWidgetTest)
using namespace Qt::Literals::StringLiterals;
namespace
{
TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest createRequest(const QJsonObject &params)
{
    return TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest::fromJson(
        QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 1}, {"method"_L1, u"elicitation/create"_s}, {"params"_L1, params}});
}
}
TextAutoGenerateElicitationWidgetTest::TextAutoGenerateElicitationWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateElicitationWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateElicitationWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
}
void TextAutoGenerateElicitationWidgetTest::shouldCreateFormEditors()
{
    const QJsonObject properties{
        {"name"_L1, QJsonObject{{"type"_L1, u"string"_s}, {"title"_L1, u"Name"_s}, {"description"_L1, u"Your name"_s}, {"maxLength"_L1, 20}}},
        {"birthday"_L1, QJsonObject{{"type"_L1, u"string"_s}, {"format"_L1, u"date"_s}, {"default"_L1, u"2000-01-02"_s}}},
        {"age"_L1, QJsonObject{{"type"_L1, u"integer"_s}, {"minimum"_L1, 0}, {"maximum"_L1, 150}, {"default"_L1, 30}}},
        {"ratio"_L1, QJsonObject{{"type"_L1, u"number"_s}, {"default"_L1, 0.5}}},
        {"subscribe"_L1, QJsonObject{{"type"_L1, u"boolean"_s}, {"default"_L1, true}}},
        {"color"_L1, QJsonObject{{"type"_L1, u"string"_s}, {"enum"_L1, QJsonArray{u"red"_s, u"green"_s}}, {"default"_L1, u"green"_s}}},
        {"size"_L1,
         QJsonObject{{"type"_L1, u"string"_s},
                     {"oneOf"_L1,
                      QJsonArray{QJsonObject{{"const"_L1, u"s"_s}, {"title"_L1, u"Small"_s}}, QJsonObject{{"const"_L1, u"l"_s}, {"title"_L1, u"Large"_s}}}}}},
        {"tags"_L1,
         QJsonObject{{"type"_L1, u"array"_s},
                     {"items"_L1, QJsonObject{{"type"_L1, u"string"_s}, {"enum"_L1, QJsonArray{u"a"_s, u"b"_s}}}},
                     {"default"_L1, QJsonArray{u"b"_s}}}},
    };
    const QJsonObject params{
        {"mode"_L1, u"form"_s},
        {"message"_L1, u"Who are you?"_s},
        {"requestedSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, properties}, {"required"_L1, QJsonArray{u"name"_s}}}}};
    TextAutoGenerateText::TextAutoGenerateElicitationWidget w;
    w.setRequest(createRequest(params));

    auto messageLabel = w.findChild<QLabel *>(u"messageLabel"_s);
    QVERIFY(messageLabel);
    QCOMPARE(messageLabel->text(), u"Who are you?"_s);

    auto name = w.findChild<QLineEdit *>(u"name"_s);
    QVERIFY(name);
    QCOMPARE(name->maxLength(), 20);
    QCOMPARE(name->toolTip(), u"Your name"_s);

    auto birthday = w.findChild<QDateEdit *>(u"birthday"_s);
    QVERIFY(birthday);
    QCOMPARE(birthday->date(), QDate(2000, 1, 2));

    auto age = w.findChild<QSpinBox *>(u"age"_s);
    QVERIFY(age);
    QCOMPARE(age->minimum(), 0);
    QCOMPARE(age->maximum(), 150);
    QCOMPARE(age->value(), 30);

    auto ratio = w.findChild<QDoubleSpinBox *>(u"ratio"_s);
    QVERIFY(ratio);
    QCOMPARE(ratio->value(), 0.5);

    auto subscribe = w.findChild<QCheckBox *>(u"subscribe"_s);
    QVERIFY(subscribe);
    QVERIFY(subscribe->isChecked());

    auto color = w.findChild<QComboBox *>(u"color"_s);
    QVERIFY(color);
    QCOMPARE(color->count(), 2);
    QCOMPARE(color->currentData().toString(), u"green"_s);

    auto size = w.findChild<QComboBox *>(u"size"_s);
    QVERIFY(size);
    QCOMPARE(size->itemText(1), u"Large"_s);
    QCOMPARE(size->itemData(1).toString(), u"l"_s);

    auto tags = w.findChild<QListWidget *>(u"tags"_s);
    QVERIFY(tags);
    QCOMPARE(tags->count(), 2);
    QCOMPARE(tags->item(0)->checkState(), Qt::Unchecked);
    QCOMPARE(tags->item(1)->checkState(), Qt::Checked);

    // New request replaces form
    w.setRequest(createRequest(QJsonObject{{"mode"_L1, u"form"_s},
                                           {"message"_L1, u"Other"_s},
                                           {"requestedSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, QJsonObject{}}}}}));
    QTRY_VERIFY(!w.findChild<QLineEdit *>(u"name"_s));
    QCOMPARE(w.findChildren<QLabel *>(u"messageLabel"_s).count(), 1);
}

void TextAutoGenerateElicitationWidgetTest::shouldShowUrl()
{
    TextAutoGenerateText::TextAutoGenerateElicitationWidget w;
    w.setRequest(createRequest(
        QJsonObject{{"mode"_L1, u"url"_s}, {"message"_L1, u"Please log in"_s}, {"elicitationId"_L1, u"e1"_s}, {"url"_L1, u"https://example.com/login"_s}}));
    QCOMPARE(w.findChild<QLabel *>(u"messageLabel"_s)->text(), u"Please log in"_s);
    auto urlLabel = w.findChild<QLabel *>(u"urlLabel"_s);
    QVERIFY(urlLabel);
    QCOMPARE(urlLabel->text(), u"https://example.com/login"_s);
    // No content for URL request
    QVERIFY(!w.content().has_value());
    QVERIFY(w.isValid());
}

void TextAutoGenerateElicitationWidgetTest::shouldReturnContent()
{
    const QJsonObject properties{
        {"name"_L1, QJsonObject{{"type"_L1, u"string"_s}}},
        {"comment"_L1, QJsonObject{{"type"_L1, u"string"_s}}},
        {"birthday"_L1, QJsonObject{{"type"_L1, u"string"_s}, {"format"_L1, u"date"_s}, {"default"_L1, u"2000-01-02"_s}}},
        {"age"_L1, QJsonObject{{"type"_L1, u"integer"_s}, {"default"_L1, 30}}},
        {"ratio"_L1, QJsonObject{{"type"_L1, u"number"_s}, {"default"_L1, 0.5}}},
        {"subscribe"_L1, QJsonObject{{"type"_L1, u"boolean"_s}, {"default"_L1, true}}},
        {"color"_L1, QJsonObject{{"type"_L1, u"string"_s}, {"enum"_L1, QJsonArray{u"red"_s, u"green"_s}}, {"default"_L1, u"green"_s}}},
        {"tags"_L1,
         QJsonObject{{"type"_L1, u"array"_s},
                     {"items"_L1, QJsonObject{{"type"_L1, u"string"_s}, {"enum"_L1, QJsonArray{u"a"_s, u"b"_s}}}},
                     {"default"_L1, QJsonArray{u"b"_s}}}},
    };
    TextAutoGenerateText::TextAutoGenerateElicitationWidget w;
    w.setRequest(createRequest(QJsonObject{{"mode"_L1, u"form"_s},
                                           {"message"_L1, u"Who are you?"_s},
                                           {"requestedSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, properties}}}}));
    w.findChild<QLineEdit *>(u"name"_s)->setText(u"Laurent"_s);
    const auto content = w.content();
    QVERIFY(content.has_value());
    // Empty optional field is not sent
    QVERIFY(!content->contains(u"comment"_s));
    QCOMPARE(std::get<QString>(content->value(u"name"_s)), u"Laurent"_s);
    QCOMPARE(std::get<QString>(content->value(u"birthday"_s)), u"2000-01-02"_s);
    QCOMPARE(std::get<int>(content->value(u"age"_s)), 30);
    QCOMPARE(std::get<double>(content->value(u"ratio"_s)), 0.5);
    QCOMPARE(std::get<bool>(content->value(u"subscribe"_s)), true);
    QCOMPARE(std::get<QString>(content->value(u"color"_s)), u"green"_s);
    QCOMPARE(std::get<QStringList>(content->value(u"tags"_s)), QStringList{u"b"_s});
}

void TextAutoGenerateElicitationWidgetTest::shouldValidateConstraints()
{
    const QJsonObject properties{
        {"name"_L1, QJsonObject{{"type"_L1, u"string"_s}, {"minLength"_L1, 3}}},
        {"code"_L1, QJsonObject{{"type"_L1, u"string"_s}, {"minLength"_L1, 2}}},
        {"tags"_L1,
         QJsonObject{{"type"_L1, u"array"_s},
                     {"items"_L1, QJsonObject{{"type"_L1, u"string"_s}, {"enum"_L1, QJsonArray{u"a"_s, u"b"_s, u"c"_s}}}},
                     {"minItems"_L1, 1},
                     {"maxItems"_L1, 2}}},
    };
    TextAutoGenerateText::TextAutoGenerateElicitationWidget w;
    QSignalSpy contentChangedSpy(&w, &TextAutoGenerateText::TextAutoGenerateElicitationWidget::contentChanged);
    w.setRequest(createRequest(
        QJsonObject{{"mode"_L1, u"form"_s},
                    {"message"_L1, u"Message"_s},
                    {"requestedSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, properties}, {"required"_L1, QJsonArray{u"name"_s}}}}}));
    QCOMPARE(contentChangedSpy.count(), 1);
    auto name = w.findChild<QLineEdit *>(u"name"_s);
    auto code = w.findChild<QLineEdit *>(u"code"_s);
    auto tags = w.findChild<QListWidget *>(u"tags"_s);
    // Required field is empty, no tag
    QVERIFY(!w.isValid());

    name->setText(u"ab"_s);
    QCOMPARE(contentChangedSpy.count(), 2);
    tags->item(0)->setCheckState(Qt::Checked);
    QCOMPARE(contentChangedSpy.count(), 3);
    // Too short
    QVERIFY(!w.isValid());
    name->setText(u"abc"_s);
    QVERIFY(w.isValid());

    // Optional field: empty is valid, too short is not
    code->setText(u"x"_s);
    QVERIFY(!w.isValid());
    code->clear();
    QVERIFY(w.isValid());

    // Too many items
    tags->item(1)->setCheckState(Qt::Checked);
    tags->item(2)->setCheckState(Qt::Checked);
    QVERIFY(!w.isValid());
    tags->item(2)->setCheckState(Qt::Unchecked);
    QVERIFY(w.isValid());
}

#include "moc_textautogenerateelicitationwidgettest.cpp"
