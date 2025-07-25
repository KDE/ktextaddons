/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginelanguagewidget.h"
using namespace Qt::Literals::StringLiterals;

#include "libbergamot_debug.h"
#include "translatormodel.h"
#include "translatorproxymodel.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

#include <KLineEditEventHandler>

BergamotEngineLanguageWidget::BergamotEngineLanguageWidget(QWidget *parent)
    : QWidget{parent}
    , mTreeView(new QTreeView(this))
    , mSearchLineEdit(new QLineEdit(this))
    , mTranslatorModel(new TranslatorModel(this))
    , mTranslatorProxyModel(new TranslatorProxyModel(this))
    , mProgressBar(new QProgressBar(this))
    , mProgressBarLabel(new QLabel(this))
    , mProgressBarWidget(new QWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setObjectName(u"hboxLayout"_s);
    hboxLayout->setContentsMargins({});
    mainLayout->addLayout(hboxLayout);

    auto vboxLayout = new QVBoxLayout;
    vboxLayout->setObjectName(u"vboxLayout"_s);
    vboxLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    vboxLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search…"));
    mSearchLineEdit->setClearButtonEnabled(true);

    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);

    mTreeView->setObjectName(u"mTreeView"_s);
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::errorText, this, &BergamotEngineLanguageWidget::slotError);
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::progress, this, &BergamotEngineLanguageWidget::slotProgressInfo);
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::extractDone, mTranslatorModel, &TranslatorModel::updateInstalledLanguage);
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::downLoadModelListDone, this, &BergamotEngineLanguageWidget::updateListModel);

    // TODO store list on local.
    if (ManagerModelTranslator::self()->needDownloadModelList()) {
        ManagerModelTranslator::self()->downloadListModels();
    } else {
        mTranslatorModel->insertTranslators(ManagerModelTranslator::self()->translators());
    }

    mTranslatorProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    mTranslatorProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mTranslatorProxyModel->setSourceModel(mTranslatorModel);
    mTreeView->setModel(mTranslatorProxyModel);
    mTreeView->setRootIsDecorated(false);
    mTreeView->setSortingEnabled(true);
    vboxLayout->addWidget(mTreeView);

    hboxLayout->addLayout(vboxLayout);

    auto buttonLayout = new QVBoxLayout;
    buttonLayout->setObjectName(u"buttonLayout"_s);
    hboxLayout->addLayout(buttonLayout);

    auto downLoadLanguage = new QPushButton(QIcon::fromTheme(u"download-symbolic"_s), i18n("Download"), this);
    downLoadLanguage->setObjectName(u"downLoadLanguage"_s);
    buttonLayout->addWidget(downLoadLanguage);
    connect(downLoadLanguage, &QPushButton::clicked, this, [this]() {
        const auto currentlySelectedIndex = mTranslatorProxyModel->mapToSource(mTreeView->selectionModel()->currentIndex());
        const QModelIndex modelIndex = mTranslatorModel->index(currentlySelectedIndex.row(), TranslatorModel::Url);
        const QModelIndex modelIndexCheckSum = mTranslatorModel->index(currentlySelectedIndex.row(), TranslatorModel::CheckSum);

        const QString url = modelIndex.data().toString();
        const QString checkSum = modelIndexCheckSum.data().toString();
        qCDebug(TRANSLATOR_LIBBERGAMOT_LOG) << " url " << url << " checksum " << checkSum;
        slotDownLoad(url, checkSum);
    });

    auto deleteLanguage = new QPushButton(QIcon::fromTheme(u"edit-delete"_s), i18n("Delete"), this);
    deleteLanguage->setObjectName(u"downLoadLanguage"_s);
    buttonLayout->addWidget(deleteLanguage);

    auto updateListLanguage = new QPushButton(i18nc("@action:button", "Update List"), this);
    updateListLanguage->setToolTip(i18nc("@info:tooltip", "Update list of languages from network"));
    updateListLanguage->setObjectName(u"updateListLanguage"_s);
    buttonLayout->addWidget(updateListLanguage);
    buttonLayout->addStretch(1); // spacer
    connect(updateListLanguage, &QPushButton::clicked, this, &BergamotEngineLanguageWidget::slotUpdateListLanguage);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &BergamotEngineLanguageWidget::slotTextChanged);

    auto progressBarLayout = new QHBoxLayout;
    progressBarLayout->setObjectName(u"progressBarLayout"_s);

    mProgressBarLabel->setObjectName(u"mProgressBarLabel"_s);
    progressBarLayout->addWidget(mProgressBarLabel);

    mProgressBar->setObjectName(u"mProgressBar"_s);
    progressBarLayout->addWidget(mProgressBar);

    mProgressBarWidget->setObjectName(u"mProgressBarWidget"_s);
    mProgressBarWidget->setLayout(progressBarLayout);

    mainLayout->addWidget(mProgressBarWidget);
    mProgressBarWidget->setVisible(false);

    mTreeView->setColumnHidden(TranslatorModel::Url, true);
    mTreeView->setColumnHidden(TranslatorModel::CheckSum, true);
    mTreeView->setColumnHidden(TranslatorModel::Identifier, true);
    mTreeView->setColumnHidden(TranslatorModel::NeedToUpdateLanguage, true);
    auto updateButton = [this, downLoadLanguage, deleteLanguage]() {
        const bool hasSelectedItem = mTreeView->currentIndex().isValid();
        const auto currentlySelectedIndex = mTranslatorProxyModel->mapToSource(mTreeView->selectionModel()->currentIndex());
        const QModelIndex modelIndex = mTranslatorModel->index(currentlySelectedIndex.row(), TranslatorModel::Installed);
        const QModelIndex modelIndexNeedToUpdate = mTranslatorModel->index(currentlySelectedIndex.row(), TranslatorModel::NeedToUpdateLanguage);
        const bool isInstalled = modelIndex.data().toBool();
        const bool needToUpdate = modelIndexNeedToUpdate.data().toBool();

        if (needToUpdate) {
            downLoadLanguage->setEnabled(hasSelectedItem && needToUpdate);
        } else {
            downLoadLanguage->setEnabled(hasSelectedItem && !isInstalled);
        }
        deleteLanguage->setEnabled(hasSelectedItem && isInstalled);
    };

    connect(deleteLanguage, &QPushButton::clicked, this, [this, updateButton]() {
        const auto currentlySelectedIndex = mTranslatorProxyModel->mapToSource(mTreeView->selectionModel()->currentIndex());
        const QModelIndex modelIndex = mTranslatorModel->index(currentlySelectedIndex.row(), TranslatorModel::Identifier);
        const QString identifier = modelIndex.data().toString();
        slotDelete(identifier);
        updateButton();
    });

    connect(mTreeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [updateButton]() {
        updateButton();
    });
    downLoadLanguage->setEnabled(false);
    deleteLanguage->setEnabled(false);
}

