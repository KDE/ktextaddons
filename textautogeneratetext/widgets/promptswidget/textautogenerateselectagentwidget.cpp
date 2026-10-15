/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateselectagentwidget.h"
#include "core/models/textautogeneratetextagentmodel.h"
#include "core/textautogenerateagentprompskillmanager.h"
#include "core/textautogeneratemanager.h"
#include "textautogenerateselectagentlistwidget.h"
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectAgentWidget::TextAutoGenerateSelectAgentWidget(TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mListWidget(new TextAutoGenerateSelectAgentListWidget(this))
    , mAgentModel(new TextAutoGenerateTextAgentModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mAgentModel->setObjectName(u"mAgentModel"_s);
    if (manager) {
        mAgentModel->setAgents(manager->textAutoGenerateAgentPrompSkillManager()->agents());
    }

    mListWidget->setModel(mAgentModel);
    mListWidget->setObjectName(u"mListWidget"_s);
    mainLayout->addWidget(mListWidget);

    connect(mListWidget, &TextAutoGenerateSelectAgentListWidget::addAgent, this, &TextAutoGenerateSelectAgentWidget::slotAddAgent);
    connect(mListWidget, &TextAutoGenerateSelectAgentListWidget::editAgent, this, &TextAutoGenerateSelectAgentWidget::slotEditAgent);
    connect(mListWidget, &TextAutoGenerateSelectAgentListWidget::removeAgent, this, &TextAutoGenerateSelectAgentWidget::slotRemoveAgent);
}

TextAutoGenerateSelectAgentWidget::~TextAutoGenerateSelectAgentWidget() = default;

QList<TextAutoGenerateAgent> TextAutoGenerateSelectAgentWidget::agents() const
{
    return mAgentModel->agents();
}

void TextAutoGenerateSelectAgentWidget::slotEditAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent)
{
    mAgentModel->updateAgent(agent);
}

void TextAutoGenerateSelectAgentWidget::slotAddAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent)
{
    mAgentModel->addAgent(agent);
}

void TextAutoGenerateSelectAgentWidget::slotRemoveAgent(const QByteArray &identifier)
{
    mAgentModel->removeAgent(identifier);
}

#include "moc_textautogenerateselectagentwidget.cpp"
