/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailabledialog.h"
using namespace Qt::Literals::StringLiterals;

#include "ollamamanager.h"
#include "ollamamodelavailableinfosmanager.h"
#include "ollamamodelavailablewidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
const char myOllamaModelDialogGroupName[] = "OllamaModelAvailableDialog";
}
OllamaModelAvailableDialog::OllamaModelAvailableDialog(OllamaManager *manager, QWidget *parent)
    : QDialog(parent)
    , mOllamaModelWidget(new OllamaModelAvailableWidget(manager, this))
{
    setWindowTitle(i18nc("@title:window", "Manage Ollama Models"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mOllamaModelWidget->setObjectName(u"mOllamaModelWidget"_s);

    OllamaModelAvailableInfosManager managerModelInfosManager;
    if (managerModelInfosManager.loadAvailableModels()) {
        mOllamaModelWidget->setAvailableInfos(managerModelInfosManager.modelInfos());
    }

    auto box = new QDialogButtonBox(QDialogButtonBox::Close, this);
    box->setObjectName(u"box"_s);
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &OllamaModelAvailableDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &OllamaModelAvailableDialog::reject);
    readConfig();
}

OllamaModelAvailableDialog::~OllamaModelAvailableDialog()
{
    writeConfig();
}

void OllamaModelAvailableDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaModelDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void OllamaModelAvailableDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaModelDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_ollamamodelavailabledialog.cpp"
