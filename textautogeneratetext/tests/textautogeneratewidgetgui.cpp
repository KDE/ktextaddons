/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratewidgetgui.h"
#include <QHBoxLayout>
#include <QPushButton>

TextAutoGenerateWidgetGui::TextAutoGenerateWidgetGui(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins({});
    auto configureButton = new QPushButton(QStringLiteral("Configure..."), this);
    mainLayout->addWidget(configureButton);
    connect(configureButton, &QPushButton::clicked, this, [this]() {
        // TODO
    });

    auto showGenerateDialogButton = new QPushButton(QStringLiteral("Show Dialog..."), this);
    mainLayout->addWidget(showGenerateDialogButton);
    connect(showGenerateDialogButton, &QPushButton::clicked, this, [this]() {
        // TODO
    });
}

TextAutoGenerateWidgetGui::~TextAutoGenerateWidgetGui() = default;

#include "moc_textautogeneratewidgetgui.cpp"
