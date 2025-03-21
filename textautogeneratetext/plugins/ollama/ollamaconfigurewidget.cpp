/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaconfigurewidget.h"

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>

OllamaConfigureWidget::OllamaConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mServerUrl(new QLineEdit(this))
    , mPrompt(new QPlainTextEdit(this))
    , mModelComboBox(new QComboBox(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mServerUrl->setObjectName(QStringLiteral("mServerUrl"));
    KLineEditEventHandler::catchReturnKey(mServerUrl);
    mainLayout->addRow(i18n("Server Url:"), mServerUrl);
    // TODO add setPlaceHolder

    mModelComboBox->setObjectName(QStringLiteral("mModelComboBox"));
    mainLayout->addRow(i18n("Model:"), mModelComboBox);

    mPrompt->setObjectName(QStringLiteral("mPrompt"));
    mainLayout->addRow(i18n("Prompt:"), mPrompt);
    // TODO add setPlaceHolder

    // TODO fill model

    loadSettings();
}

OllamaConfigureWidget::~OllamaConfigureWidget() = default;

void OllamaConfigureWidget::loadSettings()
{
}

void OllamaConfigureWidget::saveSettings()
{
}

#include "moc_ollamaconfigurewidget.cpp"
