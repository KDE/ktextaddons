/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratenotworkingwidget.h"
#include <KLocalizedString>
#include <KMessageWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using namespace TextAutogenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutogenerateNotWorkingWidget::TextAutogenerateNotWorkingWidget(QWidget *parent)
    : QWidget{parent}
    , mMessageWidget(new KMessageWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mMessageWidget->setObjectName("mMessageWidget"_L1);
    mainLayout->addWidget(mMessageWidget);
    mMessageWidget->setCloseButtonVisible(false);

    auto configureButton = new QPushButton(i18n("Configure..."), this);
    configureButton->setObjectName("configureButton"_L1);
    connect(configureButton, &QPushButton::clicked, this, &TextAutogenerateNotWorkingWidget::slotConfigure);
    mainLayout->addWidget(configureButton, 0, Qt::AlignVCenter);
}

TextAutogenerateNotWorkingWidget::~TextAutogenerateNotWorkingWidget() = default;

void TextAutogenerateNotWorkingWidget::setMessageError(const QString &str)
{
    mMessageWidget->setText(str);
    mMessageWidget->animatedShow();
}

void TextAutogenerateNotWorkingWidget::clearMessage()
{
    mMessageWidget->setText({});
    mMessageWidget->animatedHide();
}

void TextAutogenerateNotWorkingWidget::slotConfigure()
{
    // TODO
}

#include "moc_textautogeneratenotworkingwidget.cpp"
