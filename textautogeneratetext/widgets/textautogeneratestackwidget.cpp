/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratestackwidget.h"

#include "common/textautogeneratenotworkingwidget.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "textautogeneratewidget.h"
#include "widgets/common/textautogeneratenotinstancefoundwidget.h"
#include "widgets/instancesmanager/textautogeneratetextinstancesmanagerdialog.h"

#include <QStackedWidget>
#include <QTimer>
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateStackWidget::TextAutoGenerateStackWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mStackedWidget(new QStackedWidget(this))
    , mTextAutoGenerateNotWorkingWidget(new TextAutoGenerateNotWorkingWidget(manager, this))
    , mTextAutoGenerateNotInstanceFoundWidget(new TextAutoGenerateNotInstanceFoundWidget(this))
    , mTextAutoGenerateWidget(new TextAutoGenerateWidget(manager, this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mainLayout->addWidget(mStackedWidget);
    mTextAutoGenerateNotWorkingWidget->setObjectName(u"mTextAutoGenerateNotWorkingWidget"_s);
    mStackedWidget->addWidget(mTextAutoGenerateNotWorkingWidget);

    mTextAutoGenerateNotInstanceFoundWidget->setObjectName(u"mTextAutoGenerateNotInstanceFoundWidget"_s);
    mStackedWidget->addWidget(mTextAutoGenerateNotInstanceFoundWidget);

    mTextAutoGenerateWidget->setObjectName(u"mTextAutoGenerateWidget"_s);
    mStackedWidget->addWidget(mTextAutoGenerateWidget);
    mStackedWidget->setCurrentWidget(mTextAutoGenerateWidget);

    connect(mTextAutoGenerateWidget, &TextAutoGenerateWidget::noPluginsFound, this, [this](const QString &msg) {
        setBrokenEngine(true, msg);
    });
    connect(mTextAutoGenerateWidget, &TextAutoGenerateWidget::pluginBroken, this, [this](const QString &msg) {
        setBrokenEngine(true, msg);
    });
    connect(mTextAutoGenerateWidget, &TextAutoGenerateWidget::pluginInitialized, this, [this]() {
        setBrokenEngine(false, {});
    });
    connect(mTextAutoGenerateNotWorkingWidget, &TextAutoGenerateNotWorkingWidget::ollamaStarted, this, [this]() {
        setBrokenEngine(false, {});
    });
    connect(mTextAutoGenerateNotWorkingWidget, &TextAutoGenerateNotWorkingWidget::startOllamaRequested, this, [this]() {
        Q_EMIT mManager->startOllamaRequested();
    });
    connect(mTextAutoGenerateNotWorkingWidget,
            &TextAutoGenerateNotWorkingWidget::configureInstances,
            this,
            &TextAutoGenerateStackWidget::slotConfigureInstances);
    connect(mTextAutoGenerateWidget, &TextAutoGenerateWidget::needToAddInstances, this, &TextAutoGenerateStackWidget::slotNeedToAddInstances);
    connect(mTextAutoGenerateNotInstanceFoundWidget,
            &TextAutoGenerateNotInstanceFoundWidget::addInstanceRequested,
            this,
            &TextAutoGenerateStackWidget::slotConfigureInstances);

    QTimer::singleShot(0, mTextAutoGenerateWidget, &TextAutoGenerateWidget::loadEngine);
}

TextAutoGenerateStackWidget::~TextAutoGenerateStackWidget() = default;

void TextAutoGenerateStackWidget::slotConfigureInstances()
{
    TextAutoGenerateTextInstancesManagerDialog dlg(mManager, this);
    if (dlg.exec()) {
        if (mManager->textAutoGenerateTextInstancesManager()->isEmpty()) {
            mStackedWidget->setCurrentWidget(mTextAutoGenerateNotInstanceFoundWidget);
        } else {
            mStackedWidget->setCurrentWidget(mTextAutoGenerateWidget);
        }
    }
}

void TextAutoGenerateStackWidget::slotNeedToAddInstances()
{
    mStackedWidget->setCurrentWidget(mTextAutoGenerateNotInstanceFoundWidget);
}

void TextAutoGenerateStackWidget::setBrokenEngine(bool state, const QString &errorMessage)
{
    if (state) {
        if (mStackedWidget->currentWidget() != mTextAutoGenerateNotWorkingWidget) {
            mTextAutoGenerateNotWorkingWidget->setMessageError(errorMessage);
            mStackedWidget->setCurrentWidget(mTextAutoGenerateNotWorkingWidget);
        }
    } else {
        if (mStackedWidget->currentWidget() != mTextAutoGenerateWidget) {
            mTextAutoGenerateNotWorkingWidget->clearMessage();
            mStackedWidget->setCurrentWidget(mTextAutoGenerateWidget);
        }
    }
}

void TextAutoGenerateStackWidget::slotSearchText()
{
    mTextAutoGenerateWidget->slotSearchText();
}

#include "moc_textautogeneratestackwidget.cpp"
