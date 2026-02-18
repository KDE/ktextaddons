/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <KMessageWidget>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget
 * \brief The TextAutoGenerateNotWorkingMessageWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateNotWorkingMessageWidget
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateNotWorkingMessageWidget : public KMessageWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for TextAutoGenerateNotWorkingMessageWidget
     * \param parent The parent widget
     */
    explicit TextAutoGenerateNotWorkingMessageWidget(QWidget *parent = nullptr);
    /*!
     * \brief Destructor for TextAutoGenerateNotWorkingMessageWidget
     */
    ~TextAutoGenerateNotWorkingMessageWidget() override;

    /*!
     * \brief Sets the error message to display
     * \param errorMessage The error message text
     */
    void setMessageInfo(const QString &errorMessage);
Q_SIGNALS:
    /*!
     * \brief Emitted when Ollama should be started
     */
    void startOllama();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotDownloadOllama();
    QAction *mCurrentAction = nullptr;
};
}
