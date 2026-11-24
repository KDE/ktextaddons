/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratepromptwidget.h"
#include "widgets/promptswidget/textautogeneratepromptcategorycombobox.h"
#include <KIconButton>
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
    , mIconName(new KIconButton(this))
    , mCommandCompletion(new QLineEdit(this))
    , mDescription(new QPlainTextEdit(this))
    , mPrompt(new QPlainTextEdit(this))
    , mCategory(new TextAutoGeneratePromptCategoryComboBox(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mName->setObjectName(u"mName"_s);
    KLineEditEventHandler::catchReturnKey(mName);
    connect(mName, &QLineEdit::textChanged, this, &TextAutoGeneratePromptWidget::slotNameChanged);

    mIconName->setObjectName(u"mIconName"_s);

    mCommandCompletion->setObjectName(u"mCommandCompletion"_s);
    KLineEditEventHandler::catchReturnKey(mCommandCompletion);

    mCategory->setObjectName(u"mCategory"_s);

    mDescription->setObjectName(u"mDescription"_s);
    mPrompt->setObjectName(u"mPrompt"_s);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Icon:"), mIconName);
    mainLayout->addRow(i18n("Category:"), mCategory);
    mainLayout->addRow(i18n("Description:"), mDescription);
    mainLayout->addRow(i18n("Prompt:"), mPrompt);
    mainLayout->addRow(i18n("Command Completion:"), mCommandCompletion);
}

TextAutoGeneratePromptWidget::~TextAutoGeneratePromptWidget() = default;

void TextAutoGeneratePromptWidget::slotNameChanged(const QString &name)
{
    Q_EMIT enableOkButton(!name.trimmed().isEmpty());
}

void TextAutoGeneratePromptWidget::setPrompt(const TextAutoGenerateText::TextAutoGeneratePrompt &prompt)
{
    mCurrentPrompt = prompt;
    mName->setText(prompt.name());
    mIconName->setIcon(prompt.iconName());
    mDescription->setPlainText(prompt.description());
    mPrompt->setPlainText(prompt.text());
    mCategory->setCategory(prompt.category());
    mCommandCompletion->setText(prompt.commandCompletion());
}

TextAutoGenerateText::TextAutoGeneratePrompt TextAutoGeneratePromptWidget::prompt() const
{
    TextAutoGenerateText::TextAutoGeneratePrompt prompt = mCurrentPrompt;
    if (!prompt.isValid()) {
        prompt.createUniqueIdentifier();
    }
    prompt.setDescription(mDescription->toPlainText());
    prompt.setText(mPrompt->toPlainText());
    prompt.setName(mName->text());
    prompt.setIconName(mIconName->icon());
    prompt.setCategory(mCategory->category());
    prompt.setCommandCompletion(mCommandCompletion->text());
    return prompt;
}

#include "moc_textautogeneratepromptwidget.cpp"
