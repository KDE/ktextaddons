/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "begamotenginedialog.h"
#include "bergamotenginewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

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
}

BegamotEngineDialog::~BegamotEngineDialog() = default;

#include "moc_begamotenginedialog.cpp"
