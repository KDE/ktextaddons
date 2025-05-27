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
#include <KMessageBox>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QToolButton>
#include <QVBoxLayout>
OllamaModelInstalledWidget::OllamaModelInstalledWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mOllamaModelInstalledListView(new OllamaModelInstalledListView(this))
    , mSearchLineEdit(new OllamaModelSearchLineEdit(this))
    , mRemoveModelButton(new QToolButton(this))
    , mManager(manager)
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
    if (mManager) {
        connect(mManager, &OllamaManager::modelsLoadDone, this, [model, this]() {
            model->setModelInstalledInfos(mManager->installedInfos());
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
        if (KMessageBox::warningTwoActions(this,
                                           i18n("Do you want to remove this model?"),
                                           i18nc("@title", "Remove Model"),
                                           KStandardGuiItem::remove(),
                                           KStandardGuiItem::cancel())
            == KMessageBox::PrimaryAction) {
            if (mManager) {
                mManager->deleteModel(currentIndex.data(OllamaModelInstalledInfosModel::ModelName).toString());
                // TODO update list
            }
        }
    }
}

#include "moc_ollamamodelinstalledwidget.cpp"
