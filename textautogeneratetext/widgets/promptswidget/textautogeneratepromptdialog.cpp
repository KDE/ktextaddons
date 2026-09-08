/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratepromptdialog.h"
#include "core/prompts/textautogenerateprompt.h"
#include "textautogeneratepromptwidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
namespace
{
const char myTextAutoGeneratePromptDialogGroupName[] = "TextAutoGeneratePromptDialog";
}
TextAutoGeneratePromptDialog::TextAutoGeneratePromptDialog(QWidget *parent)
    : QDialog(parent)
    , mPromptWidget(new TextAutoGeneratePromptWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Prompt"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mPromptWidget->setObjectName(u"mPromptWidget"_s);
    mainLayout->addWidget(mPromptWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &TextAutoGeneratePromptDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &TextAutoGeneratePromptDialog::accept);
    TextAddonsWidgets::LoadDialogSizeUtils::manageDialogSize(this, QLatin1StringView(myTextAutoGeneratePromptDialogGroupName), QSize(400, 300));
}

TextAutoGeneratePromptDialog::~TextAutoGeneratePromptDialog() = default;

void TextAutoGeneratePromptDialog::setPrompt(const TextAutoGenerateText::TextAutoGeneratePrompt &prompt)
{
    mPromptWidget->setPrompt(prompt);
}

TextAutoGenerateText::TextAutoGeneratePrompt TextAutoGeneratePromptDialog::prompt() const
{
    return mPromptWidget->prompt();
}

#include "moc_textautogeneratepromptdialog.cpp"
