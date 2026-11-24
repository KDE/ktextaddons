/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateagentwidget.h"
#include <KIconButton>
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
    , mIconName(new KIconButton(this))
    , mDescription(new QPlainTextEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mName->setObjectName(u"mName"_s);
    KLineEditEventHandler::catchReturnKey(mName);
    connect(mName, &QLineEdit::textChanged, this, &TextAutoGenerateAgentWidget::slotNameChanged);

    mIconName->setObjectName(u"mIconName"_s);
    mDescription->setObjectName(u"mDescription"_s);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Icon:"), mIconName);
    mainLayout->addRow(i18n("Description:"), mDescription);
}

TextAutoGenerateAgentWidget::~TextAutoGenerateAgentWidget() = default;

void TextAutoGenerateAgentWidget::slotNameChanged(const QString &name)
{
    Q_EMIT enableOkButton(!name.trimmed().isEmpty());
}

void TextAutoGenerateAgentWidget::setAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent)
{
    mCurrentAgent = agent;
    mName->setText(agent.name());
    mIconName->setIcon(agent.iconName());
    mDescription->setPlainText(agent.description());
}

TextAutoGenerateText::TextAutoGenerateAgent TextAutoGenerateAgentWidget::agent() const
{
    TextAutoGenerateText::TextAutoGenerateAgent agent = mCurrentAgent;
    if (!agent.isValid()) {
        agent.createUniqueIdentifier();
    }
    agent.setDescription(mDescription->toPlainText());
    agent.setName(mName->text());
    agent.setIconName(mIconName->icon());
    return agent;
}

#include "moc_textautogenerateagentwidget.cpp"
