/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"
#include <QFrame>
class QTimer;
class QHBoxLayout;
class QTextEdit;
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::RichTextQuickTextFormat
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/RichTextQuickTextFormat
 *
 * \brief The RichTextQuickTextFormat class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT RichTextQuickTextFormat : public QFrame
{
    Q_OBJECT
public:
    enum class QuickTextFormatType : uint8_t {
        Unknown = 0,
        Bold = 1,
        Italic = 2,
        StrikeThrough = 4,
        CodeBlock = 8,
        BlockQuote = 16,
        InsertLink = 32,
        UnderLine = 64,
    };
    Q_ENUM(QuickTextFormatType)
    Q_DECLARE_FLAGS(QuickTextFormatTypes, QuickTextFormatType)
    Q_FLAG(QuickTextFormatTypes)

    /*!
     * \brief Constructor for RichTextQuickTextFormat
     * \param editor The text editor to attach to
     * \param parent The parent widget
     */
    explicit RichTextQuickTextFormat(QTextEdit *editor, QWidget *parent = nullptr);
    /*!
     * \brief Destructor for RichTextQuickTextFormat
     */
    ~RichTextQuickTextFormat() override;

    /*!
     * Returns the currently enabled text format types
     */
    [[nodiscard]] QuickTextFormatTypes formatTypes() const;
    /*!
     * Sets the enabled text format types
     * \param newFormatTypes The format types to enable
     */
    void setFormatTypes(QuickTextFormatTypes newFormatTypes);

    /*!
     * Returns whether the quick text format is enabled
     */
    [[nodiscard]] bool enabled() const;
    /*!
     * Sets whether the quick text format is enabled
     * \param newEnabled Whether to enable or disable
     */
    void setEnabled(bool newEnabled);

Q_SIGNALS:
    /*!
     * \brief Emitted when a quick text format is requested
     * \param type The type of text format requested
     */
    void quickTextFormatRequested(TextAddonsWidgets::RichTextQuickTextFormat::QuickTextFormatType type);

protected:
    /*!
     * \brief Handles events for the quick text format widget
     * \param watched The object being watched
     * \param event The event that occurred
     * \return True if the event was handled, false otherwise
     */
    [[nodiscard]] bool eventFilter(QObject *watched, QEvent *event) override;

private:
    TEXTADDONSWIDGETS_NO_EXPORT void updatePosition();
    TEXTADDONSWIDGETS_NO_EXPORT void initializeTextFormat();
    TEXTADDONSWIDGETS_NO_EXPORT void updateActions();
    TEXTADDONSWIDGETS_NO_EXPORT void slotSelectionChanged();
    QuickTextFormatTypes mFormatTypes = QuickTextFormatType::Unknown;
    QTextEdit *const mEditor;
    QTimer *const mUpdatePositionTimer;
    QHBoxLayout *const mMainLayout;
    bool mEnabled = true;
};
}
