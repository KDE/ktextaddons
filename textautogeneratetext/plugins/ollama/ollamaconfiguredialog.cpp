/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaconfiguredialog.h"
#include "modelsmanager/ollamamodelavailablewidget.h"
#include "modelsmanager/ollamamodelinstalledwidget.h"
#include "ollamaconfigurewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
const char myOllamaConfigureDialogGroupName[] = "OllamaConfigureDialog";
}

OllamaConfigureDialog::OllamaConfigureDialog(OllamaManager *manager, QWidget *parent)
    : KPageDialog(parent)
    , mOllamaConfigureWidget(new OllamaConfigureWidget(manager, this))
    , mOllamaModelWidget(new OllamaModelAvailableWidget(manager, this))
    , mOllamaModelInstalledWidget(new OllamaModelInstalledWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Ollama"));
    setFaceType(KPageDialog::List);

    const QString generalPageName = i18nc("@title Preferences page name", "General");
    auto configureGeneralWidgetPage = new KPageWidgetItem(mOllamaConfigureWidget, generalPageName);
    mOllamaConfigureWidget->setObjectName(QStringLiteral("mOllamaConfigureWidget"));
    // configureGeneralWidgetPage->setIcon(QIcon::fromTheme(QStringLiteral("ruqola")));
    addPage(configureGeneralWidgetPage);

    const QString modelAvailablePageName = i18nc("@title Preferences page name", "Available Models");
    auto configureModelWidgetPage = new KPageWidgetItem(mOllamaModelWidget, modelAvailablePageName);
    mOllamaModelWidget->setObjectName(QStringLiteral("mOllamaModelWidget"));
    // configureGeneralWidgetPage->setIcon(QIcon::fromTheme(QStringLiteral("ruqola")));
    addPage(configureModelWidgetPage);

    const QString modelInstalledPageName = i18nc("@title Preferences page name", "Installed Models");
    auto configureModelInstalledWidgetPage = new KPageWidgetItem(mOllamaModelInstalledWidget, modelInstalledPageName);
    mOllamaModelInstalledWidget->setObjectName(QStringLiteral("mOllamaModelInstalledWidget"));
    // configureGeneralWidgetPage->setIcon(QIcon::fromTheme(QStringLiteral("ruqola")));
    addPage(configureModelInstalledWidgetPage);

    connect(buttonBox(), &QDialogButtonBox::accepted, this, &OllamaConfigureDialog::slotAccepted);
    readConfig();
}

OllamaConfigureDialog::~OllamaConfigureDialog()
{
    writeConfig();
}

void OllamaConfigureDialog::slotAccepted()
{
    mOllamaConfigureWidget->saveSettings();
    accept();
}

void OllamaConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void OllamaConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_ollamaconfiguredialog.cpp"
