/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineeditattachmentclickablewidget.h"

#include <KIconLoader>
#include <KLocalizedString>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QMimeDatabase>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;

TextAutoGenerateTextLineEditAttachmentClickableWidget::TextAutoGenerateTextLineEditAttachmentClickableWidget(const QString &name,
                                                                                                             const QByteArray &mimetype,
                                                                                                             QWidget *parent)
    : TextAutoGenerateTextLineEditAttachmentClickableWidget(parent)
{
    mFileNameLabel->setText(name);
    const QMimeDatabase db;
    const QMimeType mimeType = db.mimeTypeForName(QString::fromLatin1(mimetype));
    const QString mimeTypeIconName = mimeType.iconName();

    const QString mimeTypeIconPath = KIconLoader::global()->iconPath(mimeTypeIconName, KIconLoader::Small);
    mMimetypeLabel->setPixmap(QPixmap(mimeTypeIconPath));
}

TextAutoGenerateTextLineEditAttachmentClickableWidget::TextAutoGenerateTextLineEditAttachmentClickableWidget(const QString &fileName, QWidget *parent)
    : TextAutoGenerateTextLineEditAttachmentClickableWidget(parent)
{
    mFileName = fileName;
    const QFileInfo info(fileName);
    mFileNameLabel->setText(info.fileName());
    mFileNameLabel->setToolTip(mFileName);

    const QMimeDatabase db;
    const QMimeType mimeType = db.mimeTypeForFile(info);
    const QString mimeTypeIconName = mimeType.iconName();

    const QString mimeTypeIconPath = KIconLoader::global()->iconPath(mimeTypeIconName, KIconLoader::Small);
    mMimetypeLabel->setPixmap(QPixmap(mimeTypeIconPath));
}

TextAutoGenerateTextLineEditAttachmentClickableWidget::TextAutoGenerateTextLineEditAttachmentClickableWidget(QWidget *parent)
    : QWidget{parent}
    , mClickableLabel(new TextAutoGenerateTextLineEditAttachmentClickableLabel(this))
    , mFileNameLabel(new QLabel(this))
    , mMimetypeLabel(new QLabel(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mMimetypeLabel->setObjectName(u"mMimetypeLabel"_s);
    mainLayout->addWidget(mMimetypeLabel);

    mFileNameLabel->setObjectName(u"mFileNameLabel"_s);
    mainLayout->addWidget(mFileNameLabel);

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
    Q_EMIT remove(mFileName);
}

QString TextAutoGenerateTextLineEditAttachmentClickableWidget::fileName() const
{
    return mFileName;
}

TextAutoGenerateTextLineEditAttachmentClickableLabel::TextAutoGenerateTextLineEditAttachmentClickableLabel(QWidget *parent)
    : QLabel(parent)
{
    setToolTip(i18nc("@info:tooltip", "Remove"));
    setPixmap(QIcon::fromTheme(u"delete"_s).pixmap(24, 24));
}

TextAutoGenerateTextLineEditAttachmentClickableLabel::~TextAutoGenerateTextLineEditAttachmentClickableLabel() = default;

void TextAutoGenerateTextLineEditAttachmentClickableLabel::mousePressEvent(QMouseEvent *event)
{
    Q_EMIT clicked();
    QLabel::mousePressEvent(event);
}

#include "moc_textautogeneratetextlineeditattachmentclickablewidget.cpp"
