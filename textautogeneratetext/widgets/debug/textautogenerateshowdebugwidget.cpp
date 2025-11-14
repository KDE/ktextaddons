/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateshowdebugwidget.h"
#include "textautogeneratejsonplaintexteditwidget.h"
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateShowDebugWidget::TextAutoGenerateShowDebugWidget(QWidget *parent)
    : QWidget{parent}
    , mJsonPlainTextEditWidget(new TextAutoGenerateJsonPlainTextEditWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mJsonPlainTextEditWidget->setObjectName(u"mJsonPlainTextEditWidget"_s);
    mainLayout->addWidget(mJsonPlainTextEditWidget);
}

TextAutoGenerateShowDebugWidget::~TextAutoGenerateShowDebugWidget() = default;

void TextAutoGenerateShowDebugWidget::setPlainText(const QString &text)
{
    mJsonPlainTextEditWidget->setPlainText(text);
}

#include "moc_textautogenerateshowdebugwidget.cpp"
