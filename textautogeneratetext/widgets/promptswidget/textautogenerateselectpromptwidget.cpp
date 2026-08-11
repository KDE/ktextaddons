/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateselectpromptwidget.h"
#include "core/models/textautogeneratetextpromptmodel.h"
#include "core/textautogenerateagentprompskillmanager.h"
#include "core/textautogeneratemanager.h"
#include "textautogenerateselectpromptlistwidget.h"
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectPromptWidget::TextAutoGenerateSelectPromptWidget(TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mListWidget(new TextAutoGenerateSelectPromptListWidget(this))
    , mPromptModel(new TextAutoGenerateTextPromptModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mPromptModel->setPrompt(manager->textAutoGenerateAgentPrompSkillManager()->prompts());
    mListWidget->setModel(mPromptModel);
    mListWidget->setObjectName(u"mainLayout"_s);
    mainLayout->addWidget(mListWidget);
}

TextAutoGenerateSelectPromptWidget::~TextAutoGenerateSelectPromptWidget() = default;
#include "moc_textautogenerateselectpromptwidget.cpp"
