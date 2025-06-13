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

    auto label = new QLabel(i18n("No instance found. Please add one."), this);
    label->setObjectName("label"_L1);
    mainLayout->addWidget(label);

    auto addInstanceButton = new QPushButton(i18nc("@action:button", "Add instance…"), this);
    label->setObjectName("addInstanceButton"_L1);
    mainLayout->addWidget(addInstanceButton);
    connect(addInstanceButton, &QPushButton::clicked, this, []() {
        // TODO
    });
}

TextAutoGenerateNotInstanceFoundWidget::~TextAutoGenerateNotInstanceFoundWidget() = default;

#include "moc_textautogeneratenotinstancefoundwidget.cpp"
