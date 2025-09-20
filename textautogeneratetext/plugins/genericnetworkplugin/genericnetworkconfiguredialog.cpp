/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkconfiguredialog.h"

#include "genericnetworkavailablemodelwidget.h"
#include "genericnetworkmanager.h"
#include "genericnetworknetworkpluginconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QWindow>
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
    mConfigureWidget->setObjectName(u"mConfigureWidget"_s);
    addPage(configureGeneralWidgetPage);

    const QString modelAvailablePageName = i18nc("@title Preferences page name", "Available Models");
    auto configureModelWidgetPage = new KPageWidgetItem(mAvailableModelWidget, modelAvailablePageName);
    mAvailableModelWidget->setObjectName(u"mAvailableModelWidget"_s);
    addPage(configureModelWidgetPage);

    connect(buttonBox(), &QDialogButtonBox::accepted, this, &GenericNetworkConfigureDialog::slotAccepted);
    readConfig();
}

GenericNetworkConfigureDialog::~GenericNetworkConfigureDialog()
{
    writeConfig();
}

void GenericNetworkConfigureDialog::slotAccepted()
{
    mConfigureWidget->saveSettings();
    accept();
}

void GenericNetworkConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myGenericNetworkConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void GenericNetworkConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myGenericNetworkConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_genericnetworkconfiguredialog.cpp"
