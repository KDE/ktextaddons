/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaonlineconfiguredialog.h"
#include "autogeneratetext_ollamaonline_debug.h"
#include "ollamacommonmodelavailableinfosmanager.h"
#include "ollamacommonmodelavailablewidget.h"
#include "ollamacommonmodelutils.h"
#include "ollamaonlineconfigurewidget.h"
#include "ollamaonlinemanager.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QPushButton>
#include <QWindow>
namespace
{
const char myOllamaOnlineConfigureDialogGroupName[] = "OllamaOnlineConfigureDialog";
}

using namespace Qt::Literals::StringLiterals;
OllamaOnlineConfigureDialog::OllamaOnlineConfigureDialog(OllamaOnlineManager *manager, QWidget *parent)
    : KPageDialog(parent)
    , mOllamaOnlineConfigureWidget(new OllamaOnlineConfigureWidget(manager, this))
    , mOllamaOnlineModelWidget(new OllamaCommonModelAvailableWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Ollama Online"));
    setFaceType(KPageDialog::List);

    const QString generalPageName = i18nc("@title Preferences page name", "General");
    auto configureGeneralWidgetPage = new KPageWidgetItem(mOllamaOnlineConfigureWidget, generalPageName);
    configureGeneralWidgetPage->setIcon(QIcon::fromTheme(u"://ollama-general-model"_s));
    mOllamaOnlineConfigureWidget->setObjectName(u"mOllamaConfigureWidget"_s);
    addPage(configureGeneralWidgetPage);

    const QString modelAvailablePageName = i18nc("@title Preferences page name", "Available Models");
    auto configureModelWidgetPage = new KPageWidgetItem(mOllamaOnlineModelWidget, modelAvailablePageName);
    configureModelWidgetPage->setIcon(QIcon::fromTheme(u"://ollama-available-models"_s));
    mOllamaOnlineModelWidget->setObjectName(u"mOllamaOnlineModelWidget"_s);
    if (manager) {
        connect(manager, &OllamaOnlineManager::modelsLoadDone, this, [this, manager](const OllamaOnlineManager::ModelsInfo &modelinfo) {
            // qDebug() << " OllamaConfigureWidget::fillModels() " << modelinfo;
            if (modelinfo.hasError) {
                qCWarning(AUTOGENERATETEXT_OLLAMAONLINE_LOG) << "load model failed";
            } else {
                const QList<OllamaCommonModelAvailableInfo> displayAvailablesModels = OllamaCommonModelUtils::extractAvailableModel(modelinfo);
                manager->setAvailableInfos(displayAvailablesModels);
                mOllamaOnlineModelWidget->setAvailableInfos(displayAvailablesModels);
            }
        });
    }
    addPage(configureModelWidgetPage);

    connect(buttonBox(), &QDialogButtonBox::accepted, this, &OllamaOnlineConfigureDialog::slotAccepted);

    readConfig();
    auto okButton = button(QDialogButtonBox::StandardButton::Ok);
    connect(mOllamaOnlineConfigureWidget, &OllamaOnlineConfigureWidget::enableOkButton, this, [okButton](bool state) {
        okButton->setEnabled(state);
    });
}

OllamaOnlineConfigureDialog::~OllamaOnlineConfigureDialog()
{
    writeConfig();
}

void OllamaOnlineConfigureDialog::slotAccepted()
{
    mOllamaOnlineConfigureWidget->saveSettings();
    accept();
}

void OllamaOnlineConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaOnlineConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void OllamaOnlineConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaOnlineConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_ollamaonlineconfiguredialog.cpp"
