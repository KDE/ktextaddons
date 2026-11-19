/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfigurepromptsagentswidgettest.h"
#include "core/models/textautogeneratetextagentmodel.h"
#include "core/models/textautogeneratetextpromptmodel.h"
#include "core/models/textautogeneratetextskillmodel.h"
#include "core/textautogenerateagentprompskillmanager.h"
#include "core/textautogeneratemanager.h"
#include "widgets/configure/textautogeneratetextconfigurepromptsagentswidget.h"
#include "widgets/promptswidget/textautogenerateselectagentwidget.h"
#include "widgets/promptswidget/textautogenerateselectpromptwidget.h"
#include "widgets/promptswidget/textautogenerateselectskillwidget.h"
#include <QStandardPaths>
#include <QTabWidget>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(TextAutoGenerateTextConfigurePromptsAgentsWidgetTest)

TextAutoGenerateTextConfigurePromptsAgentsWidgetTest::TextAutoGenerateTextConfigurePromptsAgentsWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateTextConfigurePromptsAgentsWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextConfigurePromptsAgentsWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTabWidget = w.findChild<QTabWidget *>(u"mTabWidget"_s);
    QVERIFY(mTabWidget);
    QCOMPARE(mTabWidget->count(), 3);

    auto mSelectPromptWidget = w.findChild<TextAutoGenerateText::TextAutoGenerateSelectPromptWidget *>(u"mSelectPromptWidget"_s);
    QVERIFY(mSelectPromptWidget);
    QCOMPARE(mTabWidget->indexOf(mSelectPromptWidget), 0);
    auto mSelectSkillWidget = w.findChild<TextAutoGenerateText::TextAutoGenerateSelectSkillWidget *>(u"mSelectSkillWidget"_s);
    QVERIFY(mSelectSkillWidget);
    QCOMPARE(mTabWidget->indexOf(mSelectSkillWidget), 1);
    auto mSelectAgentWidget = w.findChild<TextAutoGenerateText::TextAutoGenerateSelectAgentWidget *>(u"mSelectAgentWidget"_s);
    QVERIFY(mSelectAgentWidget);
    QCOMPARE(mTabWidget->indexOf(mSelectAgentWidget), 2);
    for (int i = 0; i < mTabWidget->count(); ++i) {
        QVERIFY(!mTabWidget->tabText(i).isEmpty());
    }
}

void TextAutoGenerateTextConfigurePromptsAgentsWidgetTest::shouldApplyChangesWhenSaved()
{
    TextAutoGenerateText::TextAutoGenerateManager manager;
    auto agentPromptSkillManager = manager.textAutoGenerateAgentPrompSkillManager();
    agentPromptSkillManager->setPrompts({});
    agentPromptSkillManager->setSkills({});
    agentPromptSkillManager->setAgents({});
    TextAutoGenerateText::TextAutoGenerateTextConfigurePromptsAgentsWidget w(&manager);

    TextAutoGenerateText::TextAutoGeneratePrompt prompt;
    prompt.setName(u"prompt"_s);
    prompt.createUniqueIdentifier();
    auto promptModel = w.findChild<TextAutoGenerateText::TextAutoGenerateTextPromptModel *>(u"mPromptModel"_s);
    QVERIFY(promptModel);
    promptModel->addPrompt(prompt);

    TextAutoGenerateText::TextAutoGenerateSkill skill;
    skill.setName(u"skill"_s);
    skill.createUniqueIdentifier();
    auto skillModel = w.findChild<TextAutoGenerateText::TextAutoGenerateTextSkillModel *>(u"mSkillModel"_s);
    QVERIFY(skillModel);
    skillModel->addSkill(skill);

    TextAutoGenerateText::TextAutoGenerateAgent agent;
    agent.setName(u"agent"_s);
    agent.createUniqueIdentifier();
    auto agentModel = w.findChild<TextAutoGenerateText::TextAutoGenerateTextAgentModel *>(u"mAgentModel"_s);
    QVERIFY(agentModel);
    agentModel->addAgent(agent);

    // Manager is not modified before save()
    QVERIFY(agentPromptSkillManager->prompts().isEmpty());
    QVERIFY(agentPromptSkillManager->skills().isEmpty());
    QVERIFY(agentPromptSkillManager->agents().isEmpty());

    w.save();
    QCOMPARE(agentPromptSkillManager->prompts(), QList<TextAutoGenerateText::TextAutoGeneratePrompt>{prompt});
    QCOMPARE(agentPromptSkillManager->skills(), QList<TextAutoGenerateText::TextAutoGenerateSkill>{skill});
    QCOMPARE(agentPromptSkillManager->agents(), QList<TextAutoGenerateText::TextAutoGenerateAgent>{agent});

    // Saved on disk
    TextAutoGenerateText::TextAutoGenerateAgentPrompSkillManager reloaded;
    reloaded.load();
    QCOMPARE(reloaded.prompts(), agentPromptSkillManager->prompts());
    QCOMPARE(reloaded.skills(), agentPromptSkillManager->skills());
    QCOMPARE(reloaded.agents(), agentPromptSkillManager->agents());

    // Clean up
    agentPromptSkillManager->setPrompts({});
    agentPromptSkillManager->setSkills({});
    agentPromptSkillManager->setAgents({});
    agentPromptSkillManager->save();
}

void TextAutoGenerateTextConfigurePromptsAgentsWidgetTest::shouldDiscardChangesWhenLoaded()
{
    TextAutoGenerateText::TextAutoGenerateManager manager;
    auto agentPromptSkillManager = manager.textAutoGenerateAgentPrompSkillManager();
    agentPromptSkillManager->setSkills({});
    TextAutoGenerateText::TextAutoGenerateTextConfigurePromptsAgentsWidget w(&manager);

    TextAutoGenerateText::TextAutoGenerateSkill skill;
    skill.setName(u"skill"_s);
    skill.createUniqueIdentifier();
    auto skillModel = w.findChild<TextAutoGenerateText::TextAutoGenerateTextSkillModel *>(u"mSkillModel"_s);
    QVERIFY(skillModel);
    skillModel->addSkill(skill);
    QCOMPARE(skillModel->skills().count(), 1);

    w.load();
    QVERIFY(skillModel->skills().isEmpty());
    QVERIFY(agentPromptSkillManager->skills().isEmpty());
}

#include "moc_textautogeneratetextconfigurepromptsagentswidgettest.cpp"
