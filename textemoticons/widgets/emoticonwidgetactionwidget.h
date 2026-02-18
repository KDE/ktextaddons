/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textemoticonswidgets_export.h"
#include <QWidget>
#include <TextEmoticonsWidgets/EmoticonWidgetAction>

class QHBoxLayout;
namespace TextEmoticonsWidgets
{
/*!
 * \class TextEmoticonsWidgets::EmoticonWidgetActionWidget
 * \inmodule TextEmoticonsWidgets
 * \inheaderfile TextEmoticonsWidgets/EmoticonWidgetActionWidget
 *
 * \brief A widget for displaying and selecting recent and default emoticons.
 *
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSWIDGETS_EXPORT EmoticonWidgetActionWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructs an EmoticonWidgetActionWidget with the given parent
     * \param parent The parent widget
     */
    explicit EmoticonWidgetActionWidget(QWidget *parent = nullptr);
    /*!
     * \brief Destroys the EmoticonWidgetActionWidget
     */
    ~EmoticonWidgetActionWidget() override;

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
    [[nodiscard]] TEXTEMOTICONSWIDGETS_NO_EXPORT QList<EmoticonWidgetAction::EmoticonInfo> loadRecentsEmoticons() const;
    [[nodiscard]] TEXTEMOTICONSWIDGETS_NO_EXPORT EmoticonWidgetAction::EmoticonInfo generateEmoticonInfo(const QString &identifier) const;
    TEXTEMOTICONSWIDGETS_NO_EXPORT void addDefaultEmoticons(const QList<EmoticonWidgetAction::EmoticonInfo> &emojis);
    QHBoxLayout *const mMainLayout;
};
}
