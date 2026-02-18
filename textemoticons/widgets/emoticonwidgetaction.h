/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textemoticonswidgets_export.h"
#include <QWidgetAction>

class QHBoxLayout;
namespace TextEmoticonsWidgets
{
class EmoticonWidgetActionWidget;
/*!
 * \class TextEmoticonsWidgets::EmoticonWidgetAction
 * \inmodule TextEmoticonsWidgets
 * \inheaderfile TextEmoticonsWidgets/EmoticonWidgetAction
 *
 * \brief Action to display and select emojis in a widget action.
 *
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSWIDGETS_EXPORT EmoticonWidgetAction : public QWidgetAction
{
    Q_OBJECT
public:
    /*!
     * \class TextEmoticonsWidgets::EmoticonWidgetAction::EmoticonInfo
     * \inmodule TextEmoticonsWidgets
     *
     * \brief Represents the information of a selected emoticon.
     */
    struct TEXTEMOTICONSWIDGETS_EXPORT EmoticonInfo {
        QString emojiStr; /*!< The emoji character string */
        QString emojiIdentifier; /*!< The emoji identifier (e.g., ":smile:") */
        /*!
         * \brief Checks if this emoticon info is valid
         * \return true if both emojiStr and emojiIdentifier are non-empty
         */
        [[nodiscard]] bool isValid() const;
    };

    /*!
     * \brief Constructs an EmoticonWidgetAction with the given parent
     * \param parent The parent QObject
     */
    explicit EmoticonWidgetAction(QObject *parent = nullptr);
    /*!
     * \brief Destroys the EmoticonWidgetAction
     */
    ~EmoticonWidgetAction() override;

Q_SIGNALS:
    /*!
     * \brief Emitted when an emoji character is selected
     * \param str The emoji character string
     */
    void insertEmoji(const QString &str);
    /*!
     * \brief Emitted when an emoji identifier is selected
     * \param identifier The emoji identifier (e.g., ":smile:")
     */
    void insertEmojiIdentifier(const QString &identifier);
    /*!
     * \brief Emitted when the emoji selection dialog is requested
     */
    void selectEmoji();

private:
    EmoticonWidgetActionWidget *const mEmoticonWidgetActionWidget;
};
}

Q_DECLARE_TYPEINFO(TextEmoticonsWidgets::EmoticonWidgetAction::EmoticonInfo, Q_RELOCATABLE_TYPE);
