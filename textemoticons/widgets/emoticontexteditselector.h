/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>
  based on code from kopete

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonswidgets_export.h"
#include <QWidget>

namespace TextEmoticonsWidgets
{
/**
 * @brief The EmoticonTextEditSelector class
 *
 * @short A widget to select emojis.
 *
 * @image html emoticontexteditselector.png "EmoticonTextEditSelector"
 *
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSWIDGETS_EXPORT EmoticonTextEditSelector : public QWidget
{
    Q_OBJECT
public:
    explicit EmoticonTextEditSelector(QWidget *parent = nullptr);
    ~EmoticonTextEditSelector() override;

    /**
     * Focus the line edit for search.
     */
    void forceLineEditFocus();

    /**
     * Set whether the custom emoji category should be shown.
     * @see customEmojiSupport()
     */
    void setCustomEmojiSupport(bool b);
    /**
     * Return whether the custom emoji category is enabled.
     * @see setCustomEmojiSupport()
     */
    [[nodiscard]] bool customEmojiSupport() const;

public Q_SLOTS:
    /**
     * Do all the magic of creating an TextEmoticonsCore::UnicodeEmoticonManager and loading the categories and emojis to the widget.
     */
    void loadEmoticons();

Q_SIGNALS:
    /**
     * This signal is emitted each time the user selects an emoji.
     *
     * @param character The actual emoji character
     * @see insertEmojiIdentifier
     */
    void insertEmoji(const QString &character);
    /**
     * This signal is emitted each time the user selects an emoji.
     *
     * @brief insertEmojiIdentifier
     * @param identifier The identifier of the emoji like eg. ":face_with_raised_eyebrow:"
     * @see insertEmoji
     */
    void insertEmojiIdentifier(const QString &identifier);

private:
    class EmoticonTextEditSelectorPrivate;
    std::unique_ptr<EmoticonTextEditSelectorPrivate> const d;
};
}
