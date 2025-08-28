/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadprogresswidget.h"
using namespace Qt::Literals::StringLiterals;

#include "ollamamanager.h"
#include "ollamareply.h"
#include <KLocalizedString>
#include <QLabel>
#include <QProgressBar>
#include <QToolButton>
#include <QVBoxLayout>
OllamaModelDownloadProgressWidget::OllamaModelDownloadProgressWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mProgressBar(new QProgressBar(this))
    , mModelNameLabel(new QLabel(this))
    , mProgressStatusLabel(new QLabel(this))
    , mManager(manager)
    , mCancelDownloadButton(new QToolButton(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mModelNameLabel->setObjectName(u"mModelNameLabel"_s);
    QFont f = mModelNameLabel->font();
    f.setBold(true);
    mModelNameLabel->setFont(f);

    mainLayout->addWidget(mModelNameLabel, 0, Qt::AlignHCenter);

    mProgressStatusLabel->setObjectName(u"mProgressStatusLabel"_s);
    mainLayout->addWidget(mProgressStatusLabel, 0, Qt::AlignHCenter);

    auto hboxLayout = new QHBoxLayout;
    mainLayout->addLayout(hboxLayout);

    mProgressBar->setObjectName(u"mProgressBar"_s);
    hboxLayout->addWidget(mProgressBar);
    mProgressBar->setRange(0, 100);

    mCancelDownloadButton->setObjectName(u"mCancelDownloadButton"_s);
    mCancelDownloadButton->setIcon(QIcon::fromTheme(u"dialog-cancel"_s));
    mCancelDownloadButton->setToolTip(i18nc("@info:tooltip", "Cancel"));
    mCancelDownloadButton->setFocusPolicy(Qt::NoFocus);
    hboxLayout->addWidget(mCancelDownloadButton);
    connect(mCancelDownloadButton, &QToolButton::clicked, this, [this]() {
        if (OllamaReply *value = mDownloadReply.take(mModelNameLabel->text()); value) {
            value->cancel();
        }
    });
    if (mManager) {
        connect(mManager, &OllamaManager::downloadInProgress, this, &OllamaModelDownloadProgressWidget::slotDownloadProgressInfo);
        connect(mManager, &OllamaManager::downloadDone, this, [this](const QString &modelName) {
            if (modelName == mModelName) {
                mCancelDownloadButton->hide();
                mDownloadReply.remove(modelName);
            }
        });
    }
    mainLayout->addStretch(1);
}

OllamaModelDownloadProgressWidget::~OllamaModelDownloadProgressWidget() = default;

void OllamaModelDownloadProgressWidget::downloadModel(const QString &modelName)
{
    mModelName = modelName;
    mModelNameLabel->setText(modelName);
    // qDebug() << " downloadModel " << modelName;
    auto reply = mManager->downloadModel(modelName);
    mDownloadReply.insert(modelName, reply);
    mCancelDownloadButton->show();
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
