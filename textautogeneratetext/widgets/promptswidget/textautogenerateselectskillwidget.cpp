/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateselectskillwidget.h"
#include "core/models/textautogeneratetextskillmodel.h"
#include "core/textautogenerateagentprompskillmanager.h"
#include "core/textautogeneratemanager.h"
#include "textautogenerateselectskilllistwidget.h"
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectSkillWidget::TextAutoGenerateSelectSkillWidget(TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mListWidget(new TextAutoGenerateSelectSkillListWidget(this))
    , mSkillModel(new TextAutoGenerateTextSkillModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mSkillModel->setObjectName(u"mSkillModel"_s);
    if (manager) {
        mSkillModel->setSkills(manager->textAutoGenerateAgentPrompSkillManager()->skills());
    }

    mListWidget->setModel(mSkillModel);
    mListWidget->setObjectName(u"mListWidget"_s);
    mainLayout->addWidget(mListWidget);

    connect(mListWidget, &TextAutoGenerateSelectSkillListWidget::addSkill, this, &TextAutoGenerateSelectSkillWidget::slotAddSkill);
    connect(mListWidget, &TextAutoGenerateSelectSkillListWidget::editSkill, this, &TextAutoGenerateSelectSkillWidget::slotEditSkill);
    connect(mListWidget, &TextAutoGenerateSelectSkillListWidget::removeSkill, this, &TextAutoGenerateSelectSkillWidget::slotRemoveSkill);
}

TextAutoGenerateSelectSkillWidget::~TextAutoGenerateSelectSkillWidget() = default;

QList<TextAutoGenerateSkill> TextAutoGenerateSelectSkillWidget::skills() const
{
    return mSkillModel->skills();
}

void TextAutoGenerateSelectSkillWidget::slotEditSkill(const TextAutoGenerateText::TextAutoGenerateSkill &skill)
{
    mSkillModel->updateSkill(skill);
}

void TextAutoGenerateSelectSkillWidget::slotAddSkill(const TextAutoGenerateText::TextAutoGenerateSkill &skill)
{
    mSkillModel->addSkill(skill);
}

void TextAutoGenerateSelectSkillWidget::slotRemoveSkill(const QByteArray &identifier)
{
    mSkillModel->removeSkill(identifier);
}

#include "moc_textautogenerateselectskillwidget.cpp"
