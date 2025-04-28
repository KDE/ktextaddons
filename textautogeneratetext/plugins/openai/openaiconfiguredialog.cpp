/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openaiconfiguredialog.h"
#include "openaiconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

#include <KSharedConfig>
#include <KWindowConfig>
#include <QWindow>

namespace
{
const char myOpenAIConfigureDialogGroupName[] = "OpenAIConfigureDialog";
}
OpenAIConfigureDialog::OpenAIConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mOpenaiConfigureWidget(new OpenAIConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Openai IA"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &OpenAIConfigureDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &OpenAIConfigureDialog::reject);
    readConfig();
}

OpenAIConfigureDialog::~OpenAIConfigureDialog()
{
    writeConfig();
}

void OpenAIConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOpenAIConfigureDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void OpenAIConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOpenAIConfigureDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}
#include "moc_openaiconfiguredialog.cpp"
