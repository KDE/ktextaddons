/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverconfigurationmodulewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QCheckBox>
#include <QProcess>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerUtils>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
#include <TextAutoGenerateTextMcpProtocolWidgets/McpProtocolServerConfigureWidget>
#if !defined(Q_OS_WIN) && !defined(Q_OS_MACOS)
#include <QDBusConnection>
#include <QDBusConnectionInterface>
#include <QDBusMessage>
#endif

using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
MCPServerConfigurationModuleWidget::MCPServerConfigurationModuleWidget(QWidget *parent)
    : QWidget{parent}
    , mMcpProtocolServerConfigureWidget(new TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget(this))
    , mEnabled(new QCheckBox(i18n("Enabled"), this))
    , mConfirmModify(new QCheckBox(i18nc("@option:check", "Ask confirmation before running tools which modify data"), this))
{
    auto lay = new QVBoxLayout(this);
    lay->addWidget(mEnabled);

    mConfirmModify->setObjectName(u"mConfirmModify"_s);
    lay->addWidget(mConfirmModify);

    lay->addWidget(mMcpProtocolServerConfigureWidget);
    lay->addStretch(1);

    connect(mMcpProtocolServerConfigureWidget,
            &TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget::settingsChanged,
            this,
            &MCPServerConfigurationModuleWidget::configureChanged);
    connect(mEnabled, &QCheckBox::clicked, this, &MCPServerConfigurationModuleWidget::configureChanged);
    connect(mConfirmModify, &QCheckBox::clicked, this, &MCPServerConfigurationModuleWidget::configureChanged);

    connect(mEnabled,
            &QCheckBox::toggled,
            mMcpProtocolServerConfigureWidget,
            &TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureWidget::setEnabled);
    connect(mEnabled, &QCheckBox::toggled, mConfirmModify, &QCheckBox::setEnabled);
    mConfirmModify->setEnabled(false);

    mMcpProtocolServerConfigureWidget->setEnabled(false);
}

MCPServerConfigurationModuleWidget::~MCPServerConfigurationModuleWidget() = default;

void MCPServerConfigurationModuleWidget::load()
{
    KSharedConfigPtr config = KSharedConfig::openConfig(mConfigName);
    const KConfigGroup group = config->group(u"General"_s);

    mEnabled->setChecked(group.readEntry("Enabled", false));
    mConfirmModify->setChecked(group.readEntry("AskModify", true));

    TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::loadSettings(config,
                                                                              this,
                                                                              [this](const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &settings) {
                                                                                  mMcpProtocolServerConfigureWidget->setSettings(settings);
                                                                                  Q_EMIT needSave(false);
                                                                              });
}

void MCPServerConfigurationModuleWidget::save()
{
    KSharedConfigPtr config = KSharedConfig::openConfig(mConfigName);
    KConfigGroup group = config->group(u"General"_s);
    group.writeEntry("Enabled", mEnabled->isChecked());
    group.writeEntry("AskModify", mConfirmModify->isChecked());

    TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::saveSettings(config, mMcpProtocolServerConfigureWidget->settings());
    config->sync();
    reloadServer();
}

void MCPServerConfigurationModuleWidget::defaults()
{
    mEnabled->setChecked(false);
    mConfirmModify->setChecked(true);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::defaultServerUrl());
    mMcpProtocolServerConfigureWidget->setSettings(settings);
    Q_EMIT configureChanged();
}

void MCPServerConfigurationModuleWidget::reloadServer()
{
#if !defined(Q_OS_WIN) && !defined(Q_OS_MACOS)
    if (!mDbusName.isEmpty()) {
        QDBusConnection bus = QDBusConnection::sessionBus();
        if (bus.isConnected() && bus.interface() && bus.interface()->isServiceRegistered(mDbusName)) {
            const QDBusMessage msg = QDBusMessage::createMethodCall(mDbusName, u"/"_s, mDbusName, u"reload"_s);
            bus.asyncCall(msg);
            return;
        }
    }
#endif
    if (mEnabled->isChecked() && !mExecName.isEmpty()) {
        QProcess::startDetached(mExecName, {});
    }
}

QString MCPServerConfigurationModuleWidget::execName() const
{
    return mExecName;
}

void MCPServerConfigurationModuleWidget::setExecName(const QString &newExecName)
{
    mExecName = newExecName;
}

QString MCPServerConfigurationModuleWidget::dbusName() const
{
    return mDbusName;
}

void MCPServerConfigurationModuleWidget::setDbusName(const QString &newDbusName)
{
    mDbusName = newDbusName;
}

QString MCPServerConfigurationModuleWidget::configName() const
{
    return mConfigName;
}

void MCPServerConfigurationModuleWidget::setConfigName(const QString &newConfigName)
{
    mConfigName = newConfigName;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolWidgets::MCPServerConfigurationModuleWidget &t)
{
    d.space() << "mConfigName: " << t.configName();
    d.space() << "mDbusName: " << t.dbusName();
    d.space() << "mExecName: " << t.execName();
    return d;
}
