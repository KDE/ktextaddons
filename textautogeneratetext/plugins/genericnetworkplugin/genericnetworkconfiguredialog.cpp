/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkconfiguredialog.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
const char myGenericNetworkConfigureDialogGroupName[] = "GenericNetworkConfigureDialog";
}
GenericNetworkConfigureDialog::GenericNetworkConfigureDialog(QWidget *parent)
    : KPageDialog(parent)
{
    // TODO update title
    setWindowTitle(i18nc("@title:window", "Configure"));
    setFaceType(KPageDialog::List);

    connect(buttonBox(), &QDialogButtonBox::accepted, this, &GenericNetworkConfigureDialog::slotAccepted);
    readConfig();
}

GenericNetworkConfigureDialog::~GenericNetworkConfigureDialog()
{
    writeConfig();
}

void GenericNetworkConfigureDialog::slotAccepted()
{
    // TODO mOllamaConfigureWidget->saveSettings();
    accept();
}

void GenericNetworkConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myGenericNetworkConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void GenericNetworkConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myGenericNetworkConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}
