/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginelanguagewidget.h"
#include "managermodeltranslator.h"
#include "translatormodel.h"
#include <KLocalizedString>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

BergamotEngineLanguageWidget::BergamotEngineLanguageWidget(QWidget *parent)
    : QWidget{parent}
    , mTreeView(new QTreeView(this))
    , mTranslatorModel(new TranslatorModel(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mTreeView->setObjectName(QStringLiteral("mTreeView"));
    mTranslatorModel->insertTranslators(ManagerModelTranslator::self()->translators());
    mTreeView->setModel(mTranslatorModel);
    mainLayout->addWidget(mTreeView);

    auto buttonLayout = new QVBoxLayout;
    buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
    mainLayout->addLayout(buttonLayout);

    auto downLoadLanguage = new QPushButton(i18n("Download"), this);
    downLoadLanguage->setObjectName(QStringLiteral("downLoadLanguage"));
    buttonLayout->addWidget(downLoadLanguage);

    auto deleteLanguage = new QPushButton(i18n("Delete"), this);
    deleteLanguage->setObjectName(QStringLiteral("downLoadLanguage"));
    buttonLayout->addWidget(deleteLanguage, 1);
    // TODO enable/disable it.
}

BergamotEngineLanguageWidget::~BergamotEngineLanguageWidget() = default;

#include "moc_bergamotenginelanguagewidget.cpp"
