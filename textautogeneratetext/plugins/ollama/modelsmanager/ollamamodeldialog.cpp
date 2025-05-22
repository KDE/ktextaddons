/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldialog.h"

#include "ollamamodelwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
const char myOllamaModelDialogGroupName[] = "OllamaModelDialog";
}
OllamaModelDialog::OllamaModelDialog(QWidget *parent)
    : QDialog(parent)
    , mOllamaModelWidget(new OllamaModelWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Manage Ollama Models"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mOllamaModelWidget->setObjectName(QStringLiteral("mOllamaModelWidget"));

    auto box = new QDialogButtonBox(QDialogButtonBox::Close, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &OllamaModelDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &OllamaModelDialog::reject);
    readConfig();
}

OllamaModelDialog::~OllamaModelDialog()
{
    writeConfig();
}

void OllamaModelDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaModelDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void OllamaModelDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaModelDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_ollamamodeldialog.cpp"
