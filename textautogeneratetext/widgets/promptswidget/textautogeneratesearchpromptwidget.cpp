/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchpromptwidget.h"
#include "textautogeneratepromptcategorycombobox.h"
#include <KLineEditEventHandler>
#include <QHBoxLayout>
#include <QLineEdit>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSearchPromptWidget::TextAutoGenerateSearchPromptWidget(QWidget *parent)
    : QWidget{parent}
    , mSearchLineEdit(new QLineEdit(this))
    , mPromptComboBox(new TextAutoGeneratePromptCategoryComboBox(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName(u"mSearchLineEdit"_s);
    mPromptComboBox->setObjectName(u"mPromptComboBox"_s);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);

    mainLayout->addWidget(mSearchLineEdit);
    mainLayout->addWidget(mPromptComboBox);
}

TextAutoGenerateSearchPromptWidget::~TextAutoGenerateSearchPromptWidget() = default;
#include "moc_textautogeneratesearchpromptwidget.cpp"
