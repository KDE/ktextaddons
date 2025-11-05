/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineeditattachmentwidget.h"
#include "widgets/common/textautogenerateflowlayout.h"
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextLineEditAttachmentWidget::TextAutoGenerateTextLineEditAttachmentWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new TextAutoGenerateFlowLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
    // TODO
}

TextAutoGenerateTextLineEditAttachmentWidget::~TextAutoGenerateTextLineEditAttachmentWidget() = default;

#include "moc_textautogeneratetextlineeditattachmentwidget.cpp"
