/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateselectpromptwidget.h"
#include "core/models/textautogeneratetextpromptmodel.h"
#include "core/models/textautogeneratetextpromptsortfilterproxymodel.h"
#include "core/textautogenerateagentprompskillmanager.h"
#include "core/textautogeneratemanager.h"
#include "textautogenerateselectpromptlistwidget.h"
#include "widgets/promptswidget/textautogeneratesearchpromptwidget.h"
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectPromptWidget::TextAutoGenerateSelectPromptWidget(TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mListWidget(new TextAutoGenerateSelectPromptListWidget(this))
    , mPromptModel(new TextAutoGenerateTextPromptModel(this))
    , mSearchPromptWidget(new TextAutoGenerateSearchPromptWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mPromptModel->setObjectName(u"mPromptModel"_s);
    mPromptModel->setPrompt(manager->textAutoGenerateAgentPrompSkillManager()->prompts());
    auto filterProxyModel = new TextAutoGenerateTextPromptSortFilterProxyModel(this);
    filterProxyModel->setSourceModel(mPromptModel);

    mSearchPromptWidget->setObjectName(u"mSearchPromptWidget"_s);
    mainLayout->addWidget(mSearchPromptWidget);
    // TODO connect to model

    mListWidget->setModel(filterProxyModel);
    mListWidget->setObjectName(u"mListWidget"_s);
    mainLayout->addWidget(mListWidget);

    connect(mListWidget, &TextAutoGenerateSelectPromptListWidget::addPrompt, this, &TextAutoGenerateSelectPromptWidget::slotAddPrompt);
    connect(mListWidget, &TextAutoGenerateSelectPromptListWidget::removePrompt, this, &TextAutoGenerateSelectPromptWidget::slotRemovePrompt);
}

TextAutoGenerateSelectPromptWidget::~TextAutoGenerateSelectPromptWidget() = default;

void TextAutoGenerateSelectPromptWidget::slotAddPrompt()
{
    // TODO
}

void TextAutoGenerateSelectPromptWidget::slotRemovePrompt(const QByteArray &identifier)
{
    mPromptModel->removePrompt(identifier);
}

#include "moc_textautogenerateselectpromptwidget.cpp"
