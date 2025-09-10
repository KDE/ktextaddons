/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanagertest.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "core/textautogeneratetextplugin.h"
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextInstancesManagerTest)
using namespace Qt::Literals::StringLiterals;

class CustomPlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
public:
    using TextAutoGenerateTextPlugin::TextAutoGenerateTextPlugin;

    void showConfigureDialog(QWidget *parentWidget) override;
    [[nodiscard]] QString translatedPluginName() const override;
    [[nodiscard]] QString engineName() const override;
    [[nodiscard]] QString currentModel() const override;
    void setCurrentModel(const QString &) override;
    void askToAssistant(const QString &msg) override;
    [[nodiscard]] QString displayName() const override;
    void setDisplayName(const QString &newName) override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType engineType() const override;

    [[nodiscard]] bool hasVisionSupport() const override;
    [[nodiscard]] bool hasToolsSupport() const override;

protected:
    void sendToAssistant(const SendToAssistantInfo &info) override;

private:
    QString mCurrentModel;
    QString mDisplayName;
};

void CustomPlugin::showConfigureDialog([[maybe_unused]] QWidget *parentWidget)
{
}

QString CustomPlugin::translatedPluginName() const
{
    return u"custom_plugin"_s;
}

QString CustomPlugin::engineName() const
{
    return u"CustomPugin"_s;
}

QString CustomPlugin::currentModel() const
{
    return mCurrentModel;
}

void CustomPlugin::setCurrentModel(const QString &modelName)
{
    mCurrentModel = modelName;
}

void CustomPlugin::askToAssistant([[maybe_unused]] const QString &msg)
{
}

QString CustomPlugin::displayName() const
{
    return mDisplayName;
}

void CustomPlugin::setDisplayName(const QString &newName)
{
    mDisplayName = newName;
}

TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType CustomPlugin::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Local;
}

bool CustomPlugin::hasVisionSupport() const
{
    return false;
}

bool CustomPlugin::hasToolsSupport() const
{
    return false;
}

void CustomPlugin::sendToAssistant([[maybe_unused]] const SendToAssistantInfo &info)
{
}

TextAutoGenerateTextInstancesManagerTest::TextAutoGenerateTextInstancesManagerTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateTextInstancesManagerTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(nullptr);
    QVERIFY(w.instances().isEmpty());
    QVERIFY(w.currentInstance().isEmpty());
    QVERIFY(w.isEmpty());
    QVERIFY(w.textAutoGenerateTextInstanceModel());
    QVERIFY(w.instanceDisplayNames().isEmpty());
    QVERIFY(!w.textAutoGeneratePlugin());
}

void TextAutoGenerateTextInstancesManagerTest::shouldAddInstances()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo1"_ba);
        w.addInstance(instance);
    }

    QVERIFY(!w.isEmpty());
    QCOMPARE(w.instances().count(), 1);
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        w.addInstance(instance);
    }
    QCOMPARE(w.instances().count(), 2);
}

void TextAutoGenerateTextInstancesManagerTest::shouldRemoveInstances()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo1"_ba);
        w.addInstance(instance);
    }
    QVERIFY(!w.isEmpty());
    QCOMPARE(w.instances().count(), 1);

    w.deleteInstance("foo1"_ba);
    QVERIFY(w.isEmpty());

    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        w.addInstance(instance);
    }
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo3"_ba);
        w.addInstance(instance);
    }
    QCOMPARE(w.instances().count(), 2);
    // Not existing
    w.deleteInstance("foo7"_ba);
    QCOMPARE(w.instances().count(), 2);
}

void TextAutoGenerateTextInstancesManagerTest::shouldReturnInstanceDisplayNames()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo1"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display1"_s);
        instance->setPlugin(plugin);
        w.addInstance(instance);
    }
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display2"_s);
        instance->setPlugin(plugin);
        w.addInstance(instance);
    }
    const QStringList lst = {u"display1"_s, u"display2"_s};
    QCOMPARE(w.instanceDisplayNames(), lst);
}

void TextAutoGenerateTextInstancesManagerTest::shouldReturnIsEmpty()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo1"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display1"_s);
        instance->setPlugin(plugin);
        instance->setEnabled(false);
        w.addInstance(instance);
    }
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display2"_s);
        instance->setPlugin(plugin);
        instance->setEnabled(false);
        w.addInstance(instance);
    }
    QVERIFY(w.isEmpty());
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo3"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display3"_s);
        instance->setPlugin(plugin);
        instance->setEnabled(true);
        w.addInstance(instance);
    }
    QVERIFY(!w.isEmpty());
}

