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
    , mModelNameLabel(new QLabel(this))
    , mProgressStatusLabel(new QLabel(this))
    , mManager(manager)
    , mCancelDownloadButton(new QPushButton(i18n("Cancel"), this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mModelNameLabel->setObjectName(QStringLiteral("mModelNameLabel"));
    mainLayout->addWidget(mModelNameLabel, 0, Qt::AlignHCenter);

    mProgressStatusLabel->setObjectName(QStringLiteral("mProgressStatusLabel"));
    mainLayout->addWidget(mProgressStatusLabel, 0, Qt::AlignHCenter);

    mProgressBar->setObjectName(QStringLiteral("mProgressBar"));
    mainLayout->addWidget(mProgressBar);
    mProgressBar->setRange(0, 100);

    mCancelDownloadButton->setObjectName(QStringLiteral("mCancelDownloadButton"));
    mainLayout->addWidget(mCancelDownloadButton);
    connect(mCancelDownloadButton, &QPushButton::clicked, this, [this]() {
        // TODO
    });
    if (mManager) {
        connect(mManager, &OllamaManager::downloadInProgress, this, &OllamaModelDownloadProgressWidget::slotDownloadProgressInfo);
        connect(mManager, &OllamaManager::downloadDone, this, [this] {
            mCancelDownloadButton->hide();
        });
    }
    mainLayout->addStretch(1);
}

OllamaModelDownloadProgressWidget::~OllamaModelDownloadProgressWidget() = default;

void OllamaModelDownloadProgressWidget::downloadModel(const QString &modelName)
{
    mModelName = modelName;
    mModelNameLabel->setText(modelName);
    qDebug() << " downloadModel " << modelName;
    auto reply = mManager->downloadModel(modelName);
    mCancelDownloadButton->show();
    // TODO reply->
}

void OllamaModelDownloadProgressWidget::slotDownloadProgressInfo(const QString &modelName,
                                                                 const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info)
{
    if (modelName == mModelName) {
        // qDebug() << "info " << info;
        mProgressStatusLabel->setText(info.status);
        if (info.total != 0) {
            mProgressBar->setValue(info.completed * 100 / info.total);
        }
    }
}

#include "moc_ollamamodeldownloadprogresswidget.cpp"
