/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfigurepromptsagentswidget.h"
#include "core/textautogenerateagentprompskillmanager.h"
#include "core/textautogeneratemanager.h"
#include "widgets/promptswidget/textautogenerateselectagentwidget.h"
#include "widgets/promptswidget/textautogenerateselectpromptwidget.h"
#include "widgets/promptswidget/textautogenerateselectskillwidget.h"
#include <KLocalizedString>
#include <QTabWidget>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateTextConfigurePromptsAgentsWidget::TextAutoGenerateTextConfigurePromptsAgentsWidget(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                                   QWidget *parent)
    : QWidget{parent}
    , mManager(manager)
    , mTabWidget(new QTabWidget(this))
    , mSelectPromptWidget(new TextAutoGenerateSelectPromptWidget(manager, this))
    , mSelectSkillWidget(new TextAutoGenerateSelectSkillWidget(manager, this))
    , mSelectAgentWidget(new TextAutoGenerateSelectAgentWidget(manager, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mTabWidget->setObjectName(u"mTabWidget"_s);
    mainLayout->addWidget(mTabWidget);

    mSelectPromptWidget->setObjectName(u"mSelectPromptWidget"_s);
    mTabWidget->addTab(mSelectPromptWidget, i18nc("@title:tab", "Prompts"));
    mSelectSkillWidget->setObjectName(u"mSelectSkillWidget"_s);
    mTabWidget->addTab(mSelectSkillWidget, i18nc("@title:tab", "Skills"));
    mSelectAgentWidget->setObjectName(u"mSelectAgentWidget"_s);
    mTabWidget->addTab(mSelectAgentWidget, i18nc("@title:tab", "Agents"));

    connect(mSelectPromptWidget,
            &TextAutoGenerateSelectPromptWidget::settingsChanged,
            this,
            &TextAutoGenerateTextConfigurePromptsAgentsWidget::settingsChanged);
    connect(mSelectSkillWidget, &TextAutoGenerateSelectSkillWidget::settingsChanged, this, &TextAutoGenerateTextConfigurePromptsAgentsWidget::settingsChanged);
    connect(mSelectAgentWidget, &TextAutoGenerateSelectAgentWidget::settingsChanged, this, &TextAutoGenerateTextConfigurePromptsAgentsWidget::settingsChanged);
}

TextAutoGenerateTextConfigurePromptsAgentsWidget::~TextAutoGenerateTextConfigurePromptsAgentsWidget() = default;

void TextAutoGenerateTextConfigurePromptsAgentsWidget::load()
{
    mSelectPromptWidget->load();
    mSelectSkillWidget->load();
    mSelectAgentWidget->load();
}

void TextAutoGenerateTextConfigurePromptsAgentsWidget::save()
{
    if (!mManager) {
        return;
    }
    mSelectPromptWidget->save();
    mSelectSkillWidget->save();
    mSelectAgentWidget->save();
    mManager->textAutoGenerateAgentPrompSkillManager()->save();
}

#include "moc_textautogeneratetextconfigurepromptsagentswidget.cpp"
