/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratenotworkingwidget.h"

#include "core/textautogeneratetextplugin.h"
#include "textautogeneratenotworkingmessagewidget.h"
#include "textautogeneratetextwidget_debug.h"
#include <KLocalizedString>
#include <QProcess>
#include <QPushButton>
#include <QVBoxLayout>
#include <TextAddonsWidgets/ExecutableUtils>
#include <TextAutoGenerateText/TextAutoGenerateManager>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateNotWorkingWidget::TextAutoGenerateNotWorkingWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mMessageWidget(new TextAutoGenerateNotWorkingMessageWidget(this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mMessageWidget->setObjectName("mMessageWidget"_L1);
    mainLayout->addWidget(mMessageWidget, 0, Qt::AlignTop);

    mainLayout->addStretch(1);
    auto configureButton = new QPushButton(i18nc("@action:button", "Configure…"), this);
    configureButton->setObjectName("configureButton"_L1);
    configureButton->setToolTip(i18nc("@info:tooltip", "Configure Instance"));
    connect(configureButton, &QPushButton::clicked, this, &TextAutoGenerateNotWorkingWidget::configureInstances);
    mainLayout->addWidget(configureButton, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    mainLayout->addStretch(1);
    // TODO configure from activate instance
    connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::ollamaProcessOk, this, [this](bool state) {
        if (state) {
            clearMessage();
            Q_EMIT ollamaStarted();
        }
    });
    connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::ollamaFailed, this, []() {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Ollama doesn't exist";
    });
}

TextAutoGenerateNotWorkingWidget::~TextAutoGenerateNotWorkingWidget() = default;

void TextAutoGenerateNotWorkingWidget::setMessageError(const QString &str)
{
    mMessageWidget->addAction(mManager->textAutoGeneratePlugin()->activateInstanceAction().action);
    mMessageWidget->setMessageInfo(str);
    mMessageWidget->animatedShow();
}

void TextAutoGenerateNotWorkingWidget::clearMessage()
{
    mMessageWidget->setText({});
    mMessageWidget->animatedHide();
}

#include "moc_textautogeneratenotworkingwidget.cpp"
