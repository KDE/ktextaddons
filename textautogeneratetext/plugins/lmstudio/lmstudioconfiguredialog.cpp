/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lmstudioconfiguredialog.h"
#include "lmstudiomanager.h"

#include "lmstudioconfigurewidget.h"
#include "lmstudioplugin.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
namespace
{
const char myLMStudioConfigureDialogGroupName[] = "LMStudioConfigureDialog";
}

using namespace Qt::Literals::StringLiterals;
LMStudioConfigureDialog::LMStudioConfigureDialog(LMStudioManager *manager, LMStudioPlugin *plugin, QWidget *parent)
    : KPageDialog(parent)
    , mConfigureWidget(new LMStudioConfigureWidget(manager, plugin, this))
    , mModelInstalledWidget(new LMStudioModelInstalledWidget(manager, this))
{
    setWindowTitle(i18nc("@title:window", "Configure LMStudio"));
    setFaceType(KPageDialog::List);
    setStandardButtons({QDialogButtonBox::StandardButton::Ok, QDialogButtonBox::StandardButton::Cancel, QDialogButtonBox::StandardButton::RestoreDefaults});

    const QString generalPageName = i18nc("@title Preferences page name", "General");
    auto configureGeneralWidgetPage = new KPageWidgetItem(mConfigureWidget, generalPageName);
    configureGeneralWidgetPage->setIcon(QIcon::fromTheme(u"://general-model"_s));
    mConfigureWidget->setObjectName(u"mLMStudioConfigureWidget"_s);
    addPage(configureGeneralWidgetPage);

    const QString modelInstalledPageName = i18nc("@title Preferences page name", "Installed model");
    auto configureInstalledModelWidgetPage = new KPageWidgetItem(mModelInstalledWidget, modelInstalledPageName);
    configureInstalledModelWidgetPage->setIcon(QIcon::fromTheme(u"://general-model"_s));
    mModelInstalledWidget->setObjectName(u"mLMStudioModelInstalledWidget"_s);
    addPage(configureInstalledModelWidgetPage);

    auto okButton = button(QDialogButtonBox::StandardButton::Ok);
    connect(mConfigureWidget, &LMStudioConfigureWidget::enableOkButton, this, [okButton](bool state) {
        okButton->setEnabled(state);
    });
    connect(buttonBox()->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &LMStudioConfigureDialog::slotRestoreDefaults);

    connect(buttonBox(), &QDialogButtonBox::accepted, this, &LMStudioConfigureDialog::slotAccepted);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myLMStudioConfigureDialogGroupName), QSize(400, 300));
}

LMStudioConfigureDialog::~LMStudioConfigureDialog() = default;

void LMStudioConfigureDialog::slotRestoreDefaults()
{
    mConfigureWidget->restoreToDefaults();
}

void LMStudioConfigureDialog::slotAccepted()
{
    mConfigureWidget->saveSettings();
    accept();
}

#include "moc_lmstudioconfiguredialog.cpp"
