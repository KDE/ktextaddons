/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaonlineconfiguredialog.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QWindow>
namespace
{
const char myOllamaOnlineConfigureDialogGroupName[] = "OllamaOnlineConfigureDialog";
}

using namespace Qt::Literals::StringLiterals;
OllamaOnlineConfigureDialog::OllamaOnlineConfigureDialog(QWidget *parent)
    : KPageDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure Ollama Online"));

    readConfig();
}

OllamaOnlineConfigureDialog::~OllamaOnlineConfigureDialog()
{
    writeConfig();
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
