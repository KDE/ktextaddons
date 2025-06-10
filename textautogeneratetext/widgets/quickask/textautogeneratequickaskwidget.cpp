/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskwidget.h"
#include "core/textautogenerateengineutil.h"
#include "core/textautogeneratemanager.h"

#include "core/textautogeneratetextplugin.h"
#include "textautogeneratequickaskviewwidget.h"
#include "textautogeneratetextwidget_debug.h"
#include "widgets/common/textautogeneratenotworkingwidget.h"
#include <QStackedWidget>
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
TextAutoGenerateQuickAskWidget::TextAutoGenerateQuickAskWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mStackedWidget(new QStackedWidget(this))
    , mTextAutoGenerateQuickAskViewWidget(new TextAutoGenerateQuickAskViewWidget(manager, this))
    , mTextAutoGenerateNotWorkingWidget(new TextAutoGenerateNotWorkingWidget(manager, this))
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
    mStackedWidget->setCurrentWidget(mTextAutoGenerateQuickAskViewWidget);

    connect(mTextAutoGenerateNotWorkingWidget, &TextAutoGenerateNotWorkingWidget::ollamaStarted, this, [this]() {
        mStackedWidget->setCurrentWidget(mTextAutoGenerateQuickAskViewWidget);
    });
    connect(mTextAutoGenerateQuickAskViewWidget,
            &TextAutoGenerateQuickAskViewWidget::editingFinished,
            this,
            &TextAutoGenerateQuickAskWidget::slotEditingFinished);

    if (mManager) {
        mManager->setSaveInDatabase(false);
    }
    loadEngine();
}

TextAutoGenerateQuickAskWidget::~TextAutoGenerateQuickAskWidget() = default;

void TextAutoGenerateQuickAskWidget::loadEngine()
{
    if (mManager) {
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::pluginsInitializedDone, this, &TextAutoGenerateQuickAskWidget::slotInitializeDone);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::errorOccured, this, &TextAutoGenerateQuickAskWidget::slotAutogenerateFailed);
        mManager->loadEngine();
        if (!mManager->textAutoGenerateClient()) {
            qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to create client" << TextAutoGenerateEngineUtil::loadEngine();
        }
    }
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
