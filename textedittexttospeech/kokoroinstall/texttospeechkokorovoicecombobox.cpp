/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokorovoicecombobox.h"
#include "texttospeechkokoroutils.h"
#include <KLocalizedString>
#include <QAbstractItemView>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMouseEvent>
#include <QStandardItemModel>

using namespace TextEditTextToSpeech;
using namespace Qt::Literals::StringLiterals;

namespace
{
[[nodiscard]] QString genderName(QVoice::Gender gender)
{
    switch (gender) {
    case QVoice::Female:
        return i18nc("@item:intext gender of a voice", "Female");
    case QVoice::Male:
        return i18nc("@item:intext gender of a voice", "Male");
    case QVoice::Unknown:
        break;
    }
    return i18nc("@item:intext gender of a voice", "Unknown");
}

// "English (United States)": the language alone would not separate the
// american voices from the british ones.
[[nodiscard]] QString localeName(const QLocale &locale)
{
    return i18nc("@item:intext <language> (<country>)",
                 "%1 (%2)",
                 QLocale::languageToString(locale.language()),
                 QLocale::territoryToString(locale.territory()));
}
}

TextToSpeechKokoroVoiceComboBox::TextToSpeechKokoroVoiceComboBox(QWidget *parent)
    : QComboBox(parent)
{
    // A read only line edit is the only way to show the whole selection: the
    // text of a non editable combo box is the text of the current item.
    setEditable(true);
    setInsertPolicy(QComboBox::NoInsert);
    lineEdit()->setReadOnly(true);
    lineEdit()->installEventFilter(this);
    view()->installEventFilter(this);
    view()->viewport()->installEventFilter(this);

    fill();

    connect(model(), &QAbstractItemModel::dataChanged, this, [this](const QModelIndex &, const QModelIndex &, const QList<int> &roles) {
        if (mUpdatingSelection || (!roles.isEmpty() && !roles.contains(Qt::CheckStateRole))) {
            return;
        }
        updateDisplayText();
        Q_EMIT selectedVoicesChanged(selectedVoices());
    });
    // The current item changes with the keyboard, its text must not replace the selection.
    connect(this, &QComboBox::currentIndexChanged, this, &TextToSpeechKokoroVoiceComboBox::updateDisplayText);
    updateDisplayText();
}

TextToSpeechKokoroVoiceComboBox::~TextToSpeechKokoroVoiceComboBox() = default;

void TextToSpeechKokoroVoiceComboBox::fill()
{
    auto voiceModel = new QStandardItemModel(this);
    const QList<TextToSpeechKokoroUtils::KokoroVoice> listVoices = TextToSpeechKokoroUtils::kokoroVoices();
    for (const auto &voice : listVoices) {
        auto item = new QStandardItem(TextToSpeechKokoroUtils::voiceIcon(voice),
                                      i18nc("@item:inlistbox <voice name> (<gender>)", "%1 (%2)", voice.name, genderName(voice.gender)));
        item->setToolTip(
            i18nc("@info:tooltip <voice name> (<language>, <gender>)", "%1 (%2, %3)", voice.name, localeName(voice.locale), genderName(voice.gender)));
        item->setData(voice.identifier, Qt::UserRole);
        item->setCheckable(true);
        item->setCheckState(Qt::Unchecked);
        voiceModel->appendRow(item);
    }
    setModel(voiceModel);
}

QStringList TextToSpeechKokoroVoiceComboBox::selectedVoices() const
{
    QStringList identifiers;
    for (int i = 0, total = count(); i < total; ++i) {
        if (itemData(i, Qt::CheckStateRole).value<Qt::CheckState>() == Qt::Checked) {
            identifiers.append(itemData(i).toString());
        }
    }
    return identifiers;
}

void TextToSpeechKokoroVoiceComboBox::setSelectedVoices(const QStringList &identifiers)
{
    // One signal for the whole selection, not one per item.
    mUpdatingSelection = true;
    for (int i = 0, total = count(); i < total; ++i) {
        setItemData(i, identifiers.contains(itemData(i).toString()) ? Qt::Checked : Qt::Unchecked, Qt::CheckStateRole);
    }
    mUpdatingSelection = false;
    updateDisplayText();
    Q_EMIT selectedVoicesChanged(selectedVoices());
}

void TextToSpeechKokoroVoiceComboBox::toggleItem(const QModelIndex &index)
{
    if (!index.isValid()) {
        return;
    }
    const auto state = index.data(Qt::CheckStateRole).value<Qt::CheckState>();
    model()->setData(index, state == Qt::Checked ? Qt::Unchecked : Qt::Checked, Qt::CheckStateRole);
}

void TextToSpeechKokoroVoiceComboBox::updateDisplayText()
{
    QStringList names;
    for (int i = 0, total = count(); i < total; ++i) {
        if (itemData(i, Qt::CheckStateRole).value<Qt::CheckState>() == Qt::Checked) {
            names.append(itemText(i));
        }
    }
    const QString text = names.isEmpty() ? i18nc("@info:placeholder", "No voice selected") : names.join(", "_L1);
    lineEdit()->setText(lineEdit()->fontMetrics().elidedText(text, Qt::ElideRight, lineEdit()->width()));
    setToolTip(names.isEmpty() ? QString() : text);
}

bool TextToSpeechKokoroVoiceComboBox::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == lineEdit() && event->type() == QEvent::MouseButtonPress) {
        // The line edit is read only: clicking it opens the popup as the arrow does.
        showPopup();
        return true;
    }
    if (watched == view()->viewport() && event->type() == QEvent::MouseButtonRelease) {
        const auto mouseEvent = static_cast<QMouseEvent *>(event);
        toggleItem(view()->indexAt(mouseEvent->position().toPoint()));
        // Swallowed: the popup has to stay open, several voices can be checked.
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

void TextToSpeechKokoroVoiceComboBox::resizeEvent(QResizeEvent *event)
{
    QComboBox::resizeEvent(event);
    // The elided text depends on the width of the line edit.
    updateDisplayText();
}

#include "moc_texttospeechkokorovoicecombobox.cpp"
