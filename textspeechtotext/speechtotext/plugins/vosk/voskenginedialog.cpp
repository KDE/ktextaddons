/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskenginedialog.h"
using namespace Qt::Literals::StringLiterals;

#include "voskenginelanguagewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>

namespace
{
const char myConfigGroupName[] = "VoskEngineDialog";
}

VoskEngineDialog::VoskEngineDialog(QWidget *parent)
    : QDialog(parent)
    , mVoskEngineWidget(new VoskEngineLanguageWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Vosk Plugin Settings"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mVoskEngineWidget->setObjectName(u"mVoskEngineWidget"_s);
    mainLayout->addWidget(mVoskEngineWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(u"buttonBox"_s);
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &VoskEngineDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &VoskEngineDialog::reject);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myConfigGroupName), QSize(500, 300));
}

VoskEngineDialog::~VoskEngineDialog() = default;

#include "moc_voskenginedialog.cpp"
