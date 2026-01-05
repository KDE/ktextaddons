/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateshowmodelinfowidget.h"
#include <QTextEdit>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateShowModelInfoWidget::TextAutoGenerateShowModelInfoWidget(QWidget *parent)
    : QWidget{parent}
    , mTextEdit(new QTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mTextEdit->setObjectName(u"mTextEdit"_s);
    mTextEdit->setReadOnly(true);
    mainLayout->addWidget(mTextEdit);
}

TextAutoGenerateShowModelInfoWidget::~TextAutoGenerateShowModelInfoWidget() = default;

void TextAutoGenerateShowModelInfoWidget::setText(const QString &text)
{
    mTextEdit->setMarkdown(text);
}

#include "moc_textautogenerateshowmodelinfowidget.cpp"
