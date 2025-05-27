/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodeldownloadfromnamedialog.h"
#include "ollamamodeldownloadfromnamewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
OllamaModelDownloadFromNameDialog::OllamaModelDownloadFromNameDialog(QWidget *parent)
    : QDialog(parent)
    , mOllamaModelDownloadFromNameWidget(new OllamaModelDownloadFromNameWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Download Model"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mOllamaModelDownloadFromNameWidget->setObjectName(QStringLiteral("mOllamaModelDownloadFromNameWidget"));

    auto box = new QDialogButtonBox(QDialogButtonBox::Close, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &OllamaModelDownloadFromNameDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &OllamaModelDownloadFromNameDialog::reject);
}

OllamaModelDownloadFromNameDialog::~OllamaModelDownloadFromNameDialog() = default;
