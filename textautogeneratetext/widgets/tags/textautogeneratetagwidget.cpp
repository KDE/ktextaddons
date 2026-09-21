/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetagwidget.h"
#include <KColorButton>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

TextAutoGenerateTagWidget::TextAutoGenerateTagWidget(QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mColor(new KColorButton(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mName->setObjectName(u"mName"_s);
    mName->setClearButtonEnabled(true);
    mName->setPlaceholderText(i18nc("@info:placeholder", "Tag name…"));
    KLineEditEventHandler::catchReturnKey(mName);
    connect(mName, &QLineEdit::textChanged, this, &TextAutoGenerateTagWidget::slotNameChanged);

    mColor->setObjectName(u"mColor"_s);
    mColor->setAlphaChannelEnabled(false);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Color:"), mColor);
}

TextAutoGenerateTagWidget::~TextAutoGenerateTagWidget() = default;

void TextAutoGenerateTagWidget::slotNameChanged(const QString &name)
{
    Q_EMIT enableOkButton(!name.trimmed().isEmpty());
}

void TextAutoGenerateTagWidget::setTag(const TextAutoGenerateText::TextAutoGenerateTag &tag)
{
    mTag = tag;
    mName->setText(tag.name());
    // An invalid color would make KColorButton show black, which is indistinguishable from a real choice.
    mColor->setColor(tag.color().isValid() ? tag.color() : palette().color(QPalette::Highlight));
}

TextAutoGenerateText::TextAutoGenerateTag TextAutoGenerateTagWidget::tag() const
{
    // copy => we keep identifier
    TextAutoGenerateText::TextAutoGenerateTag tag = mTag;
    tag.setName(mName->text().trimmed());
    tag.setColor(mColor->color());
    return tag;
}

#include "moc_textautogeneratetagwidget.cpp"
