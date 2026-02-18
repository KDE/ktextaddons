/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>
  based on code from kopete

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonswidgets_export.h"
#include <QWidget>

namespace TextEmoticonsWidgets
{
/*!
 * \class TextEmoticonsWidgets::EmoticonTextEditSelector
 * \inmodule TextEmoticonsWidgets
 * \inheaderfile TextEmoticonsWidgets/EmoticonTextEditSelector
 *
 * \brief A widget to select emojis.
 *
 * \image emoticontexteditselector.png "EmoticonTextEditSelector"
 *
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSWIDGETS_EXPORT EmoticonTextEditSelector : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructs an EmoticonTextEditSelector with the given parent
     * \param parent The parent widget
     */
    explicit EmoticonTextEditSelector(QWidget *parent = nullptr);
    /*!
     * \brief Destroys the EmoticonTextEditSelector
     */
    ~EmoticonTextEditSelector() override;

    /*!
     * \brief Focus the line edit for search.
     */
    void forceLineEditFocus();

    /*!
     * \brief Set whether the custom emoji category should be shown.
     * \param b true to show the custom emoji category, false otherwise
     * \sa customEmojiSupport()
     */
    void setCustomEmojiSupport(bool b);
    /*!
     * \brief Return whether the custom emoji category is enabled.
     * \return true if custom emoji support is enabled
     * \sa setCustomEmojiSupport()
     */
    [[nodiscard]] bool customEmojiSupport() const;

public:
    /*!
     * \brief Do all the magic of creating an TextEmoticonsCore::UnicodeEmoticonManager and loading the categories and emojis to the widget.
     */
    void loadEmoticons();

Q_SIGNALS:
    /*!
     * \brief This signal is emitted each time the user selects an emoji.
     * \param character The actual emoji character
     * \sa insertEmojiIdentifier
     */
    void insertEmoji(const QString &character);
    /*!
     * \brief This signal is emitted each time the user selects an emoji.
     * \param identifier The identifier of the emoji like eg. ":face_with_raised_eyebrow:"
     * \sa insertEmoji
     */
    void insertEmojiIdentifier(const QString &identifier);

private:
    class EmoticonTextEditSelectorPrivate;
    std::unique_ptr<EmoticonTextEditSelectorPrivate> const d;
};
}
