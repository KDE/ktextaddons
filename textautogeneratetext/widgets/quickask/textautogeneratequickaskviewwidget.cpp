/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskviewwidget.h"
#include "core/textautogeneratemanager.h"
#include "widgets/common/textautogenerateresultwidget.h"
#include "widgets/common/textautogeneratetextlineeditwidget.h"
#include "widgets/quickask/textautogeneratequickaskheaderwidget.h"
#include "widgets/textautogenerateconfiguredialog.h"
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
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
    // mainLayout->setSpacing(0);

    mTextAutoGenerateQuickAskHeaderWidget->setObjectName(QStringLiteral("mTextAutoGenerateQuickAskHeaderWidget"));
    mainLayout->addWidget(mTextAutoGenerateQuickAskHeaderWidget);

    mTextAutoGenerateResultWidget->setObjectName(QStringLiteral("mTextAutoGenerateResultWidget"));
    mainLayout->addWidget(mTextAutoGenerateResultWidget, 1);

    mTextAutoGenerateTextLineWidget->setObjectName(QStringLiteral("mTextAutoGenerateTextLineWidget"));
    mainLayout->addWidget(mTextAutoGenerateTextLineWidget);
    connect(mTextAutoGenerateTextLineWidget, &TextAutoGenerateTextLineEditWidget::editingFinished, this, &TextAutoGenerateQuickAskViewWidget::editingFinished);
    connect(mTextAutoGenerateQuickAskHeaderWidget,
            &TextAutoGenerateQuickAskHeaderWidget::configureRequested,
            this,
            &TextAutoGenerateQuickAskViewWidget::slotConfigureRequested);
}

TextAutoGenerateQuickAskViewWidget::~TextAutoGenerateQuickAskViewWidget() = default;

void TextAutoGenerateQuickAskViewWidget::slotConfigureRequested()
{
    TextAutoGenerateText::TextAutoGenerateConfigureDialog d(mManager, this);
    if (d.exec()) {
        d.saveSettings();
        // Q_EMIT configChanged();
    }
}

#include "moc_textautogeneratequickaskviewwidget.cpp"
