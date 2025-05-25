/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>

OllamaModelDownloadWidget::OllamaModelDownloadWidget(const QString &tagName, const QString &modelSize, QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto labelTag = new QLabel(tagName, this);
    labelTag->setObjectName(QStringLiteral("labelTag"));
    mainLayout->addWidget(labelTag);

    auto labelSize = new QLabel(modelSize, this);
    labelSize->setObjectName(QStringLiteral("labelSize"));
    mainLayout->addWidget(labelSize);

    auto toolButton = new QToolButton(this);
    toolButton->setIcon(QIcon::fromTheme(QStringLiteral("download")));
    toolButton->setAutoRaise(true);
    toolButton->setObjectName(QStringLiteral("toolButton"));
    mainLayout->addWidget(toolButton);
    connect(toolButton, &QToolButton::clicked, this, [this, tagName]() {
        Q_EMIT downloadModel(tagName);
    });
}

OllamaModelDownloadWidget::~OllamaModelDownloadWidget() = default;

#include "moc_ollamamodeldownloadwidget.cpp"
