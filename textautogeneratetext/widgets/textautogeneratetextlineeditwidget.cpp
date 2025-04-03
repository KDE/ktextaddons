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
    mainLayout->addWidget(mTextAutogenerateTextLineEdit, 0, Qt::AlignTop);

    mSendMessage->setObjectName(QStringLiteral("mSendMessage"));
    mainLayout->addWidget(mSendMessage, 0, Qt::AlignTop);

    connect(mTextAutogenerateTextLineEdit, &TextAutogenerateTextLineEdit::sendMessage, this, [this](const QString &msg) {
        const QString str = msg.trimmed();
        mSendMessage->setEnabled(!str.isEmpty());
        if (!str.isEmpty()) {
            Q_EMIT editingFinished(str);
        }
    });
    mSendMessage->setEnabled(false);

    connect(mTextAutogenerateTextLineEdit, &TextAutogenerateTextLineEdit::textChanged, this, [this]() {
        mSendMessage->setEnabled(!mTextAutogenerateTextLineEdit->document()->isEmpty());
    });

    connect(mSendMessage, &QPushButton::clicked, this, [this]() {
        Q_EMIT editingFinished(mTextAutogenerateTextLineEdit->text());
        mTextAutogenerateTextLineEdit->clear();
    });
}

TextAutogenerateTextLineEditWidget::~TextAutogenerateTextLineEditWidget() = default;

QString TextAutogenerateTextLineEditWidget::text() const
{
    return mTextAutogenerateTextLineEdit->text();
}

#include "moc_textautogeneratetextlineeditwidget.cpp"
