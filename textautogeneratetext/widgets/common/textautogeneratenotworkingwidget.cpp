/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratenotworkingwidget.h"
#include "widgets/textautogenerateconfiguredialog.h"
#include <KLocalizedString>
#include <KMessageWidget>
#include <QPushButton>
#include <QVBoxLayout>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateNotWorkingWidget::TextAutoGenerateNotWorkingWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mMessageWidget(new KMessageWidget(this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mMessageWidget->setObjectName("mMessageWidget"_L1);
    mainLayout->addWidget(mMessageWidget, 0, Qt::AlignVCenter);
    mMessageWidget->setCloseButtonVisible(false);
    mMessageWidget->setMessageType(KMessageWidget::MessageType::Error);

    auto configureButton = new QPushButton(i18n("Configure…"), this);
    configureButton->setObjectName("configureButton"_L1);
    connect(configureButton, &QPushButton::clicked, this, &TextAutoGenerateNotWorkingWidget::slotConfigure);
    mainLayout->addWidget(configureButton, 0, Qt::AlignVCenter);
    mainLayout->addStretch(1);
}

TextAutoGenerateNotWorkingWidget::~TextAutoGenerateNotWorkingWidget() = default;

void TextAutoGenerateNotWorkingWidget::setMessageError(const QString &str)
{
    mMessageWidget->setText(str);
    mMessageWidget->animatedShow();
}

void TextAutoGenerateNotWorkingWidget::clearMessage()
{
    mMessageWidget->setText({});
    mMessageWidget->animatedHide();
}

void TextAutoGenerateNotWorkingWidget::slotConfigure()
{
    TextAutoGenerateText::TextAutoGenerateConfigureDialog d(mManager, this);
    d.exec();
}

#include "moc_textautogeneratenotworkingwidget.cpp"
