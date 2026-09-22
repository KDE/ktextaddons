/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemanagetagswidget.h"
#include "core/models/textautogeneratetagsmodel.h"
#include "textautogeneratetagdialog.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QHBoxLayout>
#include <QListView>
#include <QPointer>
#include <QToolButton>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

TextAutoGenerateManageTagsWidget::TextAutoGenerateManageTagsWidget(QWidget *parent)
    : QWidget{parent}
    , mTagsListView(new QListView(this))
    , mTagsModel(new TextAutoGenerateTagsModel(this))
    , mAddButton(new QToolButton(this))
    , mModifyButton(new QToolButton(this))
    , mRemoveButton(new QToolButton(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mTagsListView->setObjectName(u"mTagsListView"_s);
    mTagsListView->setModel(mTagsModel);
    mTagsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(mTagsListView);
    connect(mTagsListView, &QListView::doubleClicked, this, qOverload<const QModelIndex &>(&TextAutoGenerateManageTagsWidget::slotModifyTag));
    connect(mTagsListView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &TextAutoGenerateManageTagsWidget::updateButtons);

    auto buttonLayout = new QVBoxLayout;
    buttonLayout->setObjectName(u"buttonLayout"_s);
    buttonLayout->setContentsMargins({});
    mainLayout->addLayout(buttonLayout);

    mAddButton->setObjectName(u"mAddButton"_s);
    mAddButton->setIcon(QIcon::fromTheme(u"list-add"_s));
    mAddButton->setToolTip(i18nc("@info:tooltip", "Add Tag…"));
    mAddButton->setAutoRaise(true);
    buttonLayout->addWidget(mAddButton);
    connect(mAddButton, &QToolButton::clicked, this, &TextAutoGenerateManageTagsWidget::slotAddTag);

    mModifyButton->setObjectName(u"mModifyButton"_s);
    mModifyButton->setIcon(QIcon::fromTheme(u"edit-rename"_s));
    mModifyButton->setToolTip(i18nc("@info:tooltip", "Modify Tag…"));
    mModifyButton->setAutoRaise(true);
    buttonLayout->addWidget(mModifyButton);
    connect(mModifyButton, &QToolButton::clicked, this, qOverload<>(&TextAutoGenerateManageTagsWidget::slotModifyTag));

    mRemoveButton->setObjectName(u"mRemoveButton"_s);
    mRemoveButton->setIcon(QIcon::fromTheme(u"list-remove"_s));
    mRemoveButton->setToolTip(i18nc("@info:tooltip", "Remove Tag"));
    mRemoveButton->setAutoRaise(true);
    buttonLayout->addWidget(mRemoveButton);
    connect(mRemoveButton, &QToolButton::clicked, this, &TextAutoGenerateManageTagsWidget::slotRemoveTag);

    buttonLayout->addStretch(1);

    updateButtons();
}

TextAutoGenerateManageTagsWidget::~TextAutoGenerateManageTagsWidget() = default;

void TextAutoGenerateManageTagsWidget::setTags(const QList<TextAutoGenerateText::TextAutoGenerateTag> &tags)
{
    mTagsModel->setTags(tags);
    updateButtons();
}

QList<TextAutoGenerateText::TextAutoGenerateTag> TextAutoGenerateManageTagsWidget::tags() const
{
    return mTagsModel->tags();
}

void TextAutoGenerateManageTagsWidget::slotAddTag()
{
    QPointer<TextAutoGenerateTagDialog> dialog(new TextAutoGenerateTagDialog(this));
    if (dialog->exec()) {
        mTagsModel->addTag(dialog->tag());
    }
    delete dialog;
}

void TextAutoGenerateManageTagsWidget::slotModifyTag()
{
    slotModifyTag(mTagsListView->currentIndex());
}

void TextAutoGenerateManageTagsWidget::slotModifyTag(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    QPointer<TextAutoGenerateTagDialog> dialog(new TextAutoGenerateTagDialog(this));
    dialog->setTag(tagFromIndex(index));
    if (dialog->exec()) {
        mTagsModel->updateTag(dialog->tag());
    }
    delete dialog;
}

void TextAutoGenerateManageTagsWidget::slotRemoveTag()
{
    const QModelIndex index = mTagsListView->currentIndex();
    if (!index.isValid()) {
        return;
    }
    const QString name = index.data(TextAutoGenerateTagsModel::Name).toString();
    if (KMessageBox::questionTwoActions(this,
                                        i18n("Do you want to remove this tag (%1)?", name),
                                        i18nc("@title:window", "Remove Tag"),
                                        KStandardGuiItem::remove(),
                                        KStandardGuiItem::cancel())
        == KMessageBox::PrimaryAction) {
        mTagsModel->removeTag(index.data(TextAutoGenerateTagsModel::Identifier).toByteArray());
        updateButtons();
    }
}

TextAutoGenerateText::TextAutoGenerateTag TextAutoGenerateManageTagsWidget::tagFromIndex(const QModelIndex &index) const
{
    TextAutoGenerateText::TextAutoGenerateTag tag;
    tag.setIdentifier(index.data(TextAutoGenerateTagsModel::Identifier).toByteArray());
    tag.setName(index.data(TextAutoGenerateTagsModel::Name).toString());
    tag.setColor(index.data(TextAutoGenerateTagsModel::Color).value<QColor>());
    return tag;
}

void TextAutoGenerateManageTagsWidget::updateButtons()
{
    const bool hasSelection = mTagsListView->selectionModel()->hasSelection();
    mModifyButton->setEnabled(hasSelection);
    mRemoveButton->setEnabled(hasSelection);
}

#include "moc_textautogeneratemanagetagswidget.cpp"
