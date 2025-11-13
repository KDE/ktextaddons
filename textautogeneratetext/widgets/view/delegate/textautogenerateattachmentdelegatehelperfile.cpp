/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateattachmentdelegatehelperfile.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include <KIconLoader>
#include <QMimeDatabase>
#include <QPainter>
#include <QPixmap>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAttachmentDelegateHelperFile::TextAutoGenerateAttachmentDelegateHelperFile(QObject *parent)
    : TextAutoGenerateAttachmentDelegateHelperBase{parent}
{
}

TextAutoGenerateAttachmentDelegateHelperFile::~TextAutoGenerateAttachmentDelegateHelperFile() = default;

// Icon + text
void TextAutoGenerateAttachmentDelegateHelperFile::draw(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                                        QPainter *painter,
                                                        QRect attachmentsRect,
                                                        const QModelIndex &index,
                                                        const QStyleOptionViewItem &option) const
{
    const FileLayout layout = doLayout(msgAttach, option, attachmentsRect.width());
    // TODO add msgAttach.mimeType()

    // TODO cache it.
    const QMimeDatabase db;
    const QMimeType mimeType = db.mimeTypeForName(QString::fromLatin1(layout.mimetype));
    const QString mimeTypeIconName = mimeType.iconName();
    qDebug() << " mimeTypeIconName " << mimeTypeIconName;
    qDebug() << " layout.name " << layout.name;
    const QString mimeTypeIconPath = KIconLoader::global()->iconPath(mimeTypeIconName, KIconLoader::Small);
    const QPixmap pix(mimeTypeIconPath);

    qDebug() << " mimeTypeIconPath " << mimeTypeIconPath;
    const QPixmap scaledPixmap = pix.scaled(25, 25, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    painter->drawPixmap(attachmentsRect.bottomRight(), scaledPixmap);

    qDebug() << " TextAutoGenerateAttachmentDelegateHelperFile::draw";
    // TODO
}

QSize TextAutoGenerateAttachmentDelegateHelperFile::sizeHint(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                                             const QModelIndex &index,
                                                             int maxWidth,
                                                             const QStyleOptionViewItem &option) const
{
    const FileLayout layout = doLayout(msgAttach, option, maxWidth);
    // TODO
    return QSize(50, 50);
}

TextAutoGenerateAttachmentDelegateHelperFile::FileLayout
TextAutoGenerateAttachmentDelegateHelperFile::doLayout(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                                       const QStyleOptionViewItem &option,
                                                       int attachmentsWidth) const
{
    FileLayout layout;
    layout.mimetype = msgAttach.mimeType();
    layout.name = msgAttach.name();

    // TODO
    return layout;
}

#include "moc_textautogenerateattachmentdelegatehelperfile.cpp"
