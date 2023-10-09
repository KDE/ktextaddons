/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskenginelanguagewidget.h"
// #include "libbergamot_debug.h"
// #include "translatormodel.h"
// #include "translatorproxymodel.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

#if QT_VERSION < QT_VERSION_CHECK(6, 4, 0)
#include <TextAddonsWidgets/LineEditCatchReturnKey>
#else
#include <KLineEditEventHandler>
#endif

VoskEngineLanguageWidget::VoskEngineLanguageWidget(QWidget *parent)
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
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
    hboxLayout->setContentsMargins({});
    mainLayout->addLayout(hboxLayout);

    auto vboxLayout = new QVBoxLayout;
    vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
    vboxLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    vboxLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setPlaceholderText(i18n("Search..."));
    mSearchLineEdit->setClearButtonEnabled(true);

#if QT_VERSION < QT_VERSION_CHECK(6, 4, 0)
    new TextAddonsWidgets::LineEditCatchReturnKey(mSearchLineEdit, this);
#else
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
#endif

    mTreeView->setObjectName(QStringLiteral("mTreeView"));
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::errorText, this, &VoskEngineLanguageWidget::slotError);
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::progress, this, &VoskEngineLanguageWidget::slotProgressInfo);
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::extractDone, mTranslatorModel, &TranslatorModel::updateInstalledLanguage);
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::downLoadModelListDone, this, &VoskEngineLanguageWidget::updateListModel);

    // TODO store list on local.
    if (ManagerModelTranslator::self()->needDownloadModelList()) {
        ManagerModelTranslator::self()->downloadListModels();
    } else {
        mTranslatorModel->insertTranslators(ManagerModelTranslator::self()->translators());
    }

    mTranslatorProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    mTranslatorProxyModel->setSourceModel(mTranslatorModel);
    mTreeView->setModel(mTranslatorProxyModel);
    mTreeView->setRootIsDecorated(false);
    mTreeView->setSortingEnabled(true);
    vboxLayout->addWidget(mTreeView);

    hboxLayout->addLayout(vboxLayout);

    auto buttonLayout = new QVBoxLayout;
    buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
    hboxLayout->addLayout(buttonLayout);

    auto downLoadLanguage = new QPushButton(QIcon::fromTheme(QStringLiteral("download-symbolic")), i18n("Download"), this);
    downLoadLanguage->setObjectName(QStringLiteral("downLoadLanguage"));
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

    auto deleteLanguage = new QPushButton(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Delete"), this);
    deleteLanguage->setObjectName(QStringLiteral("downLoadLanguage"));
    buttonLayout->addWidget(deleteLanguage);

    auto updateListLanguage = new QPushButton(i18n("Update List"), this);
    updateListLanguage->setToolTip(i18n("Update list of languages from network"));
    updateListLanguage->setObjectName(QStringLiteral("updateListLanguage"));
    buttonLayout->addWidget(updateListLanguage);
    buttonLayout->addStretch(1); // spacer
    connect(updateListLanguage, &QPushButton::clicked, this, &VoskEngineLanguageWidget::slotUpdateListLanguage);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &VoskEngineLanguageWidget::slotTextChanged);

    auto progressBarLayout = new QHBoxLayout;
    progressBarLayout->setObjectName(QStringLiteral("progressBarLayout"));

    mProgressBarLabel->setObjectName(QStringLiteral("mProgressBarLabel"));
    progressBarLayout->addWidget(mProgressBarLabel);

    mProgressBar->setObjectName(QStringLiteral("mProgressBar"));
    progressBarLayout->addWidget(mProgressBar);

    mProgressBarWidget->setObjectName(QStringLiteral("mProgressBarWidget"));
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

VoskEngineLanguageWidget::~VoskEngineLanguageWidget() = default;

void VoskEngineLanguageWidget::slotProgressInfo(const ManagerModelVoskSpeechToText::ProgressInfo &info)
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

void VoskEngineLanguageWidget::slotError(const QString &str)
{
    KMessageBox::error(this, i18n("Error: %1", str), i18n("Bergamot"));
}

void VoskEngineLanguageWidget::slotTextChanged(const QString &str)
{
    mTranslatorProxyModel->setSearchString(str);
}

void VoskEngineLanguageWidget::slotDownLoad(const QString &url, const QString &checkSum)
{
    ManagerModelVoskSpeechToText::self()->downloadLanguage(url, checkSum);
}

void VoskEngineLanguageWidget::slotDelete(const QString &identifier)
{
    mTranslatorModel->removeLanguage(identifier);
}

void VoskEngineLanguageWidget::slotUpdateListLanguage()
{
    ManagerModelVoskSpeechToText::self()->downloadListModels();
}

void VoskEngineLanguageWidget::updateListModel()
{
    mTranslatorModel->insertTranslators(ManagerModelVoskSpeechToText::self()->translators());
}

#include "moc_bergamotenginelanguagewidget.cpp"
