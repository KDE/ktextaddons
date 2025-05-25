/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfowidget.h"
#include "ollamamodeldownloadwidget.h"
#include "ollamamodelinfosmodel.h"
#include <QLabel>
#include <QVBoxLayout>

OllamaModelInfoWidget::OllamaModelInfoWidget(QWidget *parent)
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
    mModelName->setText(index.data(OllamaModelInfosModel::ModelName).toString());

    const QList<OllamaModelInfo::ModelTag> tags = index.data(OllamaModelInfosModel::Tags).value<QList<OllamaModelInfo::ModelTag>>();
    delete mDownloadWidget;
    mDownloadWidget = new QWidget;
    auto downloadLayout = new QVBoxLayout(mDownloadWidget);
    for (const auto &t : tags) {
        downloadLayout->addWidget(new OllamaModelDownloadWidget(t.size, t.tag, mDownloadWidget));
    }
    mMainLayout->addWidget(mDownloadWidget, 0, Qt::AlignTop);
    mMainLayout->addStretch(1);
}

#include "moc_ollamamodelinfowidget.cpp"
