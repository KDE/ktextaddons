/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchwidget.h"
#include "widgets/view/textautogeneratesearchlistview.h"
#include <KLocalizedString>
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
TextAutoGenerateSearchWidget::TextAutoGenerateSearchWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateSearchListView(new TextAutoGenerateSearchListView(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mTextAutoGenerateSearchListView->setObjectName(QStringLiteral("mTextAutoGenerateSearchListView"));
    mainLayout->addWidget(mTextAutoGenerateSearchListView);
}

TextAutoGenerateSearchWidget::~TextAutoGenerateSearchWidget() = default;

#include "moc_textautogeneratesearchwidget.cpp"
