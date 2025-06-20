/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratenotinstancefoundwidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateNotInstanceFoundWidget::TextAutoGenerateNotInstanceFoundWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mainLayout->addStretch(1);
    auto label = new QLabel(i18n("No instance found. Please add one."), this);
    label->setObjectName("label"_L1);
    mainLayout->addWidget(label, 0, Qt::AlignHCenter);

    auto addInstanceButton = new QPushButton(i18nc("@action:button", "Add instance…"), this);
    addInstanceButton->setObjectName("addInstanceButton"_L1);
    mainLayout->addWidget(addInstanceButton, 0, Qt::AlignHCenter);
    mainLayout->addStretch(1);
    connect(addInstanceButton, &QPushButton::clicked, this, &TextAutoGenerateNotInstanceFoundWidget::addInstanceRequested);
}

TextAutoGenerateNotInstanceFoundWidget::~TextAutoGenerateNotInstanceFoundWidget() = default;

#include "moc_textautogeneratenotinstancefoundwidget.cpp"
