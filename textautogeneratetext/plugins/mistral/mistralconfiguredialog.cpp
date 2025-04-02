/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralconfiguredialog.h"
#include "mistralconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

#include <KSharedConfig>
#include <KWindowConfig>
#include <QWindow>

namespace
{
const char myMistralConfigureDialogGroupName[] = "MistralConfigureDialog";
}
MistralConfigureDialog::MistralConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mMistralConfigureWidget(new MistralConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Mistral IA"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &MistralConfigureDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &MistralConfigureDialog::reject);
    readConfig();
}

MistralConfigureDialog::~MistralConfigureDialog()
{
    writeConfig();
}

void MistralConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myMistralConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void MistralConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myMistralConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}
#include "moc_mistralconfiguredialog.cpp"
