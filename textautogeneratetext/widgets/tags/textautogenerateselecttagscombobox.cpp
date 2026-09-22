/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateselecttagscombobox.h"
#include <KLocalizedString>
#include <QAbstractItemView>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPixmap>
#include <QStandardItemModel>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

namespace
{
[[nodiscard]] QIcon iconFromColor(const QColor &color)
{
    if (!color.isValid()) {
        return {};
    }
    QPixmap pix(16, 16);
    pix.fill(color);
    return QIcon(pix);
}
}

TextAutoGenerateSelectTagsComboBox::TextAutoGenerateSelectTagsComboBox(QWidget *parent)
    : QComboBox(parent)
    , mTagsModel(new QStandardItemModel(this))
{
    // A read only line edit is the only way to show the whole selection: the text of a non editable
    // combo box is the text of the current item.
    setEditable(true);
    setInsertPolicy(QComboBox::NoInsert);
    lineEdit()->setReadOnly(true);
    lineEdit()->installEventFilter(this);
    view()->installEventFilter(this);
    view()->viewport()->installEventFilter(this);

    setModel(mTagsModel);

    connect(mTagsModel, &QAbstractItemModel::dataChanged, this, [this](const QModelIndex &, const QModelIndex &, const QList<int> &roles) {
        if (mUpdatingSelection || (!roles.isEmpty() && !roles.contains(Qt::CheckStateRole))) {
            return;
        }
        updateDisplayText();
        Q_EMIT selectedTagsChanged(selectedTags());
    });
    // The current item changes with the keyboard, its text must not replace the selection.
    connect(this, &QComboBox::currentIndexChanged, this, &TextAutoGenerateSelectTagsComboBox::updateDisplayText);
    updateDisplayText();
}

TextAutoGenerateSelectTagsComboBox::~TextAutoGenerateSelectTagsComboBox() = default;

void TextAutoGenerateSelectTagsComboBox::setTags(const QList<TextAutoGenerateText::TextAutoGenerateTag> &tags)
{
    // Filling is not a change of selection: the signal is emitted once, at the end.
    mUpdatingSelection = true;
    mTagsModel->clear();
    for (const TextAutoGenerateTag &tag : tags) {
        auto item = new QStandardItem(iconFromColor(tag.color()), tag.name());
        item->setData(tag.identifier(), Qt::UserRole);
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
        mTagsModel->appendRow(item);
    }
    mUpdatingSelection = false;
    updateDisplayText();
    Q_EMIT selectedTagsChanged(selectedTags());
}

QList<QByteArray> TextAutoGenerateSelectTagsComboBox::selectedTags() const
{
    QList<QByteArray> identifiers;
    for (int i = 0, total = count(); i < total; ++i) {
        if (itemData(i, Qt::CheckStateRole).value<Qt::CheckState>() == Qt::Checked) {
            identifiers.append(itemData(i).toByteArray());
        }
    }
    return identifiers;
}

void TextAutoGenerateSelectTagsComboBox::setSelectedTags(const QList<QByteArray> &identifiers)
{
    // One signal for the whole selection, not one per item.
    mUpdatingSelection = true;
    for (int i = 0, total = count(); i < total; ++i) {
        setItemData(i, identifiers.contains(itemData(i).toByteArray()) ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
    }
    mUpdatingSelection = false;
    updateDisplayText();
    Q_EMIT selectedTagsChanged(selectedTags());
}

void TextAutoGenerateSelectTagsComboBox::toggleItem(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    const auto state = index.data(Qt::CheckStateRole).value<Qt::CheckState>();
    mTagsModel->setData(index, state == Qt::Checked ? Qt::Unchecked : Qt::Checked, Qt::CheckStateRole);
}

void TextAutoGenerateSelectTagsComboBox::updateDisplayText()
{
    QStringList names;
    for (int i = 0, total = count(); i < total; ++i) {
        if (itemData(i, Qt::CheckStateRole).value<Qt::CheckState>() == Qt::Checked) {
            names.append(itemText(i));
        }
    }
    const QString text = names.isEmpty() ? i18nc("@info:placeholder", "No tag selected") : names.join(", "_L1);
    lineEdit()->setText(lineEdit()->fontMetrics().elidedText(text, Qt::ElideRight, lineEdit()->width()));
    // On the line edit and not on the combo box: an empty tool tip falls back to the one the caller
    // set on the combo box, which describes what the selection is used for.
    lineEdit()->setToolTip(names.isEmpty() ? QString() : text);
}

bool TextAutoGenerateSelectTagsComboBox::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == lineEdit() && event->type() == QEvent::MouseButtonPress) {
        // The line edit is read only: clicking it opens the popup as the arrow does.
        showPopup();
        return true;
    }
    if (watched == view()->viewport() && event->type() == QEvent::MouseButtonRelease) {
        const auto mouseEvent = static_cast<QMouseEvent *>(event);
        toggleItem(view()->indexAt(mouseEvent->position().toPoint()));
        // Swallowed: the popup has to stay open, several tags can be checked.
        return true;
    }
    if (watched == view() && event->type() == QEvent::KeyPress) {
        const auto keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Space || keyEvent->key() == Qt::Key_Select) {
            toggleItem(view()->currentIndex());
            return true;
        }
    }
    return QComboBox::eventFilter(watched, event);
}

void TextAutoGenerateSelectTagsComboBox::resizeEvent(QResizeEvent *event)
{
    QComboBox::resizeEvent(event);
    // The elided text depends on the width of the line edit.
    updateDisplayText();
}

#include "moc_textautogenerateselecttagscombobox.cpp"
