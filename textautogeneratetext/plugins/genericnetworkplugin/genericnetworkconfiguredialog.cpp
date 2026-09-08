/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkconfiguredialog.h"

#include "genericnetworkavailablemodelwidget.h"
#include "genericnetworkmanager.h"
#include "genericnetworknetworkpluginconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
namespace
{
const char myGenericNetworkConfigureDialogGroupName[] = "GenericNetworkConfigureDialog";
}
using namespace Qt::Literals::StringLiterals;
GenericNetworkConfigureDialog::GenericNetworkConfigureDialog(GenericNetworkManager *manager, QWidget *parent)
    : KPageDialog(parent)
    , mConfigureWidget(new GenericNetworkNetworkPluginConfigureWidget(manager, this))
    , mAvailableModelWidget(new GenericNetworkAvailableModelWidget(manager, this))
{
    setWindowTitle(i18nc("@title:window", "Configure %1", manager->translatedPluginName()));
    setFaceType(KPageDialog::List);

    const QString generalPageName = i18nc("@title Preferences page name", "General");
    auto configureGeneralWidgetPage = new KPageWidgetItem(mConfigureWidget, generalPageName);
    configureGeneralWidgetPage->setIcon(QIcon::fromTheme(u"://general-model"_s));
    mConfigureWidget->setObjectName(u"mConfigureWidget"_s);
    addPage(configureGeneralWidgetPage);

    const QString modelAvailablePageName = i18nc("@title Preferences page name", "Available Models");
    auto configureModelWidgetPage = new KPageWidgetItem(mAvailableModelWidget, modelAvailablePageName);
    configureModelWidgetPage->setIcon(QIcon::fromTheme(u"://available-models"_s));
    mAvailableModelWidget->setObjectName(u"mAvailableModelWidget"_s);
    addPage(configureModelWidgetPage);

    auto okButton = button(QDialogButtonBox::StandardButton::Ok);
    connect(mConfigureWidget, &GenericNetworkNetworkPluginConfigureWidget::enableOkButton, this, [okButton](bool state) {
        okButton->setEnabled(state);
    });

    connect(buttonBox(), &QDialogButtonBox::accepted, this, &GenericNetworkConfigureDialog::slotAccepted);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myGenericNetworkConfigureDialogGroupName), QSize(400, 300));
}

GenericNetworkConfigureDialog::~GenericNetworkConfigureDialog() = default;

void GenericNetworkConfigureDialog::slotAccepted()
{
    mConfigureWidget->saveSettings();
    accept();
}

#include "moc_genericnetworkconfiguredialog.cpp"
