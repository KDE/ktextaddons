/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolplugintest.h"
#include "core/tools/textautogeneratetexttoolplugin.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
class CustomTextToolPlugin : public TextAutoGenerateText::TextAutoGenerateTextToolPlugin
{
public:
    explicit CustomTextToolPlugin(QObject *parent = nullptr)
        : TextAutoGenerateText::TextAutoGenerateTextToolPlugin(parent)
    {
    }
    ~CustomTextToolPlugin() override = default;

    [[nodiscard]] QString displayName() const override;
    [[nodiscard]] QString description() const override;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *callTool() override;
};

TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *CustomTextToolPlugin::callTool()
{
    return nullptr;
}

QString CustomTextToolPlugin::displayName() const
{
    return {};
}

QString CustomTextToolPlugin::description() const
{
    return {};
}

class CustomTextToolPlugin2 : public TextAutoGenerateText::TextAutoGenerateTextToolPlugin
{
public:
    explicit CustomTextToolPlugin2(QObject *parent = nullptr)
        : TextAutoGenerateText::TextAutoGenerateTextToolPlugin(parent)
    {
    }
    ~CustomTextToolPlugin2() override = default;

    [[nodiscard]] QString displayName() const override;
    [[nodiscard]] QString description() const override;

    [[nodiscard]] QJsonObject testGenerateMetadata() const;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *callTool() override;
};

TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *CustomTextToolPlugin2::callTool()
{
    return nullptr;
}

QJsonObject CustomTextToolPlugin2::testGenerateMetadata() const
{
    return generateMetadata();
}

QString CustomTextToolPlugin2::displayName() const
{
    return u"description custom2"_s;
}

QString CustomTextToolPlugin2::description() const
{
    return u"foo bla"_s;
}

QTEST_GUILESS_MAIN(TextAutoGenerateTextToolPluginTest)
TextAutoGenerateTextToolPluginTest::TextAutoGenerateTextToolPluginTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextToolPluginTest::shouldHaveDefaultValues()
{
    CustomTextToolPlugin w;
    QVERIFY(w.description().isEmpty());
    QVERIFY(!w.metadata().isEmpty());
    QVERIFY(w.displayName().isEmpty());
    QVERIFY(w.toolNameId().isEmpty());
    QVERIFY(w.enabled());
    QVERIFY(!w.isValid());
}

void TextAutoGenerateTextToolPluginTest::shouldGenerateMetadata()
{
    QFETCH(QByteArray, toolNameId);
    QFETCH(QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty>, properties);
    QFETCH(QByteArray, result);

    CustomTextToolPlugin2 w;
    w.setToolNameId(toolNameId);
    w.setProperties(properties);
    const QJsonObject obj = w.testGenerateMetadata();
    const QJsonDocument doc(obj);
    const QByteArray ba = doc.toJson();
    qDebug() << " ba " << ba;
    QCOMPARE(ba, result);
}

void TextAutoGenerateTextToolPluginTest::shouldGenerateMetadata_data()
{
    QTest::addColumn<QByteArray>("toolNameId");
    QTest::addColumn<QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty>>("properties");
    QTest::addColumn<QByteArray>("result");
    {
        QTest::addRow("empty") << ""_ba << QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty>{}
                               << QByteArray(
                                      "{\n    \"function\": {\n        \"description\": \"foo bla\",\n        \"name\": \"\",\n        \"parameters\": {\n     "
                                      "       \"properties\": {\n            },\n            \"required\": [\n            ],\n            \"type\": "
                                      "\"object\"\n        }\n    },\n    \"type\": \"function\"\n}\n");
    }
    {
        QTest::addRow("test1") << "test_example1"_ba << QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty>{}
                               << QByteArray(
                                      "{\n    \"function\": {\n        \"description\": \"foo bla\",\n        \"name\": \"test_example1\",\n        "
                                      "\"parameters\": {\n            \"properties\": {\n            },\n            \"required\": [\n            ],\n         "
                                      "   \"type\": \"object\"\n        }\n    },\n    \"type\": \"function\"\n}\n");
    }
    {
        QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> lst;
        {
            TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty prop;
            prop.setDescription(kli18n("The name of the city"));
            prop.setName(u"city"_s);
            lst.append(prop);
        }
        QTest::addRow("test2")
            << "test_example2"_ba << lst
            << QByteArray(
                   "{\n    \"function\": {\n        \"description\": \"foo bla\",\n        \"name\": \"test_example2\",\n        \"parameters\": {\n           "
                   " \"properties\": {\n                \"city\": {\n                    \"description\": \"The name of the city\",\n                    "
                   "\"type\": \"string\"\n                }\n            },\n            \"required\": [\n                \"city\"\n            ],\n           "
                   " \"type\": \"object\"\n        }\n    },\n    \"type\": \"function\"\n}\n");
    }

    {
        QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> lst;
        {
            TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty prop;
            prop.setDescription(kli18n("Time or date"));
            prop.setName(u"type"_s);
            prop.setTypeElements({u"date"_s, u"time"_s, u"date and time"_s});
            lst.append(prop);
        }
        QTest::addRow("test3-enum")
            << "test_example_enum"_ba << lst
            << QByteArray(
                   "{\n    \"function\": {\n        \"description\": \"foo bla\",\n        \"name\": \"test_example_enum\",\n        \"parameters\": {\n       "
                   "     \"properties\": {\n                \"type\": {\n                    \"description\": \"Time or date\",\n                    \"enum\": "
                   "[\n                        \"date\",\n                        \"time\",\n                        \"date and time\"\n                    "
                   "],\n                    \"type\": \"string\"\n                }\n            },\n            \"required\": [\n                \"type\"\n   "
                   "         ],\n            \"type\": \"object\"\n        }\n    },\n    \"type\": \"function\"\n}\n");
    }
}

#include "moc_textautogeneratetexttoolplugintest.cpp"
