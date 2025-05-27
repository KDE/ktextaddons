/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadfromnamewidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QLineEdit>
#include <QVBoxLayout>

OllamaModelDownloadFromNameWidget::OllamaModelDownloadFromNameWidget(QWidget *parent)
    : QWidget{parent}
    , mModelNameLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mModelNameLineEdit->setObjectName(QStringLiteral("mModelNameLineEdit"));
    mainLayout->addWidget(mModelNameLineEdit);
    KLineEditEventHandler::catchReturnKey(mModelNameLineEdit);
}

OllamaModelDownloadFromNameWidget::~OllamaModelDownloadFromNameWidget() = default;

QString OllamaModelDownloadFromNameWidget::modelName() const
{
    return mModelNameLineEdit->text();
}

#include "moc_ollamamodeldownloadfromnamewidget.cpp"
