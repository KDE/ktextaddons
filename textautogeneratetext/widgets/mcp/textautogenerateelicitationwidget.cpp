/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateelicitationwidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateElicitationWidget::TextAutoGenerateElicitationWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
}

TextAutoGenerateElicitationWidget::~TextAutoGenerateElicitationWidget() = default;

#include "moc_textautogenerateelicitationwidget.cpp"
