/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammarresultwidget.h"
using namespace Qt::Literals::StringLiterals;

#include "grammarresulttextedit.h"

#include <KLocalizedString>

#include <QHBoxLayout>
#include <QToolButton>
using namespace TextGrammarCheck;
GrammarResultWidget::GrammarResultWidget(QWidget *parent)
    : QWidget(parent)
    , mResult(new GrammarResultTextEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainlayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    mExtraWidgetLayout = new QHBoxLayout;
    mExtraWidgetLayout->setContentsMargins({});
    mainLayout->addLayout(mExtraWidgetLayout);

    auto closeBtn = new QToolButton(this);
    closeBtn->setObjectName(u"close-button"_s);
    closeBtn->setIcon(QIcon::fromTheme(u"dialog-close"_s));
    closeBtn->setIconSize(QSize(16, 16));
    closeBtn->setToolTip(i18nc("@info:tooltip", "Close"));
    closeBtn->setAutoRaise(true);
    mExtraWidgetLayout->addWidget(closeBtn);
    mExtraWidgetLayout->addStretch(1);
    connect(closeBtn, &QToolButton::clicked, this, &GrammarResultWidget::closeChecker);

    mResult->setObjectName(u"grammarResult"_s);
    connect(mResult, &GrammarResultTextEdit::replaceText, this, &GrammarResultWidget::replaceText);
    connect(mResult, &GrammarResultTextEdit::checkAgain, this, &GrammarResultWidget::checkAgain);
    connect(mResult, &GrammarResultTextEdit::closeChecker, this, &GrammarResultWidget::closeChecker);
    connect(mResult, &GrammarResultTextEdit::configure, this, &GrammarResultWidget::configure);
    mainLayout->addWidget(mResult);
}

GrammarResultWidget::~GrammarResultWidget() = default;

void GrammarResultWidget::addExtraWidget()
{
}

void GrammarResultWidget::setText(const QString &str)
{
    mResult->setText(str);
}

void GrammarResultWidget::applyGrammarResult(const QVector<GrammarError> &infos)
{
    mResult->applyGrammarResult(infos);
}

#include "moc_grammarresultwidget.cpp"
