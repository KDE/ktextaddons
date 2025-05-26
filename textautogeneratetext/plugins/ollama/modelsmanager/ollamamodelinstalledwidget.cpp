/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledwidget.h"
#include "ollamamanager.h"
#include "ollamamodelinstalledinfosmodel.h"
#include "ollamamodelinstalledlistview.h"
#include "ollamamodelsearchlineedit.h"
#include <KLocalizedString>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>
OllamaModelInstalledWidget::OllamaModelInstalledWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mOllamaModelInstalledListView(new OllamaModelInstalledListView(this))
    , mSearchLineEdit(new OllamaModelSearchLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    mainLayout->addWidget(mSearchLineEdit);

    mOllamaModelInstalledListView->setObjectName(QStringLiteral("mOllamaModelInstalledListView"));
    mainLayout->addWidget(mOllamaModelInstalledListView);

    auto model = new OllamaModelInstalledInfosModel(this);
    if (manager) {
        connect(manager, &OllamaManager::modelsLoadDone, this, [model, manager]() {
            model->setModelInstalledInfos(manager->installedInfos());
        });
    }
    auto proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    connect(mSearchLineEdit, &OllamaModelSearchLineEdit::textChanged, this, [this, proxyModel](const QString &str) {
        proxyModel->setFilterFixedString(str);
    });
    mOllamaModelInstalledListView->setModel(proxyModel);
}

OllamaModelInstalledWidget::~OllamaModelInstalledWidget() = default;

#include "moc_ollamamodelinstalledwidget.cpp"
