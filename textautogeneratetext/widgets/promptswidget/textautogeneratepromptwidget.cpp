/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratepromptwidget.h"
#include "core/prompts/textautogenerateprompt.h"
#include "widgets/promptswidget/textautogeneratepromptcategorycombobox.h"
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
    , mCategory(new TextAutoGeneratePromptCategoryComboBox(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mName->setObjectName(u"mName"_s);
    KLineEditEventHandler::catchReturnKey(mName);

    mCategory->setObjectName(u"mCategory"_s);

    mDescription->setObjectName(u"mDescription"_s);
    mPrompt->setObjectName(u"mPrompt"_s);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Category:"), mCategory);
    mainLayout->addRow(i18n("Description:"), mDescription);
    mainLayout->addRow(i18n("Prompt:"), mPrompt);
}

TextAutoGeneratePromptWidget::~TextAutoGeneratePromptWidget() = default;

void TextAutoGeneratePromptWidget::setPrompt(const TextAutoGenerateText::TextAutoGeneratePrompt &prompt)
{
    mName->setText(prompt.name());
    mDescription->setPlainText(prompt.description());
    mPrompt->setPlainText(prompt.text());
    mCategory->setCategory(prompt.category());
}

TextAutoGenerateText::TextAutoGeneratePrompt TextAutoGeneratePromptWidget::prompt() const
{
    TextAutoGenerateText::TextAutoGeneratePrompt prompt;
    prompt.setDescription(mDescription->toPlainText());
    prompt.setText(mPrompt->toPlainText());
    prompt.setName(mName->text());
    prompt.setCategory(mCategory->category());
    return prompt;
}

#include "moc_textautogeneratepromptwidget.cpp"
