/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratenotworkingwidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using namespace TextAutogenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutogenerateNotWorkingWidget::TextAutogenerateNotWorkingWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    auto configureButton = new QPushButton(i18n("Configure..."), this);
    configureButton->setObjectName("configureButton"_L1);
    connect(configureButton, &QPushButton::clicked, this, &TextAutogenerateNotWorkingWidget::slotConfigure);
    mainLayout->addWidget(configureButton, 0, Qt::AlignVCenter);
    // TODO add button for configure it ?
    // TODO add message info
}

TextAutogenerateNotWorkingWidget::~TextAutogenerateNotWorkingWidget() = default;

void TextAutogenerateNotWorkingWidget::slotConfigure()
{
    // TODO
}

#include "moc_textautogeneratenotworkingwidget.cpp"
