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
    mMessageWidget->hide();
    hide();

    connect(mAutoHideTimer, &QTimer::timeout, this, &TextMessageWidget::hide);

    mAutoHideTimer->setSingleShot(true);
}

void TextMessageWidget::setTextFormat(Qt::TextFormat textFormat)
{
    mMessageWidget->setTextFormat(textFormat);
}

void TextMessageWidget::showMessage(const QString &message, const QString &details, Icon icon, int durationMs)
{
    if (mAutoHideTimer->isActive()) {
        mAutoHideTimer->stop();
    }
    QString str = message;
    if (!details.isEmpty()) {
        str += u'\n' + details;
    }
    mMessageWidget->setText(str);
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

#include "moc_textmessagewidget.cpp"