void TextAutoGenerateTextInstancesManagerTest::shouldReturnCurrentPluginNotCurrentInstance()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo1"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display1"_s);
        instance->setPlugin(plugin);
        instance->setEnabled(false);
        w.addInstance(instance);
    }
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display2"_s);
        instance->setPlugin(plugin);
        instance->setEnabled(false);
        w.addInstance(instance);
    }
    // No active instance and not currentInstance
    QVERIFY(!w.textAutoGeneratePlugin());
}

void TextAutoGenerateTextInstancesManagerTest::shouldReturnCurrentPluginCurrentInstanceAllDisabled()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo1"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display1"_s);
        instance->setPlugin(plugin);
        instance->setEnabled(false);
        w.addInstance(instance);
    }
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display2"_s);
        instance->setPlugin(plugin);
        instance->setEnabled(false);
        w.addInstance(instance);
    }
    w.setCurrentinstance("foo1"_ba);
    // No active instance and currentInstance
    QVERIFY(!w.textAutoGeneratePlugin());
}

void TextAutoGenerateTextInstancesManagerTest::shouldReturnCurrentPluginCurrentInstance()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    auto instanceFoo = new TextAutoGenerateText::TextAutoGenerateTextInstance();
    instanceFoo->setInstanceUuid("foo1"_ba);
    instanceFoo->setPluginName(u"custom"_s);
    auto pluginFoo = new CustomPlugin(&autoGenerateManager, instanceFoo);
    pluginFoo->setDisplayName(u"display1"_s);
    instanceFoo->setPlugin(pluginFoo);
    instanceFoo->setEnabled(true);
    w.addInstance(instanceFoo);
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display2"_s);
        instance->setPlugin(plugin);
        instance->setEnabled(true);
        w.addInstance(instance);
    }
    w.setCurrentinstance("foo1"_ba);
    QCOMPARE(w.textAutoGeneratePlugin(), pluginFoo);
}

void TextAutoGenerateTextInstancesManagerTest::shouldReturnCurrentPluginWithInvalidCurrentInstance()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    auto instanceFoo = new TextAutoGenerateText::TextAutoGenerateTextInstance();
    instanceFoo->setInstanceUuid("foo1"_ba);
    instanceFoo->setPluginName(u"custom"_s);
    auto pluginFoo = new CustomPlugin(&autoGenerateManager, instanceFoo);
    pluginFoo->setDisplayName(u"display1"_s);
    instanceFoo->setPlugin(pluginFoo);
    instanceFoo->setEnabled(true);
    w.addInstance(instanceFoo);
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display2"_s);
        instance->setPlugin(plugin);
        instance->setEnabled(true);
        w.addInstance(instance);
    }
    // Invalid current Instance
    w.setCurrentinstance("foo555"_ba);
    QCOMPARE(w.textAutoGeneratePlugin(), pluginFoo);
}

void TextAutoGenerateTextInstancesManagerTest::shouldReturnCurrentPluginWithInvalidCurrentInstanceNoEnableInstance()
{
    TextAutoGenerateText::TextAutoGenerateManager autoGenerateManager;
    TextAutoGenerateText::TextAutoGenerateTextInstancesManager w(&autoGenerateManager, nullptr);
    QVERIFY(w.isEmpty());
    auto instanceFoo = new TextAutoGenerateText::TextAutoGenerateTextInstance();
    instanceFoo->setInstanceUuid("foo1"_ba);
    instanceFoo->setPluginName(u"custom"_s);
    auto pluginFoo = new CustomPlugin(&autoGenerateManager, instanceFoo);
    pluginFoo->setDisplayName(u"display1"_s);
    instanceFoo->setPlugin(pluginFoo);
    instanceFoo->setEnabled(false);
    w.addInstance(instanceFoo);
    {
        auto instance = new TextAutoGenerateText::TextAutoGenerateTextInstance();
        instance->setInstanceUuid("foo2"_ba);
        instance->setPluginName(u"custom"_s);
        auto plugin = new CustomPlugin(&autoGenerateManager, instance);
        plugin->setDisplayName(u"display2"_s);
        instance->setPlugin(plugin);
        instance->setEnabled(false);
        w.addInstance(instance);
    }
    // Invalid current Instance
    w.setCurrentinstance("foo555"_ba);
    QVERIFY(!w.textAutoGeneratePlugin());
}

#include "moc_textautogeneratetextinstancesmanagertest.cpp"
