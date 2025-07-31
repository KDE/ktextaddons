/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;

#include "modelsmanager/ollamamodelavailableinfosmanager.h"
#include "modelsmanager/ollamamodelavailablewidget.h"
#include "modelsmanager/ollamamodelcreatewidget.h"
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
    , mOllamaModelInstalledWidget(new OllamaModelInstalledWidget(manager, this))
    , mOllamaModelCreateWidget(new OllamaModelCreateWidget(manager, this))
{
    setWindowTitle(i18nc("@title:window", "Configure Ollama"));
    setFaceType(KPageDialog::List);

    connect(mOllamaConfigureWidget, &OllamaConfigureWidget::ollamaProcessOk, this, [this](bool status) {
        mOllamaModelCreateWidget->setEnabled(status);
        mOllamaModelWidget->setEnabled(status);
        mOllamaModelInstalledWidget->setEnabled(status);
    });

    OllamaModelAvailableInfosManager managerModelInfosManager;
    if (managerModelInfosManager.loadAvailableModels()) {
        mOllamaModelWidget->setAvailableInfos(managerModelInfosManager.modelInfos());
        mOllamaModelInstalledWidget->setAvailableInfos(managerModelInfosManager.modelInfos());
    }

    const QString generalPageName = i18nc("@title Preferences page name", "General");
    auto configureGeneralWidgetPage = new KPageWidgetItem(mOllamaConfigureWidget, generalPageName);
    mOllamaConfigureWidget->setObjectName(u"mOllamaConfigureWidget"_s);
    // configureGeneralWidgetPage->setIcon(QIcon::fromTheme(u"ruqola"_s));
    addPage(configureGeneralWidgetPage);

    const QString modelAvailablePageName = i18nc("@title Preferences page name", "Available Models");
    auto configureModelWidgetPage = new KPageWidgetItem(mOllamaModelWidget, modelAvailablePageName);
    mOllamaModelWidget->setObjectName(u"mOllamaModelWidget"_s);
    // configureGeneralWidgetPage->setIcon(QIcon::fromTheme(u"ruqola"_s));
    addPage(configureModelWidgetPage);

    const QString modelInstalledPageName = i18nc("@title Preferences page name", "Installed Models");
    auto configureModelInstalledWidgetPage = new KPageWidgetItem(mOllamaModelInstalledWidget, modelInstalledPageName);
    mOllamaModelInstalledWidget->setObjectName(u"mOllamaModelInstalledWidget"_s);
    // configureGeneralWidgetPage->setIcon(QIcon::fromTheme(u"ruqola"_s));
    addPage(configureModelInstalledWidgetPage);

    const QString modelCreatePageName = i18nc("@title Preferences page name", "Create Models");
    auto configureModelCreateWidgetPage = new KPageWidgetItem(mOllamaModelCreateWidget, modelCreatePageName);
    mOllamaModelCreateWidget->setObjectName(u"mOllamaModelCreateWidget"_s);
    // configureGeneralWidgetPage->setIcon(QIcon::fromTheme(u"ruqola"_s));
    addPage(configureModelCreateWidgetPage);

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
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void OllamaConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_ollamaconfiguredialog.cpp"
