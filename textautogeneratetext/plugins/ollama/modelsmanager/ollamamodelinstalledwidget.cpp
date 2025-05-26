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
#include <QToolButton>
#include <QVBoxLayout>
OllamaModelInstalledWidget::OllamaModelInstalledWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mOllamaModelInstalledListView(new OllamaModelInstalledListView(this))
    , mSearchLineEdit(new OllamaModelSearchLineEdit(this))
    , mRemoveModelButton(new QToolButton(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
    hboxLayout->setContentsMargins({});
    hboxLayout->setSpacing(0);
    mainLayout->addLayout(hboxLayout);

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    hboxLayout->addWidget(mSearchLineEdit);

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
    connect(mSearchLineEdit, &OllamaModelSearchLineEdit::textChanged, this, [proxyModel](const QString &str) {
        proxyModel->setFilterFixedString(str);
    });
    mOllamaModelInstalledListView->setModel(proxyModel);

    mRemoveModelButton->setObjectName(QStringLiteral("mRemoveModelButton"));
    hboxLayout->addWidget(mRemoveModelButton);
    mRemoveModelButton->setIcon(QIcon::fromTheme(QStringLiteral("edit-delete")));
    connect(mRemoveModelButton, &QToolButton::clicked, this, &OllamaModelInstalledWidget::slotRemoveModel);
}

OllamaModelInstalledWidget::~OllamaModelInstalledWidget() = default;

void OllamaModelInstalledWidget::slotRemoveModel()
{
    const auto currentIndex = mOllamaModelInstalledListView->currentIndex();
    if (currentIndex.isValid()) {
        // TODO update
    }
}

#include "moc_ollamamodelinstalledwidget.cpp"
