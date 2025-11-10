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
}

TextAutoGenerateTextLineEditAttachmentWidget::~TextAutoGenerateTextLineEditAttachmentWidget() = default;

void TextAutoGenerateTextLineEditAttachmentWidget::addAttachement(const QString &fileName)
{
    if (mMap.contains(fileName)) {
        return;
    }
    auto clickableWidget = new TextAutoGenerateTextLineEditAttachmentClickableWidget(fileName, this);
    connect(clickableWidget,
            &TextAutoGenerateTextLineEditAttachmentClickableWidget::remove,
            this,
            &TextAutoGenerateTextLineEditAttachmentWidget::slotRemoveAttachment);
    mMainLayout->addWidget(clickableWidget);
    mMap.insert(fileName, clickableWidget);
}

void TextAutoGenerateTextLineEditAttachmentWidget::slotRemoveAttachment(const QString &fileName)
{
    TextAutoGenerateTextLineEditAttachmentClickableWidget *userWidget = mMap.value(fileName);
    if (userWidget) {
        const int index = mMainLayout->indexOf(userWidget);
        if (index != -1) {
            userWidget->deleteLater();
            delete mMainLayout->takeAt(index);
            mMap.remove(fileName);
        }
    }
}

QList<TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo>
TextAutoGenerateTextLineEditAttachmentWidget::attachmentElementInfoList() const
{
    QList<TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo> lst;
    lst.reserve(mMap.count());
    for (const auto &[key, value] : mMap.asKeyValueRange()) {
        lst.append(TextAutoGenerateAttachmentUtils::createAttachmentElementInfoFromFile(value->fileName()));
    }
    return lst;
}

void TextAutoGenerateTextLineEditAttachmentWidget::clear()
{
    mMainLayout->clearAndDeleteWidgets();
    mMap.clear();
}

#include "moc_textautogeneratetextlineeditattachmentwidget.cpp"
