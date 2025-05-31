/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledwidget.h"
#include "ollamamanager.h"
#include "ollamamodelinstalledinfosmodel.h"
#include "ollamamodelinstalledinfowidget.h"
#include "ollamamodelinstalledlistview.h"
#include "ollamamodelsearchlineedit.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QLineEdit>
#include <QSortFilterProxyModel>
#include <QSplitter>
#include <QToolButton>
#include <QVBoxLayout>
OllamaModelInstalledWidget::OllamaModelInstalledWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mOllamaModelInstalledListView(new OllamaModelInstalledListView(this))
    , mSearchLineEdit(new OllamaModelSearchLineEdit(this))
    , mRemoveModelButton(new QToolButton(this))
    , mOllamaModelInstalledInfoWidget(new OllamaModelInstalledInfoWidget(this))
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

    auto splitter = new QSplitter(this);
    splitter->setObjectName(QStringLiteral("splitter"));
    mainLayout->addWidget(splitter);
    splitter->setChildrenCollapsible(false);

    mOllamaModelInstalledListView->setObjectName(QStringLiteral("mOllamaModelInstalledListView"));
    splitter->addWidget(mOllamaModelInstalledListView);

    mOllamaModelInstalledInfoWidget->setObjectName(QStringLiteral("mOllamaModelInstalledInfoWidget"));
    splitter->addWidget(mOllamaModelInstalledInfoWidget);

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
    mRemoveModelButton->setEnabled(false);
    hboxLayout->addWidget(mRemoveModelButton);
    mRemoveModelButton->setIcon(QIcon::fromTheme(QStringLiteral("edit-delete")));
    connect(mRemoveModelButton, &QToolButton::clicked, this, &OllamaModelInstalledWidget::slotRemoveModel);
    connect(mOllamaModelInstalledListView, &OllamaModelInstalledListView::clicked, this, &OllamaModelInstalledWidget::slotClicked);
    connect(mOllamaModelInstalledListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &OllamaModelInstalledWidget::slotCurrentChanged);
}

OllamaModelInstalledWidget::~OllamaModelInstalledWidget() = default;

void OllamaModelInstalledWidget::slotClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        const OllamaModelInstalledInfo info = index.data(OllamaModelInstalledInfosModel::DescriptionInfo).value<OllamaModelInstalledInfo>();
        mOllamaModelInstalledInfoWidget->setOllamaModelInstalledInfo(info, mModelAvailableInfos);
    }
}

void OllamaModelInstalledWidget::slotCurrentChanged()
{
    mRemoveModelButton->setEnabled(mOllamaModelInstalledListView->currentIndex().isValid());
}

void OllamaModelInstalledWidget::slotRemoveModel()
{
    const auto currentIndex = mOllamaModelInstalledListView->currentIndex();
    if (currentIndex.isValid()) {
        const QString modelName = currentIndex.data(OllamaModelInstalledInfosModel::ModelName).toString();
        if (KMessageBox::warningTwoActions(this,
                                           i18n("Do you want to remove this model (%1)?", modelName),
                                           i18nc("@title", "Remove Model"),
                                           KStandardGuiItem::remove(),
                                           KStandardGuiItem::cancel())
            == KMessageBox::PrimaryAction) {
            if (mManager) {
                mManager->deleteModel(modelName);
                // mRemoveModelButton->setEnabled(false); // TODO verify it.
            }
        }
    }
}

void OllamaModelInstalledWidget::setAvailableInfos(const QList<OllamaModelAvailableInfo> &infos)
{
    mModelAvailableInfos = infos;
}
#include "moc_ollamamodelinstalledwidget.cpp"
