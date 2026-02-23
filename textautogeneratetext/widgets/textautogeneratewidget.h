/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QPointer>
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateAttachmentUtils>
#include <TextAutoGenerateText/TextAutoGenerateManager>
class QSplitter;
namespace TextAutoGenerateText
{
class TextAutoGenerateResultWidget;
class TextAutoGenerateTextLineEditWidget;
class TextAutoGenerateHistoryWidget;
class TextAutoGenerateHeaderWidget;
class TextAutoGenerateSearchDialog;
class TextAutoGeneratePowerSaverMessageWidget;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateWidget
 * \brief The TextAutoGenerateWidget class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateWidget
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Constructs a new TextAutoGenerateWidget.
     * \param manager The TextAutoGenerateManager instance
     * \param parent The parent widget
     */
    explicit TextAutoGenerateWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateWidget.
     */
    ~TextAutoGenerateWidget() override;

    /*!
     * Returns the current text in the line edit.
     * \return The text from the line edit widget
     */
    [[nodiscard]] QString textLineEdit() const;
    /*!
     * Performs a text search based on current input.
     */
    void slotSearchText();

    /*!
     * Loads the AI engine for text generation.
     */
    void loadEngine();

Q_SIGNALS:
    /*!
     * Emitted when no plugins are found.
     * \param msg The error message
     */
    void noPluginsFound(const QString &msg);
    /*!
     * Emitted when a plugin is broken or failed to load.
     * \param msg The error message
     */
    void pluginBroken(const QString &msg);
    /*!
     * Emitted when the editing mode is stopped.
     * \param uuid The UUID of the message being edited
     */
    void stopEditingMode(const QByteArray &uuid);
    /*!
     * Emitted when instances need to be added.
     */
    void needToAddInstances();
    /*!
     * Emitted when the plugin is initialized successfully.
     */
    void pluginInitialized();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotInitializeDone();
    TEXTAUTOGENERATETEXT_NO_EXPORT void
    slotEditingFinished(const QString &str,
                        const QByteArray &uuid,
                        const QList<QByteArray> &lstTools,
                        const QList<TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &attachmentInfoList);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAutogenerateFailed(const QString &errorMessage);
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void keyPressedInLineEdit(QKeyEvent *ev);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditMessage(const QModelIndex &index, const QList<QByteArray> &tools);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotCancelRequest(const QByteArray &uuid);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAskMessageRequester(const TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo &info);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRefreshAnswer(const QByteArray &chatId, const QModelIndex &index, const QList<QByteArray> &tools);
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT bool lineEditWidgetEnabledState() const;
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotQuickSearchText(bool enabled);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotErrorOccurred(QNetworkReply::NetworkError e);

    TextAutoGenerateResultWidget *const mTextAutoGenerateResultWidget;
    TextAutoGenerateTextLineEditWidget *const mTextAutoGenerateTextLineEditWidget;

    QSplitter *const mSplitter;
    TextAutoGenerateHistoryWidget *const mHistoryWidget;
    TextAutoGenerateHeaderWidget *const mHeaderWidget;
    QList<TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo> mAskMessageList;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    QPointer<TextAutoGenerateSearchDialog> mSearchDialog;
    TextAutoGeneratePowerSaverMessageWidget *const mTextAutoGeneratePowerSaverMessageWidget;
};
}
