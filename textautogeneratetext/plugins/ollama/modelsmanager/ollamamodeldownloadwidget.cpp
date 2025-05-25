/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>

OllamaModelDownloadWidget::OllamaModelDownloadWidget(const QString &name, const QString &url, QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto label = new QLabel(name, this);
    label->setObjectName(QStringLiteral("label"));
    mainLayout->addWidget(label);

    auto toolButton = new QToolButton(this);
    toolButton->setIcon(QIcon::fromTheme(QStringLiteral("download")));
    toolButton->setAutoRaise(true);
    toolButton->setObjectName(QStringLiteral("toolButton"));
    mainLayout->addWidget(toolButton);
    connect(toolButton, &QToolButton::clicked, this, [this, url]() {
        Q_EMIT downloadModel(url);
    });
}

OllamaModelDownloadWidget::~OllamaModelDownloadWidget() = default;

#include "moc_ollamamodeldownloadwidget.cpp"
