/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodeldownloadfromnamedialog.h"
using namespace Qt::Literals::StringLiterals;

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
    mainLayout->setObjectName(u"mainLayout"_s);
    mOllamaModelDownloadFromNameWidget->setObjectName(u"mOllamaModelDownloadFromNameWidget"_s);
    mainLayout->addWidget(mOllamaModelDownloadFromNameWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(u"box"_s);
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
