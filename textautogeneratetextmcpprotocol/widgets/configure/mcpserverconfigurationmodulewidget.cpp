/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverconfigurationmodulewidget.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolWidgets/McpProtocolServerConfigureWidget>

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
    // TODO
}

void MCPServerConfigurationModuleWidget::save()
{
    // TODO
}

void MCPServerConfigurationModuleWidget::defaults()
{
    // TODO
}

void MCPServerConfigurationModuleWidget::reloadServer()
{
    // TODO
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
