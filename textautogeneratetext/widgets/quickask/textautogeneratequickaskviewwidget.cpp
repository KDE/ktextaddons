/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskviewwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "core/textautogeneratemanager.h"
#include "widgets/common/textautogenerateresultwidget.h"
#include "widgets/common/textautogeneratetextlineeditwidget.h"
#include "widgets/instancesmanager/textautogeneratetextinstancesmanagerdialog.h"
#include "widgets/quickask/textautogeneratequickaskheaderwidget.h"
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
TextAutoGenerateQuickAskViewWidget::TextAutoGenerateQuickAskViewWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateTextLineWidget(new TextAutoGenerateTextLineEditWidget(manager, this))
    , mTextAutoGenerateResultWidget(new TextAutoGenerateResultWidget(manager, this))
    , mTextAutoGenerateQuickAskHeaderWidget(new TextAutoGenerateQuickAskHeaderWidget(manager, this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
    // mainLayout->setSpacing(0);

    mTextAutoGenerateQuickAskHeaderWidget->setObjectName(u"mTextAutoGenerateQuickAskHeaderWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateQuickAskHeaderWidget);

    mTextAutoGenerateResultWidget->setObjectName(u"mTextAutoGenerateResultWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateResultWidget, 1);

    mTextAutoGenerateTextLineWidget->setObjectName(u"mTextAutoGenerateTextLineWidget"_s);
    mainLayout->addWidget(mTextAutoGenerateTextLineWidget);
    connect(mTextAutoGenerateTextLineWidget, &TextAutoGenerateTextLineEditWidget::editingFinished, this, &TextAutoGenerateQuickAskViewWidget::editingFinished);
    connect(mTextAutoGenerateQuickAskHeaderWidget,
            &TextAutoGenerateQuickAskHeaderWidget::configureRequested,
            this,
            &TextAutoGenerateQuickAskViewWidget::slotConfigureInstances);

    connect(mTextAutoGenerateResultWidget, &TextAutoGenerateResultWidget::cancelRequested, this, &TextAutoGenerateQuickAskViewWidget::cancelRequested);

    connect(mTextAutoGenerateResultWidget,
            &TextAutoGenerateResultWidget::refreshAnswerRequested,
            this,
            &TextAutoGenerateQuickAskViewWidget::refreshAnswerRequested);

    connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::pluginsInitializedDone, this, [this]() {
        mTextAutoGenerateQuickAskHeaderWidget->setModelList(mManager->textAutoGeneratePlugin()->models());
    });
}

TextAutoGenerateQuickAskViewWidget::~TextAutoGenerateQuickAskViewWidget() = default;

void TextAutoGenerateQuickAskViewWidget::slotConfigureInstances()
{
    TextAutoGenerateTextInstancesManagerDialog dlg(mManager, this);
    if (dlg.exec()) {
        Q_EMIT configureChanged();
    }
}

#include "moc_textautogeneratequickaskviewwidget.cpp"
