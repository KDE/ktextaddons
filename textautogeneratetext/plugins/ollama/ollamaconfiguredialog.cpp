/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaconfiguredialog.h"
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

OllamaConfigureDialog::OllamaConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mOllamaConfigureWidget(new OllamaConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Ollama"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mOllamaConfigureWidget->setObjectName(QStringLiteral("mOllamaConfigureWidget"));
    mainLayout->addWidget(mOllamaConfigureWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &OllamaConfigureDialog::slotAccepted);
    connect(box, &QDialogButtonBox::rejected, this, &OllamaConfigureDialog::reject);
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
