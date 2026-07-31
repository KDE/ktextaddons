/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailabledialog.h"

#include "ollamamanager.h"
#include "ollamamodelavailablewidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
namespace
{
const char myOllamaModelDialogGroupName[] = "OllamaModelAvailableDialog";
}
using namespace Qt::Literals::StringLiterals;
OllamaModelAvailableDialog::OllamaModelAvailableDialog(OllamaManager *manager, QWidget *parent)
    : QDialog(parent)
    , mOllamaModelWidget(new OllamaModelAvailableWidget(manager, this))
{
    setWindowTitle(i18nc("@title:window", "Manage Ollama Models"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mOllamaModelWidget->setObjectName(u"mOllamaModelWidget"_s);

    if (manager) {
        mOllamaModelWidget->setAvailableInfos(manager->availableInfos());
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
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myOllamaModelDialogGroupName), 400, 300);
}

void OllamaModelAvailableDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myOllamaModelDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_ollamamodelavailabledialog.cpp"
