/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadprogresswidget.h"
#include "ollamamanager.h"
#include "ollamareply.h"
#include <KLocalizedString>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
OllamaModelDownloadProgressWidget::OllamaModelDownloadProgressWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mProgressBar(new QProgressBar(this))
    , mModelName(new QLabel(this))
    , mProgressStatusLabel(new QLabel(this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mModelName->setObjectName(QStringLiteral("mModelName"));
    mainLayout->addWidget(mModelName);

    mProgressStatusLabel->setObjectName(QStringLiteral("mProgressStatusLabel"));
    mainLayout->addWidget(mProgressStatusLabel);

    mProgressBar->setObjectName(QStringLiteral("mProgressBar"));
    mainLayout->addWidget(mProgressBar);
    mProgressBar->setRange(0, 100);

    auto cancelDownload = new QPushButton(i18n("Cancel"), this);
    cancelDownload->setObjectName(QStringLiteral("cancelDownload"));
    mainLayout->addWidget(cancelDownload);
    connect(cancelDownload, &QPushButton::clicked, this, [this]() {
        // TODO
    });
    if (mManager) {
        connect(mManager, &OllamaManager::downloadInProgress, this, &OllamaModelDownloadProgressWidget::slotDownloadProgressInfo);
    }
    mainLayout->addStretch(1);
}

OllamaModelDownloadProgressWidget::~OllamaModelDownloadProgressWidget() = default;

void OllamaModelDownloadProgressWidget::downloadModel(const QString &url)
{
    qDebug() << " downloadModel " << url;
    auto reply = mManager->downloadModel(url);
    // TODO reply->
}

void OllamaModelDownloadProgressWidget::slotDownloadProgressInfo(const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info)
{
    // qDebug() << "info " << info;
    mProgressStatusLabel->setText(info.status);
    if (info.total != 0) {
        mProgressBar->setValue(info.completed * 100 / info.total);
    }
}

#include "moc_ollamamodeldownloadprogresswidget.cpp"
