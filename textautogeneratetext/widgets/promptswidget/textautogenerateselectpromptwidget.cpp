/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateselectpromptwidget.h"
#include "textautogenerateselectpromptlistwidget.h"
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectPromptWidget::TextAutoGenerateSelectPromptWidget(QWidget *parent)
    : QWidget{parent}
    , mListWidget(new TextAutoGenerateSelectPromptListWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mListWidget->setObjectName(u"mainLayout"_s);
    mainLayout->addWidget(mListWidget);
}

TextAutoGenerateSelectPromptWidget::~TextAutoGenerateSelectPromptWidget() = default;
#include "moc_textautogenerateselectpromptwidget.cpp"
