/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateskillwidget.h"
#include "core/prompts/textautogenerateskill.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

TextAutoGenerateSkillWidget::TextAutoGenerateSkillWidget(QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mDescription(new QLineEdit(this))
    , mInstructions(new QPlainTextEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mName->setObjectName(u"mName"_s);
    KLineEditEventHandler::catchReturnKey(mName);
    mDescription->setObjectName(u"mDescription"_s);
    KLineEditEventHandler::catchReturnKey(mDescription);
    mInstructions->setObjectName(u"mInstructions"_s);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Description:"), mDescription);
    mainLayout->addRow(i18n("Instructions:"), mInstructions);
}

TextAutoGenerateSkillWidget::~TextAutoGenerateSkillWidget() = default;

void TextAutoGenerateSkillWidget::setSkill(const TextAutoGenerateText::TextAutoGenerateSkill &skill)
{
    mName->setText(skill.name());
    mDescription->setText(skill.description());
    mInstructions->setPlainText(skill.instructions());
}

TextAutoGenerateText::TextAutoGenerateSkill TextAutoGenerateSkillWidget::skill() const
{
    TextAutoGenerateText::TextAutoGenerateSkill skill;
    skill.setDescription(mDescription->text());
    skill.setInstructions(mInstructions->toPlainText());
    skill.setName(mName->text());
    return skill;
}

#include "moc_textautogenerateskillwidget.cpp"
