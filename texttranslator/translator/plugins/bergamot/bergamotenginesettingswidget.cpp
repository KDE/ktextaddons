/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "bergamotenginesettingswidget.h"
#include <KLocalizedString>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>

BergamotEngineSettingsWidget::BergamotEngineSettingsWidget(QWidget *parent)
    : QWidget{parent}
    , mNumberThreads(new QComboBox(this))
    , mMemoryByThreads(new QComboBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    auto resourceBox = new QGroupBox(i18n("Resource Usage"), this);
    resourceBox->setObjectName(QStringLiteral("resourceBox"));
    mainLayout->addWidget(resourceBox);

    mNumberThreads->setObjectName(QStringLiteral("mNumberThreads"));
    mMemoryByThreads->setObjectName(QStringLiteral("mMemoryByThreads"));

    auto formLayout = new QFormLayout;
    formLayout->setObjectName(QStringLiteral("formLayout"));
    resourceBox->setLayout(formLayout);
    formLayout->addRow(i18n("Thread:"), mNumberThreads);
    formLayout->addRow(i18n("Memory by Thread:"), mMemoryByThreads);
}

BergamotEngineSettingsWidget::~BergamotEngineSettingsWidget() = default;

#include "moc_bergamotenginesettingswidget.cpp"
