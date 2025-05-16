/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditwidget.h"
#include "core/textautogeneratemanager.h"
#include "widgets/textautogeneratetextlineedit.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QPushButton>

using namespace TextAutoGenerateText;
TextAutoGenerateTextLineEditWidget::TextAutoGenerateTextLineEditWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateTextLineEdit(new TextAutoGenerateTextLineEdit(this))
    , mSendMessage(new QPushButton(QIcon::fromTheme(QStringLiteral("document-send")), i18n("Send"), this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mTextAutoGenerateTextLineEdit->setObjectName(QStringLiteral("mTextAutoGenerateTextLineEdit"));
    mainLayout->addWidget(mTextAutoGenerateTextLineEdit, 0, Qt::AlignTop);

    mSendMessage->setObjectName(QStringLiteral("mSendMessage"));
    mainLayout->addWidget(mSendMessage, 0, Qt::AlignTop);

    connect(mTextAutoGenerateTextLineEdit, &TextAutoGenerateTextLineEdit::sendMessage, this, [this](const QString &msg) {
        const QString str = msg.trimmed();
        mSendMessage->setEnabled(!str.isEmpty());
        if (!str.isEmpty()) {
            Q_EMIT editingFinished(str, mUuid);
            clearLineEdit();
        }
    });
    mSendMessage->setEnabled(false);

    connect(mTextAutoGenerateTextLineEdit, &TextAutoGenerateTextLineEdit::textChanged, this, [this]() {
        mSendMessage->setEnabled(!mTextAutoGenerateTextLineEdit->document()->isEmpty());
    });

    connect(mSendMessage, &QPushButton::clicked, this, [this]() {
        Q_EMIT editingFinished(mTextAutoGenerateTextLineEdit->text(), mUuid);
        clearLineEdit();
    });
    connect(mTextAutoGenerateTextLineEdit, &TextAutoGenerateTextLineEdit::keyPressed, this, &TextAutoGenerateTextLineEditWidget::keyPressed);
    if (manager) {
        connect(manager, &TextAutoGenerateText::TextAutoGenerateManager::showArchiveChanged, this, [this, manager]() {
            setEnabled(!manager->showArchived());
        });
    }
}

TextAutoGenerateTextLineEditWidget::~TextAutoGenerateTextLineEditWidget() = default;

void TextAutoGenerateTextLineEditWidget::clearLineEdit()
{
    mTextAutoGenerateTextLineEdit->clear();
    mUuid.clear();
}

QString TextAutoGenerateTextLineEditWidget::text() const
{
    return mTextAutoGenerateTextLineEdit->text();
}

void TextAutoGenerateTextLineEditWidget::setText(const QString &str)
{
    mTextAutoGenerateTextLineEdit->setText(str);
}

QByteArray TextAutoGenerateTextLineEditWidget::uuid() const
{
    return mUuid;
}

void TextAutoGenerateTextLineEditWidget::setUuid(const QByteArray &newUuid)
{
    mUuid = newUuid;
}

#include "moc_textautogeneratetextlineeditwidget.cpp"
