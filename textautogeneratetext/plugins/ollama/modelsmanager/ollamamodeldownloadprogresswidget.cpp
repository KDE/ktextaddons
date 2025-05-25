/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadprogresswidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>

OllamaModelDownloadProgressWidget::OllamaModelDownloadProgressWidget(QWidget *parent)
    : QWidget{parent}
    , mProgressBar(new QProgressBar(this))
    , mModelName(new QLabel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mModelName->setObjectName(QStringLiteral("mModelName"));
    mainLayout->addWidget(mModelName);

    mProgressBar->setObjectName(QStringLiteral("mProgressBar"));
    mainLayout->addWidget(mProgressBar);

    auto cancelDownload = new QPushButton(i18n("Cancel"), this);
    cancelDownload->setObjectName(QStringLiteral("cancelDownload"));
    mainLayout->addWidget(cancelDownload);
    connect(cancelDownload, &QPushButton::clicked, this, [this]() {
        // TODO
    });
    mainLayout->addStretch(1);
}

OllamaModelDownloadProgressWidget::~OllamaModelDownloadProgressWidget() = default;

#include "moc_ollamamodeldownloadprogresswidget.cpp"
