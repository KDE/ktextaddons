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
     */
    explicit TextAutoGenerateWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateWidget() override;

    /*!
     */
    [[nodiscard]] QString textLineEdit() const;
    /*!
     */
    void slotSearchText();

    /*!
     */
    void loadEngine();

Q_SIGNALS:
    /*!
     */
    void noPluginsFound(const QString &msg);
    /*!
     */
    void pluginBroken(const QString &msg);
    /*!
     */
    void stopEditingMode(const QByteArray &uuid);
    /*!
     */
    void needToAddInstances();
    /*!
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
};
}
