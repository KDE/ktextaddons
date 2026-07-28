/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratepromptwidget.h"
#include "core/prompts/textautogenerateprompt.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGeneratePromptWidget::TextAutoGeneratePromptWidget(QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mDescription(new QPlainTextEdit(this))
    , mPrompt(new QPlainTextEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mName->setObjectName(u"mName"_s);
    KLineEditEventHandler::catchReturnKey(mName);
    mDescription->setObjectName(u"mDescription"_s);
    mPrompt->setObjectName(u"mPrompt"_s);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Description:"), mDescription);
    mainLayout->addRow(i18n("Prompt:"), mPrompt);
}

TextAutoGeneratePromptWidget::~TextAutoGeneratePromptWidget() = default;

void TextAutoGeneratePromptWidget::setPrompt(const TextAutoGenerateText::TextAutoGeneratePrompt &prompt)
{
    mName->setText(prompt.name());
    mDescription->setPlainText(prompt.description());
    mPrompt->setPlainText(prompt.text());
}

TextAutoGenerateText::TextAutoGeneratePrompt TextAutoGeneratePromptWidget::prompt() const
{
    TextAutoGenerateText::TextAutoGeneratePrompt prompt;
    prompt.setDescription(mDescription->toPlainText());
    prompt.setText(mPrompt->toPlainText());
    prompt.setName(mName->text());
    return prompt;
}

#include "moc_textautogeneratepromptwidget.cpp"