BergamotEngineLanguageWidget::~BergamotEngineLanguageWidget() = default;

void BergamotEngineLanguageWidget::slotProgressInfo(const ManagerModelTranslator::ProgressInfo &info)
{
    if (info.bytesReceived != info.bytesTotal) {
        mProgressBarWidget->setVisible(true);
    } else {
        mProgressBarWidget->setVisible(false);
    }
    mProgressBarLabel->setText(info.languageName);
    mProgressBar->setRange(0, 100);
    mProgressBar->setValue((info.bytesReceived * 100) / info.bytesTotal);
}

void BergamotEngineLanguageWidget::slotError(const QString &str)
{
    KMessageBox::error(this, i18n("Error: %1", str), i18n("Bergamot"));
}

void BergamotEngineLanguageWidget::slotTextChanged(const QString &str)
{
    mTranslatorProxyModel->setSearchString(str);
}

void BergamotEngineLanguageWidget::slotDownLoad(const QString &url, const QString &checkSum)
{
    ManagerModelTranslator::self()->downloadLanguage(url, checkSum);
}

void BergamotEngineLanguageWidget::slotDelete(const QString &identifier)
{
    mTranslatorModel->removeLanguage(identifier);
}

void BergamotEngineLanguageWidget::slotUpdateListLanguage()
{
    ManagerModelTranslator::self()->downloadListModels();
}

void BergamotEngineLanguageWidget::updateListModel()
{
    mTranslatorModel->insertTranslators(ManagerModelTranslator::self()->translators());
}

#include "moc_bergamotenginelanguagewidget.cpp"
