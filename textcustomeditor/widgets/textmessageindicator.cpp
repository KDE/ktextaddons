/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textmessageindicator.h"

#include <KMessageWidget>
#include <QAbstractScrollArea>
#include <QTimer>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextCustomEditor;
TextMessageIndicator::TextMessageIndicator(QWidget *parent)
    : QWidget(parent)
    , mMessageWidget(new KMessageWidget(this))
    , mAutoHideTimer(new QTimer(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mMessageWidget->setCloseButtonVisible(false);
    mMessageWidget->setPosition(KMessageWidget::Position::Inline);

    mainLayout->addWidget(mMessageWidget);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    mMessageWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    mMessageWidget->hide();
    hide();

    connect(mAutoHideTimer, &QTimer::timeout, this, &TextMessageIndicator::hide);

    // setup autoHide timer details
    mAutoHideTimer->setSingleShot(true);
}

void TextMessageIndicator::display(const QString &message, [[maybe_unused]] const QString &details, Icon icon, int durationMs)
{
    mAutoHideTimer->stop();
    mMessageWidget->setText(message);
    switch (icon) {
    case None:
        mMessageWidget->setMessageType(KMessageWidget::Positive);
        break;
    case Info:
        mMessageWidget->setMessageType(KMessageWidget::Information);
        break;
    case Warning:
        mMessageWidget->setMessageType(KMessageWidget::Warning);
        break;
    case Error:
        mMessageWidget->setMessageType(KMessageWidget::Error);
        break;
    }
    mMessageWidget->setTextFormat(Qt::RichText);
    mMessageWidget->setWordWrap(true);

    // make sure the widget's size is up-to-date in its hidden state
    mMessageWidget->ensurePolished();
    mMessageWidget->adjustSize();
    adjustSize();
    mMessageWidget->show();
    move(parentWidget()->width() - width() - 10, 10);
    show();
    if (durationMs > 0) {
        mAutoHideTimer->start(durationMs);
    }
}

#include "moc_textmessageindicator.cpp"
