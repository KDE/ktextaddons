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
            Q_EMIT editingFinished(str, mUuid);
            clearLineEdit();
        }
    });
    mSendMessage->setEnabled(false);

    connect(mTextAutogenerateTextLineEdit, &TextAutogenerateTextLineEdit::textChanged, this, [this]() {
        mSendMessage->setEnabled(!mTextAutogenerateTextLineEdit->document()->isEmpty());
    });

    connect(mSendMessage, &QPushButton::clicked, this, [this]() {
        Q_EMIT editingFinished(mTextAutogenerateTextLineEdit->text(), mUuid);
        clearLineEdit();
    });
    connect(mTextAutogenerateTextLineEdit, &TextAutogenerateTextLineEdit::keyPressed, this, &TextAutogenerateTextLineEditWidget::keyPressed);
}

TextAutogenerateTextLineEditWidget::~TextAutogenerateTextLineEditWidget() = default;

void TextAutogenerateTextLineEditWidget::clearLineEdit()
{
    mTextAutogenerateTextLineEdit->clear();
    mUuid.clear();
}

QString TextAutogenerateTextLineEditWidget::text() const
{
    return mTextAutogenerateTextLineEdit->text();
}

void TextAutogenerateTextLineEditWidget::setText(const QString &str)
{
    mTextAutogenerateTextLineEdit->setText(str);
}

QByteArray TextAutogenerateTextLineEditWidget::uuid() const
{
    return mUuid;
}

void TextAutogenerateTextLineEditWidget::setUuid(const QByteArray &newUuid)
{
    mUuid = newUuid;
}

#include "moc_textautogeneratetextlineeditwidget.cpp"
