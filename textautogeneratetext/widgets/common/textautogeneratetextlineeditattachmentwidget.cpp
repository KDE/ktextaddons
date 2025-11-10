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
    // TODO
    return {};
}

QStringList TextAutoGenerateTextLineEditAttachmentWidget::attachmentFileNames() const
{
    QStringList fileNames;
    for (const auto &[key, value] : mMap.asKeyValueRange()) {
        fileNames << value->fileName();
    }
    return fileNames;
}

void TextAutoGenerateTextLineEditAttachmentWidget::clear()
{
    mMainLayout->clearAndDeleteWidgets();
    mMap.clear();
}

#include "moc_textautogeneratetextlineeditattachmentwidget.cpp"
