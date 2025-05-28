/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodeldownloadfromnamedialog.h"
#include "ollamamodeldownloadfromnamewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
OllamaModelDownloadFromNameDialog::OllamaModelDownloadFromNameDialog(QWidget *parent)
    : QDialog(parent)
    , mOllamaModelDownloadFromNameWidget(new OllamaModelDownloadFromNameWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Download Model"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mOllamaModelDownloadFromNameWidget->setObjectName(QStringLiteral("mOllamaModelDownloadFromNameWidget"));
    mainLayout->addWidget(mOllamaModelDownloadFromNameWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &OllamaModelDownloadFromNameDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &OllamaModelDownloadFromNameDialog::reject);
    auto okButton = box->button(QDialogButtonBox::Ok);
    okButton->setEnabled(false);
    connect(mOllamaModelDownloadFromNameWidget, &OllamaModelDownloadFromNameWidget::textChanged, this, [okButton](const QString &str) {
        // TODO verify that str is name:tag
        okButton->setEnabled(!str.trimmed().isEmpty());
    });
}

OllamaModelDownloadFromNameDialog::~OllamaModelDownloadFromNameDialog() = default;

QString OllamaModelDownloadFromNameDialog::modelName() const
{
    return mOllamaModelDownloadFromNameWidget->modelName();
}

#include "moc_ollamamodeldownloadfromnamedialog.cpp"
