/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchlistview.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratesearchmessagesmodel.h"
#include "core/textautogeneratesearchmessageutils.h"
#include "textautogeneratesearchlistviewdelegate.h"

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
    path = path.remove(TextAutoGenerateSearchMessageUtils::scheme() + QStringLiteral("://"));
    const QStringList pathList = path.split(QLatin1Char(':'));
    if (pathList.count() == 2) {
        mManager->goToMessage(pathList.at(0).toLatin1(), pathList.at(1).toLatin1());
    }
}

#include "moc_textautogeneratesearchlistview.cpp"
