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

    void executeTool() override;
    [[nodiscard]] QString displayName() const override;
    [[nodiscard]] QString description() const override;

    void
    callTools(const QByteArray &chatId, const QByteArray &uuid, const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> &info) override;
};

void CustomTextToolPlugin::callTools([[maybe_unused]] const QByteArray &chatId,
                                     [[maybe_unused]] const QByteArray &uuid,
                                     [[maybe_unused]] const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> &info)
{
}

void CustomTextToolPlugin::executeTool()
{
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

    void executeTool() override;
    [[nodiscard]] QString displayName() const override;
    [[nodiscard]] QString description() const override;

    void
    callTools(const QByteArray &chatId, const QByteArray &uuid, const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> &info) override;
};

void CustomTextToolPlugin2::callTools([[maybe_unused]] const QByteArray &chatId,
                                      [[maybe_unused]] const QByteArray &uuid,
                                      [[maybe_unused]] const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo> &info)
{
    // Nothing
}

void CustomTextToolPlugin2::executeTool()
{
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

#include "moc_textautogeneratetexttoolplugintest.cpp"
