/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteurlrequesterwidget.h"
using namespace Qt::Literals::StringLiterals;

#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>

using namespace TextGrammarCheck;
GrammalecteUrlRequesterWidget::GrammalecteUrlRequesterWidget(QWidget *parent)
    : QWidget{parent}
    , mLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mLineEdit->setObjectName(u"mLineEdit"_s);
    mainLayout->addWidget(mLineEdit);
    KLineEditEventHandler::catchReturnKey(mLineEdit);
    auto selectUrlButton = new QToolButton(this);
    selectUrlButton->setText(u"…"_s);
    selectUrlButton->setObjectName(u"selectUrlButton"_s);
    mainLayout->addWidget(selectUrlButton);

    connect(selectUrlButton, &QToolButton::clicked, this, [this]() {
        const QString path = QFileDialog::getOpenFileName(this, i18n("Select Path"));
        mLineEdit->setText(path);
    });
}

GrammalecteUrlRequesterWidget::~GrammalecteUrlRequesterWidget() = default;

void GrammalecteUrlRequesterWidget::setPath(const QString &path)
{
    mLineEdit->setText(path);
}

QString GrammalecteUrlRequesterWidget::path() const
{
    return mLineEdit->text();
}

void GrammalecteUrlRequesterWidget::setPlaceholderText(const QString &text)
{
    mLineEdit->setPlaceholderText(text);
}

#include "moc_grammalecteurlrequesterwidget.cpp"
