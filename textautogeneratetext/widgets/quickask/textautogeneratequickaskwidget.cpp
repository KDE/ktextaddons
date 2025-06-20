/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskwidget.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogeneratemanager.h"

#include "core/textautogeneratetextinstancesmanager.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratequickaskviewwidget.h"
#include "textautogeneratetextwidget_debug.h"
#include "widgets/common/textautogeneratenotinstancefoundwidget.h"
#include "widgets/common/textautogeneratenotworkingwidget.h"
#include <QStackedWidget>
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
TextAutoGenerateQuickAskWidget::TextAutoGenerateQuickAskWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mStackedWidget(new QStackedWidget(this))
    , mTextAutoGenerateQuickAskViewWidget(new TextAutoGenerateQuickAskViewWidget(manager, this))
    , mTextAutoGenerateNotWorkingWidget(new TextAutoGenerateNotWorkingWidget(manager, this))
    , mTextAutoGenerateNotInstanceFoundWidget(new TextAutoGenerateNotInstanceFoundWidget(this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mStackedWidget->setObjectName(QStringLiteral("mStackedWidget"));
    mainLayout->addWidget(mStackedWidget);

    mTextAutoGenerateQuickAskViewWidget->setObjectName(QStringLiteral("mTextAutoGenerateQuickAskViewWidget"));
    mStackedWidget->addWidget(mTextAutoGenerateQuickAskViewWidget);

    mTextAutoGenerateNotWorkingWidget->setObjectName(QStringLiteral("mTextAutoGenerateNotWorkingWidget"));
    mStackedWidget->addWidget(mTextAutoGenerateNotWorkingWidget);

    mTextAutoGenerateNotInstanceFoundWidget->setObjectName(QStringLiteral("mTextAutoGenerateNotInstanceFoundWidget"));
    mStackedWidget->addWidget(mTextAutoGenerateNotInstanceFoundWidget);

    connect(mTextAutoGenerateNotInstanceFoundWidget, &TextAutoGenerateNotInstanceFoundWidget::addInstanceRequested, this, [this]() {
        mTextAutoGenerateQuickAskViewWidget->slotConfigureInstances();
    });

    mStackedWidget->setCurrentWidget(mTextAutoGenerateQuickAskViewWidget);

    connect(mTextAutoGenerateNotWorkingWidget, &TextAutoGenerateNotWorkingWidget::ollamaStarted, this, [this]() {
        mStackedWidget->setCurrentWidget(mTextAutoGenerateQuickAskViewWidget);
    });
    connect(mTextAutoGenerateQuickAskViewWidget,
            &TextAutoGenerateQuickAskViewWidget::editingFinished,
            this,
            &TextAutoGenerateQuickAskWidget::slotEditingFinished);

    connect(mTextAutoGenerateQuickAskViewWidget,
            &TextAutoGenerateQuickAskViewWidget::cancelRequested,
            this,
            &TextAutoGenerateQuickAskWidget::slotCancelRequest);

    connect(mTextAutoGenerateQuickAskViewWidget, &TextAutoGenerateQuickAskViewWidget::configureChanged, this, [this]() {
        if (mManager->textAutoGenerateTextInstancesManager()->isEmpty()) {
            mStackedWidget->setCurrentWidget(mTextAutoGenerateNotInstanceFoundWidget);
        } else {
            mStackedWidget->setCurrentWidget(mTextAutoGenerateQuickAskViewWidget);
        }
    });
    connect(mTextAutoGenerateQuickAskViewWidget,
            &TextAutoGenerateQuickAskViewWidget::refreshAnswerRequested,
            this,
            &TextAutoGenerateQuickAskWidget::slotRefreshAnswer);

    if (mManager) {
        mManager->setSaveInDatabase(false);
    }
    loadEngine();
}

TextAutoGenerateQuickAskWidget::~TextAutoGenerateQuickAskWidget() = default;

void TextAutoGenerateQuickAskWidget::slotCancelRequest(const QByteArray &uuid)
{
    mManager->textAutoGeneratePlugin()->cancelRequest(uuid);
}

void TextAutoGenerateQuickAskWidget::slotRefreshAnswer(const QByteArray &chatId, const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    const QString messageStr = index.data(TextAutoGenerateMessagesModel::OriginalMessageRole).toString();
    mManager->textAutoGeneratePlugin()->editMessage(chatId, uuid, messageStr);
}

void TextAutoGenerateQuickAskWidget::loadEngine()
{
    if (mManager) {
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::pluginsInitializedDone, this, &TextAutoGenerateQuickAskWidget::slotInitializeDone);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::errorOccured, this, &TextAutoGenerateQuickAskWidget::slotAutogenerateFailed);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::needToAddInstances, this, &TextAutoGenerateQuickAskWidget::slotNeedToAddInstances);
        mManager->loadEngine();
    }
}

void TextAutoGenerateQuickAskWidget::slotNeedToAddInstances()
{
    mStackedWidget->setCurrentWidget(mTextAutoGenerateNotInstanceFoundWidget);
}

void TextAutoGenerateQuickAskWidget::slotAutogenerateFailed(const QString &str)
{
    mTextAutoGenerateNotWorkingWidget->setMessageError(str);
    mStackedWidget->setCurrentWidget(mTextAutoGenerateNotWorkingWidget);
}

void TextAutoGenerateQuickAskWidget::slotInitializeDone()
{
    mPluginWasInitialized = true;
    for (const auto &str : std::as_const(mAskMessageList)) {
        slotEditingFinished(str, {});
    }
    mAskMessageList.clear();
}

void TextAutoGenerateQuickAskWidget::slotEditingFinished(const QString &str, const QByteArray &uuid)
{
    mManager->checkCurrentChat();
    if (uuid.isEmpty()) {
        mManager->textAutoGeneratePlugin()->sendMessage(mManager->currentChatId(), str);
    } else {
        mManager->textAutoGeneratePlugin()->editMessage(mManager->currentChatId(), uuid, str);
    }
    // mTextAutoGenerateResultWidget->editingFinished(uuid);
}

#include "moc_textautogeneratequickaskwidget.cpp"
