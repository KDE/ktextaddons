/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledwidget.h"
#include "ollamamodelinstalledlistview.h"
#include <KLocalizedString>
#include <QVBoxLayout>
OllamaModelInstalledWidget::OllamaModelInstalledWidget(QWidget *parent)
    : QWidget{parent}
    , mOllamaModelInstalledListView(new OllamaModelInstalledListView(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mOllamaModelInstalledListView->setObjectName(QStringLiteral("mOllamaModelInstalledListView"));
    mainLayout->addWidget(mOllamaModelInstalledListView);
}

OllamaModelInstalledWidget::~OllamaModelInstalledWidget() = default;

#include "moc_ollamamodelinstalledwidget.cpp"
