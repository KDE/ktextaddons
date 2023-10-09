/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskenginedialog.h"
#include "voskenginelanguagewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
static const char myConfigGroupName[] = "VoskEngineDialog";
}

VoskEngineDialog::VoskEngineDialog(QWidget *parent)
    : QDialog(parent)
    , mVoskEngineWidget(new VoskEngineLanguageWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Bergamot Plugin Settings"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mVoskEngineWidget->setObjectName(QStringLiteral("mVoskEngineWidget"));
    mainLayout->addWidget(mVoskEngineWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &VoskEngineDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &VoskEngineDialog::reject);
    readConfig();
}

VoskEngineDialog::~VoskEngineDialog()
{
    writeConfig();
}

void VoskEngineDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void VoskEngineDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(500, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}
