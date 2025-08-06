/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfigurepromptwidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QPlainTextEdit>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateTextConfigurePromptWidget::TextAutoGenerateTextConfigurePromptWidget(QWidget *parent)
    : QWidget{parent}
    , mSystemPrompt(new QPlainTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mSystemPrompt->setObjectName(u"mSystemPrompt"_s);

    auto label = new QLabel(i18n("Prompt"), this);
    label->setObjectName(u"label"_s);

    mainLayout->addWidget(label);
    mainLayout->addWidget(mSystemPrompt);
}

TextAutoGenerateTextConfigurePromptWidget::~TextAutoGenerateTextConfigurePromptWidget() = default;

#include "moc_textautogeneratetextconfigurepromptwidget.cpp"
