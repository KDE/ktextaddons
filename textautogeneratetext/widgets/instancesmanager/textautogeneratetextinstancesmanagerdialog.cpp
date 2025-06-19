/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancesmanagerdialog.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <qwindow.h>
namespace
{
const char myTextAutoGenerateTextInstancesManagerDialogGroupName[] = "TextAutoGenerateTextInstancesManagerDialog";
}
using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManagerDialog::TextAutoGenerateTextInstancesManagerDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure Instances"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    auto button = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this);
    button->setObjectName(QStringLiteral("button"));
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGenerateTextInstancesManagerDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGenerateTextInstancesManagerDialog::accept);
    readConfig();
}

TextAutoGenerateTextInstancesManagerDialog::~TextAutoGenerateTextInstancesManagerDialog()
{
    writeConfig();
}

void TextAutoGenerateTextInstancesManagerDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateTextInstancesManagerDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void TextAutoGenerateTextInstancesManagerDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myTextAutoGenerateTextInstancesManagerDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}
