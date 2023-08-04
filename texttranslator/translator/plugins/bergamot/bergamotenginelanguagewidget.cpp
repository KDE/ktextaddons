/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginelanguagewidget.h"
#include "managermodeltranslator.h"
#include "translatormodel.h"
#include "translatorproxymodel.h"
#include <KLocalizedString>
#include <QLineEdit>
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
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto vboxLayout = new QVBoxLayout;
    vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
    vboxLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(QStringLiteral("mSearchLineEdit"));
    vboxLayout->addWidget(mSearchLineEdit);
    mSearchLineEdit->setPlaceholderText(i18n("Search..."));

#if QT_VERSION < QT_VERSION_CHECK(6, 4, 0)
    new TextAddonsWidgets::LineEditCatchReturnKey(mSearchLineEdit, this);
#else
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
#endif

    mTreeView->setObjectName(QStringLiteral("mTreeView"));
    mTranslatorModel->insertTranslators(ManagerModelTranslator::self()->translators());
    auto proxyModel = new TranslatorProxyModel(this);
    proxyModel->setSourceModel(mTranslatorModel);
    mTreeView->setModel(proxyModel);
    mTreeView->setRootIsDecorated(false);
    mTreeView->setSortingEnabled(true);
    vboxLayout->addWidget(mTreeView);

    mainLayout->addLayout(vboxLayout);

    auto buttonLayout = new QVBoxLayout;
    buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
    mainLayout->addLayout(buttonLayout);

    auto downLoadLanguage = new QPushButton(i18n("Download"), this);
    downLoadLanguage->setObjectName(QStringLiteral("downLoadLanguage"));
    buttonLayout->addWidget(downLoadLanguage);
    connect(downLoadLanguage, &QPushButton::clicked, this, &BergamotEngineLanguageWidget::slotDownLoad);

    auto deleteLanguage = new QPushButton(i18n("Delete"), this);
    deleteLanguage->setObjectName(QStringLiteral("downLoadLanguage"));
    buttonLayout->addWidget(deleteLanguage, 1);
    connect(deleteLanguage, &QPushButton::clicked, this, &BergamotEngineLanguageWidget::slotDelete);

    auto updateListLanguage = new QPushButton(i18n("Update"), this);
    updateListLanguage->setObjectName(QStringLiteral("updateListLanguage"));
    buttonLayout->addWidget(updateListLanguage, 1);
    connect(updateListLanguage, &QPushButton::clicked, this, &BergamotEngineLanguageWidget::slotUpdateListLanguage);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &BergamotEngineLanguageWidget::slotTextChanged);
    // TODO enable/disable it.
}

BergamotEngineLanguageWidget::~BergamotEngineLanguageWidget() = default;

void BergamotEngineLanguageWidget::slotTextChanged(const QString &str)
{
    // TODO
}

void BergamotEngineLanguageWidget::slotDownLoad()
{
    // TODO
}

void BergamotEngineLanguageWidget::slotDelete()
{
    // TODO
}

void BergamotEngineLanguageWidget::slotUpdateListLanguage()
{
    // TODO
}

#include "moc_bergamotenginelanguagewidget.cpp"
