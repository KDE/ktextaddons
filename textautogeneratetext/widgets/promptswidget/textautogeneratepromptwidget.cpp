/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratepromptwidget.h"
#include "core/prompts/textautogenerateprompt.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGeneratePromptWidget::TextAutoGeneratePromptWidget(QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mDescription(new QLineEdit(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mName->setObjectName(u"mName"_s);
    mDescription->setObjectName(u"mDescription"_s);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Description:"), mDescription);
}

TextAutoGeneratePromptWidget::~TextAutoGeneratePromptWidget() = default;

void TextAutoGeneratePromptWidget::setPrompt(const TextAutoGenerateText::TextAutoGeneratePrompt &prompt)
{
    // TODO
}

TextAutoGenerateText::TextAutoGeneratePrompt TextAutoGeneratePromptWidget::prompt() const
{
    // TODO
    return {};
}
