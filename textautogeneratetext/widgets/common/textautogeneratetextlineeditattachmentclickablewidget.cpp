/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineeditattachmentclickablewidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextLineEditAttachmentClickableWidget::TextAutoGenerateTextLineEditAttachmentClickableWidget(const QString &fileName, QWidget *parent)
    : QWidget{parent}
    , mFileName(fileName)
    , mClickableLabel(new TextAutoGenerateTextLineEditAttachmentClickableLabel(this))
    , mFileNameLabel(new QLabel(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mFileNameLabel->setObjectName(u"mFileNameLabel"_s);
    mainLayout->addWidget(mFileNameLabel);
    // TODO show MimeType ?

    mClickableLabel->setObjectName(u"mClickableLabel"_s);
    mainLayout->addWidget(mClickableLabel);
    connect(mClickableLabel,
            &TextAutoGenerateTextLineEditAttachmentClickableLabel::clicked,
            this,
            &TextAutoGenerateTextLineEditAttachmentClickableWidget::slotRemove);
}

TextAutoGenerateTextLineEditAttachmentClickableWidget::~TextAutoGenerateTextLineEditAttachmentClickableWidget() = default;

void TextAutoGenerateTextLineEditAttachmentClickableWidget::slotRemove()
{
    // TODO
}

TextAutoGenerateTextLineEditAttachmentClickableLabel::TextAutoGenerateTextLineEditAttachmentClickableLabel(QWidget *parent)
    : QLabel(parent)
{
    setToolTip(i18nc("@info:tooltip", "Remove"));
    setPixmap(QIcon::fromTheme(u"delete"_s).pixmap(18, 18));
}

TextAutoGenerateTextLineEditAttachmentClickableLabel::~TextAutoGenerateTextLineEditAttachmentClickableLabel() = default;

void TextAutoGenerateTextLineEditAttachmentClickableLabel::mousePressEvent(QMouseEvent *event)
{
    Q_EMIT clicked();
    QLabel::mousePressEvent(event);
}

#include "moc_textautogeneratetextlineeditattachmentclickablewidget.cpp"
