/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskviewwidget.h"
#include "core/textautogeneratemanager.h"
#include "widgets/common/textautogenerateresultwidget.h"
#include "widgets/common/textautogeneratetextlineedit.h"
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
TextAutoGenerateQuickAskViewWidget::TextAutoGenerateQuickAskViewWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateTextLineEdit(new TextAutoGenerateTextLineEdit(this))
    , mTextAutoGenerateResultWidget(new TextAutoGenerateResultWidget(manager, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mTextAutoGenerateResultWidget->setObjectName(QStringLiteral("mTextAutoGenerateResultWidget"));
    mainLayout->addWidget(mTextAutoGenerateResultWidget);

    mTextAutoGenerateTextLineEdit->setObjectName(QStringLiteral("mTextAutoGenerateTextLineEdit"));
    mainLayout->addWidget(mTextAutoGenerateTextLineEdit);
}

TextAutoGenerateQuickAskViewWidget::~TextAutoGenerateQuickAskViewWidget() = default;

#include "moc_textautogeneratequickaskviewwidget.cpp"
