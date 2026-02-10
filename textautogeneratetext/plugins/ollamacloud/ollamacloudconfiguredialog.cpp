/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacloudconfiguredialog.h"
#include "ollamacloudconfigurewidget.h"
#include "ollamacloudmanager.h"
#include "ollamacommonmodelavailablewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QPushButton>
#include <QWindow>
namespace
{
const char myOllamaCloudConfigureDialogGroupName[] = "OllamaCloudConfigureDialog";
}

using namespace Qt::Literals::StringLiterals;
OllamaCloudConfigureDialog::OllamaCloudConfigureDialog(OllamaCloudManager *manager, QWidget *parent)
    : KPageDialog(parent)
    , mOllamaCloudConfigureWidget(new OllamaCloudConfigureWidget(manager, this))
    , mOllamaCloudModelWidget(new OllamaCommonModelAvailableWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Ollama Cloud"));
    setFaceType(KPageDialog::List);

    const QString generalPageName = i18nc("@title Preferences page name", "General");
    auto configureGeneralWidgetPage = new KPageWidgetItem(mOllamaCloudConfigureWidget, generalPageName);
    configureGeneralWidgetPage->setIcon(QIcon::fromTheme(u"://ollama-general-model"_s));
    mOllamaCloudConfigureWidget->setObjectName(u"mOllamaConfigureWidget"_s);
    addPage(configureGeneralWidgetPage);

    const QString modelAvailablePageName = i18nc("@title Preferences page name", "Available Models");
    auto configureModelWidgetPage = new KPageWidgetItem(mOllamaCloudModelWidget, modelAvailablePageName);
    configureModelWidgetPage->setIcon(QIcon::fromTheme(u"://ollama-available-models"_s));
    mOllamaCloudModelWidget->setObjectName(u"mOllamaCloudModelWidget"_s);
    addPage(configureModelWidgetPage);
    if (manager) {
        mOllamaCloudModelWidget->setAvailableInfos(manager->availableInfos());
    }
    connect(buttonBox(), &QDialogButtonBox::accepted, this, &OllamaCloudConfigureDialog::slotAccepted);

    readConfig();
    auto okButton = button(QDialogButtonBox::StandardButton::Ok);
    connect(mOllamaCloudConfigureWidget, &OllamaCloudConfigureWidget::enableOkButton, this, [okButton](bool state) {
        okButton->setEnabled(state);
    });
}

OllamaCloudConfigureDialog::~OllamaCloudConfigureDialog()
{
    writeConfig();
}

void OllamaCloudConfigureDialog::slotAccepted()
{
    mOllamaCloudConfigureWidget->saveSettings();
    accept();
}

void OllamaCloudConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    const KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaCloudConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void OllamaCloudConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaCloudConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_ollamacloudconfiguredialog.cpp"
