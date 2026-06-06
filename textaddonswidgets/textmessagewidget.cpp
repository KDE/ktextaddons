/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textmessagewidget.h"

#include <KMessageWidget>
#include <QAbstractScrollArea>
#include <QTimer>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAddonsWidgets;
TextMessageWidget::TextMessageWidget(QWidget *parent)
    : QWidget(parent)
    , mMessageWidget(new KMessageWidget(this))
    , mAutoHideTimer(new QTimer(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mMessageWidget->setObjectName(u"mMessageWidget"_s);
    mMessageWidget->setCloseButtonVisible(false);
    mMessageWidget->setPosition(KMessageWidget::Position::Inline);
    mMessageWidget->setWordWrap(false);

    mainLayout->addWidget(mMessageWidget);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    mMessageWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    mMessageWidget->ensurePolished();
    mMessageWidget->adjustSize();
    adjustSize();
    mMessageWidget->hide();
    hide();

    connect(mAutoHideTimer, &QTimer::timeout, this, &TextMessageWidget::hide);

    mAutoHideTimer->setSingleShot(true);
}

void TextMessageWidget::setTextFormat(Qt::TextFormat textFormat)
{
    mMessageWidget->setTextFormat(textFormat);
}

void TextMessageWidget::showMessage(const QString &message, const QString &details, KMessageWidget::MessageType type, int durationMs)
{
    if (mAutoHideTimer->isActive()) {
        mAutoHideTimer->stop();
    }
    QString str = message;
    if (!details.isEmpty()) {
        str += u'\n' + details;
    }
    mMessageWidget->setText(str);
    switch (type) {
    case KMessageWidget::MessageType::Positive:
        mMessageWidget->setMessageType(KMessageWidget::Positive);
        break;
    case KMessageWidget::MessageType::Information:
        mMessageWidget->setMessageType(KMessageWidget::Information);
        break;
    case KMessageWidget::MessageType::Warning:
        mMessageWidget->setMessageType(KMessageWidget::Warning);
        mMessageWidget->setIcon(QIcon::fromTheme(u"state-warning-symbolic"_s));
        break;
    case KMessageWidget::MessageType::Error:
        mMessageWidget->setMessageType(KMessageWidget::Error);
        mMessageWidget->setIcon(QIcon::fromTheme(u"state-error-symbolic"_s));
        break;
    }

    // make sure the widget's size is up-to-date in its hidden state
    mMessageWidget->ensurePolished();
    mMessageWidget->adjustSize();
    mMessageWidget->show();
    adjustSize();
    move(parentWidget()->width() - width() - 10, 10);
    show();
    if (durationMs > 0) {
        mAutoHideTimer->start(durationMs);
    }
}

#include "moc_textmessagewidget.cpp"
