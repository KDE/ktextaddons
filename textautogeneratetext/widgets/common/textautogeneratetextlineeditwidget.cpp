/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextlineeditwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "core/textautogeneratemanager.h"
#include "widgets/common/textautogeneratetextlineedit.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QPushButton>

using namespace TextAutoGenerateText;
TextAutoGenerateTextLineEditWidget::TextAutoGenerateTextLineEditWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateTextLineEdit(new TextAutoGenerateTextLineEdit(this))
    , mSendMessage(new QPushButton(QIcon::fromTheme(u"document-send"_s), i18n("Send"), this))
    , mManager(manager)
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mTextAutoGenerateTextLineEdit->setObjectName(u"mTextAutoGenerateTextLineEdit"_s);
    mainLayout->addWidget(mTextAutoGenerateTextLineEdit, 0, Qt::AlignTop);

    mSendMessage->setObjectName(u"mSendMessage"_s);
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
    if (mManager) {
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::showArchiveChanged, this, &TextAutoGenerateTextLineEditWidget::updateEnableState);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::chatInProgressChanged, this, &TextAutoGenerateTextLineEditWidget::updateEnableState);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged, this, &TextAutoGenerateTextLineEditWidget::updateEnableState);
    }
}

TextAutoGenerateTextLineEditWidget::~TextAutoGenerateTextLineEditWidget() = default;

void TextAutoGenerateTextLineEditWidget::updateEnableState()
{
    setEnabled(!mManager->showArchived() && !mManager->chatInProgress(mManager->currentChatId()));
}

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
