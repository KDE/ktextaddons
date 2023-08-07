/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginelanguagewidget.h"
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

#if QT_VERSION < QT_VERSION_CHECK(6, 4, 0)
#include <TextAddonsWidgets/LineEditCatchReturnKey>
#else
#include <KLineEditEventHandler>
#endif

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
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::errorText, this, &BergamotEngineLanguageWidget::slotError);
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::progress, this, &BergamotEngineLanguageWidget::slotProgressInfo);
    mTranslatorModel->insertTranslators(ManagerModelTranslator::self()->translators());

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

    auto downLoadLanguage = new QPushButton(i18n("Download"), this);
    downLoadLanguage->setObjectName(QStringLiteral("downLoadLanguage"));
    buttonLayout->addWidget(downLoadLanguage);
    connect(downLoadLanguage, &QPushButton::clicked, this, [this]() {
        QString url;
        // TODO
        slotDownLoad(url);
    });

    auto deleteLanguage = new QPushButton(i18n("Delete"), this);
    deleteLanguage->setObjectName(QStringLiteral("downLoadLanguage"));
    buttonLayout->addWidget(deleteLanguage);
    connect(deleteLanguage, &QPushButton::clicked, this, &BergamotEngineLanguageWidget::slotDelete);

    auto updateListLanguage = new QPushButton(i18n("Update"), this);
    updateListLanguage->setObjectName(QStringLiteral("updateListLanguage"));
    buttonLayout->addWidget(updateListLanguage, 1);
    connect(updateListLanguage, &QPushButton::clicked, this, &BergamotEngineLanguageWidget::slotUpdateListLanguage);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &BergamotEngineLanguageWidget::slotTextChanged);
    connect(mTreeView, &QTreeView::clicked, this, &BergamotEngineLanguageWidget::slotClicked);
    // TODO enable/disable it.

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

    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::extractDone, this, &BergamotEngineLanguageWidget::updateListModel);
    connect(ManagerModelTranslator::self(), &ManagerModelTranslator::downLoadModelListDone, this, &BergamotEngineLanguageWidget::updateListModel);
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

void BergamotEngineLanguageWidget::slotClicked(const QModelIndex &index)
{
    // TODO
}

void BergamotEngineLanguageWidget::slotError(const QString &str)
{
    KMessageBox::error(this, i18n("Error: %1", str), i18n("Bergamot"));
}

void BergamotEngineLanguageWidget::slotTextChanged(const QString &str)
{
    mTranslatorProxyModel->setSearchString(str);
}

void BergamotEngineLanguageWidget::slotDownLoad(const QString &url)
{
    ManagerModelTranslator::self()->downloadLanguage(url);
}

void BergamotEngineLanguageWidget::slotDelete()
{
    // TODO
    // ManagerModelTranslator::self()->removeLanguage(...)
    updateListModel();
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
