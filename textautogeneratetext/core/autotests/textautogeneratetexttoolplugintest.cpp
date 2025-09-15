/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolplugintest.h"
#include "core/tools/textautogeneratetexttoolplugin.h"
#include <QTest>

class CustomTextToolPlugin : public TextAutoGenerateText::TextAutoGenerateTextToolPlugin
{
public:
    explicit CustomTextToolPlugin(QObject *parent = nullptr)
        : TextAutoGenerateText::TextAutoGenerateTextToolPlugin(parent)
    {
    }
    ~CustomTextToolPlugin() override = default;

    [[nodiscard]] QString executeTool() override;
    [[nodiscard]] QString displayName() const override;
    [[nodiscard]] QString description() const override;
    [[nodiscard]] QByteArray metadata() const override;
};

QString CustomTextToolPlugin::executeTool()
{
    return {};
}

QString CustomTextToolPlugin::displayName() const
{
    return {};
}

QString CustomTextToolPlugin::description() const
{
    return {};
}

QByteArray CustomTextToolPlugin::metadata() const
{
    return {};
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
    QVERIFY(w.metadata().isEmpty());
    QVERIFY(w.displayName().isEmpty());
    QVERIFY(w.executeTool().isEmpty());
    QVERIFY(w.toolNameId().isEmpty());
    QVERIFY(w.enabled());
    QVERIFY(!w.isValid());
}

#include "moc_textautogeneratetexttoolplugintest.cpp"
