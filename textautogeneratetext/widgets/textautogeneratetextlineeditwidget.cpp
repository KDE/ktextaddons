/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditwidget.h"
#include "widgets/textautogeneratetextlineedit.h"
#include <QHBoxLayout>

using namespace TextAutogenerateText;
TextAutogenerateTextLineEditWidget::TextAutogenerateTextLineEditWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutogenerateTextLineEdit(new TextAutogenerateTextLineEdit(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mTextAutogenerateTextLineEdit->setObjectName(QStringLiteral("mTextAutogenerateTextLineEdit"));
    mainLayout->addWidget(mTextAutogenerateTextLineEdit);
    // TODO add button for sending

    connect(mTextAutogenerateTextLineEdit, &TextAutogenerateTextLineEdit::editingFinished, this, [this]() {
        Q_EMIT editingFinished(mTextAutogenerateTextLineEdit->text());
    });
}

TextAutogenerateTextLineEditWidget::~TextAutogenerateTextLineEditWidget() = default;

QString TextAutogenerateTextLineEditWidget::text() const
{
    return mTextAutogenerateTextLineEdit->text();
}

#include "moc_textautogeneratetextlineeditwidget.cpp"
