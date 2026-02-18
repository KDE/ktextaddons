/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class QStackedWidget;
namespace TextAutoGenerateText
{
class TextAutoGenerateNotWorkingWidget;
class TextAutoGenerateNotInstanceFoundWidget;
class TextAutoGenerateManager;
class TextAutoGenerateWidget;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateStackWidget
 * \brief The TextAutoGenerateStackWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateStackWidget
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateStackWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructs a new TextAutoGenerateStackWidget
     * \param manager The TextAutoGenerateManager instance
     * \param parent The parent widget
     */
    explicit TextAutoGenerateStackWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     * \brief Destroys the TextAutoGenerateStackWidget
     */
    ~TextAutoGenerateStackWidget() override;

    /*!
     * \brief Sets the engine state and error message
     * \param state True if the engine is broken, false otherwise
     * \param errorMessage The error message to display
     */
    void setBrokenEngine(bool state, const QString &errorMessage);
    /*!
     * \brief Performs a search text operation
     */
    void slotSearchText();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotNeedToAddInstances();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigureInstances();
    QStackedWidget *const mStackedWidget;
    TextAutoGenerateNotWorkingWidget *const mTextAutoGenerateNotWorkingWidget;
    TextAutoGenerateNotInstanceFoundWidget *const mTextAutoGenerateNotInstanceFoundWidget;
    TextAutoGenerateWidget *const mTextAutoGenerateWidget;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};

}
