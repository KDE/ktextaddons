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
    mMainLayout->addStretch(1);
    QFont f = mModelName->font();
    f.setBold(true);
    mModelName->setFont(f);
}

OllamaModelInfoWidget::~OllamaModelInfoWidget() = default;

void OllamaModelInfoWidget::generateWidget(const QModelIndex &index)
{
    mModelName->setText(index.data(OllamaModelInfosModel::ModelName).toString());
}

#include "moc_ollamamodelinfowidget.cpp"
