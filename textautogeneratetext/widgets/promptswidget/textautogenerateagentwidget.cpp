/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateagentwidget.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

TextAutoGenerateAgentWidget::TextAutoGenerateAgentWidget(QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mDescription(new QPlainTextEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mName->setObjectName(u"mName"_s);
    KLineEditEventHandler::catchReturnKey(mName);
    mDescription->setObjectName(u"mDescription"_s);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Description:"), mDescription);
}

TextAutoGenerateAgentWidget::~TextAutoGenerateAgentWidget() = default;

void TextAutoGenerateAgentWidget::setAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent)
{
    mCurrentAgent = agent;
    mName->setText(agent.name());
    mDescription->setPlainText(agent.description());
}

TextAutoGenerateText::TextAutoGenerateAgent TextAutoGenerateAgentWidget::agent() const
{
    TextAutoGenerateText::TextAutoGenerateAgent agent = mCurrentAgent;
    agent.setDescription(mDescription->toPlainText());
    agent.setName(mName->text());
    return agent;
}

#include "moc_textautogenerateagentwidget.cpp"
