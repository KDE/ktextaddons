/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailableinfowidget.h"
#include "ollamamanager.h"
#include "ollamamodelavailableinfosmodel.h"
#include "ollamamodeldownloadwidget.h"
#include "ollamamodelflowlayout.h"
#include <KLocalizedString>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

OllamaModelAvailableInfoWidget::OllamaModelAvailableInfoWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mMainLayout(new QVBoxLayout(this))
    , mModelName(new QLabel(this))
    , mOllamaManager(manager)
{
    mMainLayout->setObjectName(QStringLiteral("mainlayout"));
    mMainLayout->setContentsMargins({});
    mMainLayout->addWidget(mModelName, 0, Qt::AlignHCenter);
    QFont f = mModelName->font();
    f.setBold(true);
    mModelName->setFont(f);
}

OllamaModelAvailableInfoWidget::~OllamaModelAvailableInfoWidget() = default;

void OllamaModelAvailableInfoWidget::generateWidget(const QModelIndex &index)
{
    if (mDownloadWidget) {
        mMainLayout->removeWidget(mDownloadWidget);
        mDownloadWidget->deleteLater();
    }
    const QString modelName = index.data(OllamaModelAvailableInfosModel::ModelName).toString();
    mModelName->setText(modelName);

    delete mDownloadWidget;
    mDownloadWidget = new QWidget(this);
    auto downloadLayout = new QVBoxLayout(mDownloadWidget);

    auto langugesGroupBox = new QGroupBox(i18n("Languages Supported"), mDownloadWidget);
    auto languagesGroupBoxLayout = new OllamaModelFlowLayout(langugesGroupBox);
    const QStringList languages = index.data(OllamaModelAvailableInfosModel::Languages).toStringList();
    for (const auto &l : languages) {
        const QLocale locale(l);
        languagesGroupBoxLayout->addWidget(new QLabel(QLocale::languageToString(locale.language()), mDownloadWidget));
    }
    downloadLayout->addWidget(langugesGroupBox);
    // TODO show categories

    auto downloadModelGroupBox = new QGroupBox(i18n("Models"), mDownloadWidget);

    downloadLayout->addWidget(downloadModelGroupBox);
    auto downloadGroupBoxLayout = new QVBoxLayout(downloadModelGroupBox);
    const QList<OllamaModelAvailableInfo::ModelTag> tags = index.data(OllamaModelAvailableInfosModel::Tags).value<QList<OllamaModelAvailableInfo::ModelTag>>();
    for (const auto &t : tags) {
        const bool alreadyInstalled = mOllamaManager->isAlreadyInstalled(QStringLiteral("%1:%2").arg(modelName, t.tag));
        auto downLoadWidget = new OllamaModelDownloadWidget(t.tag, t.size, alreadyInstalled, mDownloadWidget);
        connect(downLoadWidget, &OllamaModelDownloadWidget::downloadModel, this, [this, modelName](const QString &tagName) {
            Q_EMIT downloadModel(QStringLiteral("%1:%2").arg(modelName, tagName));
        });
        downloadGroupBoxLayout->addWidget(downLoadWidget);
    }
    mMainLayout->addWidget(mDownloadWidget, 1, Qt::AlignTop);
}

#include "moc_ollamamodelavailableinfowidget.cpp"
