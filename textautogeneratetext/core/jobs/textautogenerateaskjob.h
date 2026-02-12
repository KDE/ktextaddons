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
    /*! Constructs a new TextAutoGenerateAskJob object with the given @p parent. */
    explicit TextAutoGenerateAskJob(QObject *parent = nullptr);
    /*! Destroys the TextAutoGenerateAskJob object. */
    ~TextAutoGenerateAskJob() override;
    /*! Returns whether the ask job can be started. */
    [[nodiscard]] bool canStart() const;

    /*! Starts the ask job. */
    void start();

    /*! Returns the associated TextAutoGenerateManager. */
    [[nodiscard]] TextAutoGenerateManager *manager() const;
    /*! Sets the associated TextAutoGenerateManager to @p newManager. */
    void setManager(TextAutoGenerateManager *newManager);

    /*! Returns the text to ask. */
    [[nodiscard]] QString text() const;
    /*! Sets the text to ask to @p newText. */
    void setText(const QString &newText);

Q_SIGNALS:
    /*! Emitted when text generation is in progress with the current @p response. */
    void generateTextInProgress(const TextAutoGenerateText::TextAutoGenerateReply::Response &response);
    /*! Emitted when text generation has finished successfully. */
    void generateTextDone();
    /*! Emitted when an error occurs with the error message in @p str. */
    void errorOccured(const QString &str);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAutogenerateFailed(const QString &msg);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotInitializeDone();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAskToLlmDone();
    QString mText;
    TextAutoGenerateManager *mManager = nullptr;
};
}
