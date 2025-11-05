/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineeditattachmentwidget.h"
#include "textautogeneratetextlineeditattachmentclickablewidget.h"
#include "widgets/common/textautogenerateflowlayout.h"
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextLineEditAttachmentWidget::TextAutoGenerateTextLineEditAttachmentWidget(QWidget *parent)
    : QWidget{parent}
    , mMainLayout(new TextAutoGenerateFlowLayout(this))
{
    mMainLayout->setObjectName(u"mainLayout"_s);
    mMainLayout->setContentsMargins({});
    // TODO
}

TextAutoGenerateTextLineEditAttachmentWidget::~TextAutoGenerateTextLineEditAttachmentWidget() = default;

void TextAutoGenerateTextLineEditAttachmentWidget::addAttachement(const QString &fileName)
{
#if 0
    const QString &roomName = info.roomName;
    if (mMap.contains(roomName)) {
        return;
    }
#endif
    auto clickableWidget = new TextAutoGenerateTextLineEditAttachmentClickableLabel(this);
    mMainLayout->addWidget(clickableWidget);
}

#include "moc_textautogeneratetextlineeditattachmentwidget.cpp"
