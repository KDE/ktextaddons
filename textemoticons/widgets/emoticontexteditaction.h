/*
  SPDX-FileCopyrightText: 2012-2024 Laurent Montel <montel@kde.org>
  based on code from kopete

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonswidgets_export.h"
#include <KActionMenu>
namespace TextEmoticonsWidgets
{
/**
 * @brief The TextEmoticonsWidgets::EmoticonTextEditAction class
 *
 * @short Action to select emojis.
 *
 * Opens an EmoticonTextEditSelector to select an emoji.
 *
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSWIDGETS_EXPORT EmoticonTextEditAction : public KActionMenu
{
    Q_OBJECT
public:
    explicit EmoticonTextEditAction(QObject *parent);
    ~EmoticonTextEditAction() override;

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

Q_SIGNALS:
    /**
     * This signal is emitted each time the user selects an emoji.
     *
     * @param character The actual emoji character
     * @see EmoticonTextEditSelector::insertEmoticon
     */
    void insertEmoticon(const QString &);

private:
    class EmoticonTextEditActionPrivate;
    std::unique_ptr<EmoticonTextEditActionPrivate> const d;
};
}
