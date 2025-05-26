/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledwidget.h"
#include "modelsmanager/ollamamodelinstalledinfosmodel.h"
#include "ollamamanager.h"
#include "ollamamodelinstalledlistview.h"
#include <KLocalizedString>
#include <QLineEdit>
#include <QVBoxLayout>
OllamaModelInstalledWidget::OllamaModelInstalledWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mOllamaModelInstalledListView(new OllamaModelInstalledListView(this))
    , mSearchLineEdit(new QLineEdit(this))
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
            qDebug() << "manager->installedInfos() " << manager->installedInfos();
            model->setModelInstalledInfos(manager->installedInfos());
        });
    }
    // mProxyModel->setSourceModel(model);
    // TODO fill model
    mOllamaModelInstalledListView->setModel(model);
}

OllamaModelInstalledWidget::~OllamaModelInstalledWidget() = default;

#include "moc_ollamamodelinstalledwidget.cpp"
