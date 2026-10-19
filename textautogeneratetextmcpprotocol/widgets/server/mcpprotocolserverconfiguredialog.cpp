/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverconfiguredialog.h"
#include "server/mcpprotocolserverconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerUtils>

namespace
{
const char myMcpProtocolServerConfigureDialogGroupName[] = "McpProtocolServerConfigureDialog";
}
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
McpProtocolServerConfigureDialog::McpProtocolServerConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mMcpProtocolServerConfigureWidget(new McpProtocolServerConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Server Configuration"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mMcpProtocolServerConfigureWidget->setObjectName(u"mMcpProtocolServerConfigureWidget"_s);
    mainLayout->addWidget(mMcpProtocolServerConfigureWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    auto buttonOk = button->button(QDialogButtonBox::Ok);
    // Enabled when settings are loaded
    buttonOk->setEnabled(false);
    connect(button, &QDialogButtonBox::rejected, this, &McpProtocolServerConfigureDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, [this]() {
        TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::saveSettings(mMcpProtocolServerConfigureWidget->settings());
        accept();
    });
    connect(mMcpProtocolServerConfigureWidget, &McpProtocolServerConfigureWidget::settingsChanged, this, [this, buttonOk]() {
        buttonOk->setEnabled(mMcpProtocolServerConfigureWidget->isValid());
    });
    TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils::loadSettings(this,
                                                                              [this](const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &settings) {
                                                                                  mMcpProtocolServerConfigureWidget->setSettings(settings);
                                                                              });
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myMcpProtocolServerConfigureDialogGroupName), QSize(500, 200));
}

McpProtocolServerConfigureDialog::~McpProtocolServerConfigureDialog() = default;

#include "moc_mcpprotocolserverconfiguredialog.cpp"
