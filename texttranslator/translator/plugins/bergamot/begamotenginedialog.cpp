/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "begamotenginedialog.h"
#include "bergamotenginewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myConfigGroupName[] = "BegamotEngineDialog";
}
BegamotEngineDialog::BegamotEngineDialog(QWidget *parent)
    : QDialog(parent)
    , mBergamotEngineWidget(new BergamotEngineWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Bergamot Plugin Settings"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mBergamotEngineWidget->setObjectName(QStringLiteral("mBergamotEngineWidget"));
    mainLayout->addWidget(mBergamotEngineWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(QStringLiteral("button"));
    mainLayout->addWidget(button);
    readConfig();
}

BegamotEngineDialog::~BegamotEngineDialog()
{
    writeConfig();
}

void BegamotEngineDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void BegamotEngineDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(500, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

#include "moc_begamotenginedialog.cpp"
