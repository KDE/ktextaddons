/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateAskJob
 * \brief The TextAutoGenerateAskJob class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateAskJob
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAskJob : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Constructs a new TextAutoGenerateAskJob object
     * \param parent The parent object
     */
    explicit TextAutoGenerateAskJob(QObject *parent = nullptr);
    /*!
     * \brief Destroys the TextAutoGenerateAskJob object
     */
    ~TextAutoGenerateAskJob() override;
    /*!
     * \brief Returns whether the ask job can be started
     * \return True if the job can start, false otherwise
     */
    [[nodiscard]] bool canStart() const;

    /*!
     * \brief Starts the ask job
     */
    void start();

    /*!
     * \brief Returns the associated TextAutoGenerateManager
     * \return The manager object
     */
    [[nodiscard]] TextAutoGenerateManager *manager() const;
    /*!
     * \brief Sets the associated TextAutoGenerateManager
     * \param newManager The manager to set
     */
    void setManager(TextAutoGenerateManager *newManager);

    /*!
     * \brief Returns the text to ask
     * \return The question text
     */
    [[nodiscard]] QString text() const;
    /*!
     * \brief Sets the text to ask
     * \param newText The question text to set
     */
    void setText(const QString &newText);

Q_SIGNALS:
    /*!
     * \brief Emitted when text generation is in progress
     * \param response The current response from text generation
     */
    void generateTextInProgress(const TextAutoGenerateText::TextAutoGenerateReply::Response &response);
    /*!
     * \brief Emitted when text generation has finished successfully
     */
    void generateTextDone();
    /*!
     * \brief Emitted when an error occurs
     * \param str The error message
     */
    void errorOccured(const QString &str);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAutogenerateFailed(const QString &msg);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotInitializeDone();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAskToLlmDone();
    QString mText;
    TextAutoGenerateManager *mManager = nullptr;
};
}
