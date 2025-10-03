/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledwidget.h"

#include "ollamamanager.h"
#include "ollamamodelinstalledinfosmodel.h"
#include "ollamamodelinstalledinfossortproxymodel.h"
#include "ollamamodelinstalledinfowidget.h"
#include "ollamamodelinstalledlistview.h"
#include "ollamamodelsinfoscategoriescombobox.h"

#include "widgets/common/textautogeneratemodelsearchlineedit.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QScrollArea>
#include <QSortFilterProxyModel>
#include <QSplitter>
#include <QToolButton>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
OllamaModelInstalledWidget::OllamaModelInstalledWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mOllamaModelInstalledListView(new OllamaModelInstalledListView(this))
    , mSearchLineEdit(new TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit(this))
    , mCategoriesComboBox(new OllamaModelsInfosCategoriesComboBox(this))
    , mRemoveModelButton(new QToolButton(this))
    , mOllamaModelInstalledInfoWidget(new OllamaModelInstalledInfoWidget(this))
    , mManager(manager)
    , mProxyModel(new OllamaModelInstalledInfosSortProxyModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setObjectName(u"hboxLayout"_s);
    hboxLayout->setContentsMargins({});
    hboxLayout->setSpacing(0);
    mainLayout->addLayout(hboxLayout);

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    hboxLayout->addWidget(mSearchLineEdit);

    mCategoriesComboBox->setObjectName(u"mCategoriesComboBox"_s);
    hboxLayout->addWidget(mCategoriesComboBox);
    connect(mCategoriesComboBox, &OllamaModelsInfosCategoriesComboBox::categoriesChanged, this, [this]() {
        mProxyModel->setCategories(mCategoriesComboBox->categories());
    });

    auto splitter = new QSplitter(this);
    splitter->setObjectName(u"splitter"_s);
    mainLayout->addWidget(splitter);
    splitter->setChildrenCollapsible(false);

    mOllamaModelInstalledListView->setObjectName(u"mOllamaModelInstalledListView"_s);
    splitter->addWidget(mOllamaModelInstalledListView);

    auto scrollArea = new QScrollArea(this);
    scrollArea->setObjectName(u"scrollArea"_s);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    splitter->addWidget(scrollArea);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(mOllamaModelInstalledInfoWidget);
    mOllamaModelInstalledInfoWidget->setObjectName(u"mOllamaModelInstalledInfoWidget"_s);

    auto model = new OllamaModelInstalledInfosModel(this);
    if (mManager) {
        connect(mManager, &OllamaManager::modelsLoadDone, this, [model, this]() {
            model->setModelInstalledInfos(mManager->installedInfos());
        });
    }
    mProxyModel->setSourceModel(model);
    mProxyModel->sort(0);
    connect(mSearchLineEdit, &TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit::textChanged, this, [this](const QString &str) {
        mProxyModel->setFilterFixedString(str);
    });
    mOllamaModelInstalledListView->setModel(mProxyModel);

    mRemoveModelButton->setObjectName(u"mRemoveModelButton"_s);
    mRemoveModelButton->setEnabled(false);
    mRemoveModelButton->setToolTip(i18nc("@info:tooltip", "Remove Selected Model"));
    scrollArea->hide();
    hboxLayout->addWidget(mRemoveModelButton);
    mRemoveModelButton->setIcon(QIcon::fromTheme(u"edit-delete"_s));
    connect(mRemoveModelButton, &QToolButton::clicked, this, &OllamaModelInstalledWidget::slotRemoveModel);
    connect(mOllamaModelInstalledListView, &OllamaModelInstalledListView::pressed, this, &OllamaModelInstalledWidget::slotClicked);
    connect(mOllamaModelInstalledListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this, scrollArea]() {
        const bool isEnabled = mOllamaModelInstalledListView->currentIndex().isValid();
        mRemoveModelButton->setEnabled(isEnabled);
        scrollArea->setVisible(isEnabled);
    });
}

OllamaModelInstalledWidget::~OllamaModelInstalledWidget() = default;

void OllamaModelInstalledWidget::slotClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        const OllamaModelInstalledInfo info = index.data(OllamaModelInstalledInfosModel::DescriptionInfo).value<OllamaModelInstalledInfo>();
        mOllamaModelInstalledInfoWidget->setOllamaModelInstalledInfo(info);
    }
}

void OllamaModelInstalledWidget::slotRemoveModel()
{
    const auto currentIndex = mOllamaModelInstalledListView->currentIndex();
    if (currentIndex.isValid()) {
        const QString modelGeneratedName = currentIndex.data(OllamaModelInstalledInfosModel::ModelGeneratedName).toString();
        if (KMessageBox::warningTwoActions(this,
                                           i18n("Do you want to remove this model (%1)?", modelGeneratedName),
                                           i18nc("@title", "Remove Model"),
                                           KStandardGuiItem::remove(),
                                           KStandardGuiItem::cancel())
            == KMessageBox::PrimaryAction) {
            if (mManager) {
                const QString modelName = currentIndex.data(OllamaModelInstalledInfosModel::OriginalName).toString();
                mManager->deleteModel(modelName);
                // mRemoveModelButton->setEnabled(false); // TODO verify it.
            }
        }
    }
}

#include "moc_ollamamodelinstalledwidget.cpp"
