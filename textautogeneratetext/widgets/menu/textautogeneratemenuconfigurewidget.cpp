/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratemenuconfigurewidget.h"
#include "textautogeneratemenulistview.h"
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
TextAutoGenerateMenuConfigureWidget::TextAutoGenerateMenuConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mListView(new TextAutoGenerateMenuListView(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins({});

    mListView->setObjectName(QStringLiteral("mListView"));
    mainLayout->addWidget(mListView);
}

TextAutoGenerateMenuConfigureWidget::~TextAutoGenerateMenuConfigureWidget() = default;

void TextAutoGenerateMenuConfigureWidget::setTextInfos(const QList<TextAutoGenerateMenuTextInfo> &infos)
{
    mListView->setTextInfos(infos);
}

QList<TextAutoGenerateMenuTextInfo> TextAutoGenerateMenuConfigureWidget::textInfos() const
{
    return mListView->textInfos();
}

#include "moc_textautogeneratemenuconfigurewidget.cpp"
