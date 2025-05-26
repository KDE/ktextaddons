/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfowidget.h"
#include "ollamamanager.h"
#include "ollamamodelavailableinfosmodel.h"
#include "ollamamodeldownloadwidget.h"
#include <QLabel>
#include <QVBoxLayout>

OllamaModelInfoWidget::OllamaModelInfoWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mMainLayout(new QVBoxLayout(this))
    , mModelName(new QLabel(this))
{
    mMainLayout->setObjectName(QStringLiteral("mainlayout"));
    mMainLayout->setContentsMargins({});
    mMainLayout->addWidget(mModelName);
    QFont f = mModelName->font();
    f.setBold(true);
    mModelName->setFont(f);
}

OllamaModelInfoWidget::~OllamaModelInfoWidget() = default;

void OllamaModelInfoWidget::generateWidget(const QModelIndex &index)
{
    if (mDownloadWidget) {
        mMainLayout->removeWidget(mDownloadWidget);
        mDownloadWidget->deleteLater();
    }
    const QString modelName = index.data(OllamaModelAvailableInfosModel::ModelName).toString();
    mModelName->setText(modelName);

    const QList<OllamaModelAvailableInfo::ModelTag> tags = index.data(OllamaModelAvailableInfosModel::Tags).value<QList<OllamaModelAvailableInfo::ModelTag>>();
    delete mDownloadWidget;
    mDownloadWidget = new QWidget(this);
    auto downloadLayout = new QVBoxLayout(mDownloadWidget);
    for (const auto &t : tags) {
        auto downLoadWidget = new OllamaModelDownloadWidget(t.tag, t.size, mDownloadWidget);
        connect(downLoadWidget, &OllamaModelDownloadWidget::downloadModel, this, [this, modelName](const QString &tagName) {
            Q_EMIT downloadModel(QStringLiteral("%1:%2").arg(modelName, tagName));
        });
        downloadLayout->addWidget(downLoadWidget);
    }
    mMainLayout->addWidget(mDownloadWidget, 1, Qt::AlignTop);
}

#include "moc_ollamamodelinfowidget.cpp"
