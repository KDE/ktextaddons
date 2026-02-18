/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateNotWorkingMessageWidget;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateNotWorkingWidget
 * \brief The TextAutoGenerateNotWorkingWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateNotWorkingWidget
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateNotWorkingWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Constructor for TextAutoGenerateNotWorkingWidget
     * \param manager The TextAutoGenerateManager instance
     * \param parent The parent widget
     */
    explicit TextAutoGenerateNotWorkingWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     * \brief Destructor for TextAutoGenerateNotWorkingWidget
     */
    ~TextAutoGenerateNotWorkingWidget() override;

    /*!
     * \brief Sets an error message to display
     * \param str The error message
     */
    void setMessageError(const QString &str);
    /*!
     * \brief Clears any displayed message
     */
    void clearMessage();

Q_SIGNALS:
    /*!
     * \brief Emitted when Ollama has been started
     */
    void ollamaStarted();
    /*!
     * \brief Emitted when the configuration of instances is requested
     */
    void configureInstances();
    /*!
     * \brief Emitted when Ollama startup is requested
     */
    void startOllamaRequested();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotStartOllama();
    TextAutoGenerateNotWorkingMessageWidget *const mMessageWidget;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
