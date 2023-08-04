/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginewidget.h"
#include "bergamotenginelanguagewidget.h"
#include "bergamotenginesettingswidget.h"
#include <KLocalizedString>
#include <QTabWidget>
#include <QVBoxLayout>

BergamotEngineWidget::BergamotEngineWidget(QWidget *parent)
    : QWidget{parent}
    , mTabWidget(new QTabWidget(this))
    , mLanguageWidget(new BergamotEngineLanguageWidget(this))
    , mSettingsWidget(new BergamotEngineSettingsWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mTabWidget->setObjectName(QStringLiteral("mTabWidget"));
    mainLayout->addWidget(mTabWidget);

    mLanguageWidget->setObjectName(QStringLiteral("mLanguageWidget"));
    mSettingsWidget->setObjectName(QStringLiteral("mSettingsWidget"));

    mTabWidget->addTab(mLanguageWidget, i18n("Languages"));
    mTabWidget->addTab(mSettingsWidget, i18n("Settings"));
}

BergamotEngineWidget::~BergamotEngineWidget() = default;

#include "moc_bergamotenginewidget.cpp"