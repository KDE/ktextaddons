/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "begamotenginedialog.h"
using namespace Qt::Literals::StringLiterals;

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
    mainLayout->setObjectName(u"mainLayout"_s);

    mBergamotEngineWidget->setObjectName(u"mBergamotEngineWidget"_s);
    mainLayout->addWidget(mBergamotEngineWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &BegamotEngineDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &BegamotEngineDialog::reject);
    readConfig();
}

BegamotEngineDialog::~BegamotEngineDialog()
{
    writeConfig();
}

void BegamotEngineDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void BegamotEngineDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(500, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(myConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void BegamotEngineDialog::setSettingsInfo(const BergamotEngineUtils::SettingsInfo &info)
{
    mBergamotEngineWidget->setSettingsInfo(info);
}

BergamotEngineUtils::SettingsInfo BegamotEngineDialog::settingsInfo() const
{
    return mBergamotEngineWidget->settingsInfo();
}

#include "moc_begamotenginedialog.cpp"
