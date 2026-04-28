/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lmstudioconfiguredialog.h"
#include "lmstudiomanager.h"

#include "lmstudioconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QWindow>

namespace
{
const char myLMStudioConfigureDialogGroupName[] = "LMStudioConfigureDialog";
}

using namespace Qt::Literals::StringLiterals;
LMStudioConfigureDialog::LMStudioConfigureDialog(LMStudioManager *manager, QWidget *parent)
    : KPageDialog(parent)
    , mConfigureWidget(new LMStudioConfigureWidget(manager, this))
    , mModelInstalledWidget(new LMStudioModelInstalledWidget(manager, this))
{
    setWindowTitle(i18nc("@title:window", "Configure LMStudio"));
    setFaceType(KPageDialog::List);
    setStandardButtons({QDialogButtonBox::StandardButton::Ok, QDialogButtonBox::StandardButton::Cancel, QDialogButtonBox::StandardButton::RestoreDefaults});

    const QString generalPageName = i18nc("@title Preferences page name", "General");
    auto configureGeneralWidgetPage = new KPageWidgetItem(mConfigureWidget, generalPageName);
    configureGeneralWidgetPage->setIcon(QIcon::fromTheme(u"://ollama-general-model"_s));
    mConfigureWidget->setObjectName(u"mLMStudioConfigureWidget"_s);
    addPage(configureGeneralWidgetPage);

    const QString modelInstalledPageName = i18nc("@title Preferences page name", "Installed model");
    auto configureInstalledModelWidgetPage = new KPageWidgetItem(mModelInstalledWidget, modelInstalledPageName);
    configureInstalledModelWidgetPage->setIcon(QIcon::fromTheme(u"://ollama-general-model"_s));
    mModelInstalledWidget->setObjectName(u"mLMStudioModelInstalledWidget"_s);
    addPage(configureInstalledModelWidgetPage);

    auto okButton = button(QDialogButtonBox::StandardButton::Ok);
    connect(mConfigureWidget, &LMStudioConfigureWidget::enableOkButton, this, [okButton](bool state) {
        okButton->setEnabled(state);
    });
    connect(buttonBox()->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &LMStudioConfigureDialog::slotRestoreDefaults);

    connect(buttonBox(), &QDialogButtonBox::accepted, this, &LMStudioConfigureDialog::slotAccepted);
    readConfig();
}

LMStudioConfigureDialog::~LMStudioConfigureDialog()
{
    writeConfig();
}

void LMStudioConfigureDialog::slotRestoreDefaults()
{
    mConfigureWidget->restoreToDefaults();
}

void LMStudioConfigureDialog::slotAccepted()
{
    mConfigureWidget->saveSettings();
    accept();
}

void LMStudioConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myLMStudioConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void LMStudioConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myLMStudioConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_lmstudioconfiguredialog.cpp"
