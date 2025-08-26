/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchlistview.h"
using namespace Qt::Literals::StringLiterals;

#include "core/models/textautogeneratesearchmessagesmodel.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratesearchmessageutils.h"
#include "delegate/textautogeneratesearchlistviewdelegate.h"
#include <KLocalizedString>
#include <QEvent>
#include <QPainter>

using namespace TextAutoGenerateText;
TextAutoGenerateSearchListView::TextAutoGenerateSearchListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : TextAutoGenerateBaseListView(manager, parent)
    , mModel(new TextAutoGenerateSearchMessagesModel(this))
{
    auto delegate = new TextAutoGenerateSearchListViewDelegate(this);
    connect(delegate, &TextAutoGenerateSearchListViewDelegate::goToMessage, this, &TextAutoGenerateSearchListView::slotGoToMessage);
    mDelegate = delegate;
    setItemDelegate(mDelegate);
    setModel(mModel);
}

TextAutoGenerateSearchListView::~TextAutoGenerateSearchListView() = default;

void TextAutoGenerateSearchListView::setSearchMessages(const QList<TextAutoGenerateSearchMessage> &msgs)
{
    mModel->setSearchMessages(msgs);
}

void TextAutoGenerateSearchListView::slotGoToMessage(const QString &link)
{
    QString path = link;
    path = path.remove(TextAutoGenerateSearchMessageUtils::scheme() + u"://"_s);
    const QStringList pathList = path.split(u':');
    if (pathList.count() == 2) {
        mManager->goToMessage(pathList.at(0).toLatin1(), pathList.at(1).toLatin1());
    }
}

void TextAutoGenerateSearchListView::paintEvent(QPaintEvent *event)
{
    if (mModel->isEmpty()) {
        const QString label = i18n("No Messages Found.");

        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        if (!mTextColor.isValid()) {
            generalPaletteChanged();
        }
        p.setPen(mTextColor);
        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, label);
    } else {
        TextAutoGenerateBaseListView::paintEvent(event);
    }
}

void TextAutoGenerateSearchListView::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
}

bool TextAutoGenerateSearchListView::event(QEvent *ev)
{
    if (ev->type() == QEvent::ApplicationPaletteChange) {
        generalPaletteChanged();
    }
    return TextAutoGenerateBaseListView::event(ev);
}

QString TextAutoGenerateSearchListView::originalMessage(const QModelIndex &index) const
{
    return index.data(TextAutoGenerateSearchMessagesModel::PreviewText).toString();
}

#include "moc_textautogeneratesearchlistview.cpp"
