/*
  SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>
  based on code from kopete

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonswidgets_export.h"
#include <KActionMenu>
namespace TextEmoticonsWidgets
{
/*!
 * \class TextEmoticonsWidgets::EmoticonTextEditAction
 * \inmodule TextEmoticonsWidgets
 * \inheaderfile TextEmoticonsWidgets/EmoticonTextEditAction
 *
 * \brief Action to select emojis.
 *
 * Opens an EmoticonTextEditSelector to select an emoji.
 *
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSWIDGETS_EXPORT EmoticonTextEditAction : public KActionMenu
{
    Q_OBJECT
public:
    /*!
     * \brief Constructs an EmoticonTextEditAction with the given parent
     * \param parent The parent QObject
     */
    explicit EmoticonTextEditAction(QObject *parent);
    /*!
     * \brief Destroys the EmoticonTextEditAction
     */
    ~EmoticonTextEditAction() override;

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

Q_SIGNALS:
    /*!
     * \brief This signal is emitted each time the user selects an emoji.
     * \param character The actual emoji character
     * \sa EmoticonTextEditSelector::insertEmoticon
     */
    void insertEmoticon(const QString &);

private:
    class EmoticonTextEditActionPrivate;
    std::unique_ptr<EmoticonTextEditActionPrivate> const d;
};
}
