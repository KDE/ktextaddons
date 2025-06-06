/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskwidget.h"
#include "core/textautogeneratemanager.h"

#include "textautogeneratequickaskviewwidget.h"
#include <QStackedWidget>
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
TextAutoGenerateQuickAskWidget::TextAutoGenerateQuickAskWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mStackedWidget(new QStackedWidget(this))
    , mTextAutoGenerateQuickAskViewWidget(new TextAutoGenerateQuickAskViewWidget(manager, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mStackedWidget->setObjectName(QStringLiteral("mStackedWidget"));
    mainLayout->addWidget(mStackedWidget);

    mTextAutoGenerateQuickAskViewWidget->setObjectName(QStringLiteral("mTextAutoGenerateQuickAskViewWidget"));
    mStackedWidget->addWidget(mTextAutoGenerateQuickAskViewWidget);
}

TextAutoGenerateQuickAskWidget::~TextAutoGenerateQuickAskWidget() = default;

#include "moc_textautogeneratequickaskwidget.cpp"
