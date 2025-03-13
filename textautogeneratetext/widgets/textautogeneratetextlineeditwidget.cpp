/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditwidget.h"
#include "widgets/textautogeneratetextlineedit.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QPushButton>

using namespace TextAutogenerateText;
TextAutogenerateTextLineEditWidget::TextAutogenerateTextLineEditWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutogenerateTextLineEdit(new TextAutogenerateTextLineEdit(this))
    , mSendMessage(new QPushButton(i18n("Send"), this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mTextAutogenerateTextLineEdit->setObjectName(QStringLiteral("mTextAutogenerateTextLineEdit"));
    mainLayout->addWidget(mTextAutogenerateTextLineEdit);

    mSendMessage->setObjectName(QStringLiteral("mSendMessage"));
    mainLayout->addWidget(mSendMessage);

    connect(mTextAutogenerateTextLineEdit, &TextAutogenerateTextLineEdit::editingFinished, this, [this]() {
        Q_EMIT editingFinished(mTextAutogenerateTextLineEdit->text());
    });
    mSendMessage->setEnabled(false);
    connect(mTextAutogenerateTextLineEdit, &TextAutogenerateTextLineEdit::textEdited, this, [this](const QString &str) {
        mSendMessage->setEnabled(!str.isEmpty());
    });

    connect(mSendMessage, &QPushButton::clicked, this, [this]() {
        Q_EMIT editingFinished(mTextAutogenerateTextLineEdit->text());
    });
}

TextAutogenerateTextLineEditWidget::~TextAutogenerateTextLineEditWidget() = default;

QString TextAutogenerateTextLineEditWidget::text() const
{
    return mTextAutogenerateTextLineEdit->text();
}

#include "moc_textautogeneratetextlineeditwidget.cpp"
