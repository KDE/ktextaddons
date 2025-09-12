/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolswidget.h"
#include "widgets/common/textautogenerateflowlayout.h"
#include <QToolButton>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateToolsWidget::TextAutoGenerateToolsWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new TextAutoGenerateFlowLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    // TODO add QToolButton from tools manager
}

TextAutoGenerateToolsWidget::~TextAutoGenerateToolsWidget() = default;

#include "moc_textautogeneratetoolswidget.cpp"
