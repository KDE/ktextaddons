/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class QSplitter;
namespace TextAutoGenerateText
{
class TextAutoGenerateResultWidget;
class TextAutoGenerateTextLineEditWidget;
class TextAutoGenerateMessage;
class TextAutoGenerateManager;
class TextAutoGenerateHistoryWidget;
class TextAutoGenerateHeaderWidget;
/**
 * @brief The TextAutoGenerateWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateWidget() override;

    [[nodiscard]] QString textLineEdit() const;
    void slotSearchText();

    void loadEngine();

Q_SIGNALS:
    void noPluginsFound(const QString &msg);
    void pluginBroken(const QString &msg);
    void stopEditingMode(const QByteArray &uuid);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotInitializeDone();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditingFinished(const QString &str, const QByteArray &uuid);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAutogenerateFinished(const TextAutoGenerateMessage &msg);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAutogenerateFailed(const QString &errorMessage);
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigureChanged();
    TEXTAUTOGENERATETEXT_NO_EXPORT void keyPressedInLineEdit(QKeyEvent *ev);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditMessage(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotCancelRequest(const QByteArray &uuid);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAskMessageRequester(const QString &str);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRefreshAnswer(const QByteArray &chatId, const QModelIndex &index);

    TextAutoGenerateResultWidget *const mTextAutoGenerateResultWidget;
    TextAutoGenerateTextLineEditWidget *const mTextAutoGenerateTextLineEditWidget;

    QSplitter *const mSplitter;
    TextAutoGenerateHistoryWidget *const mHistoryWidget;
    TextAutoGenerateHeaderWidget *const mHeaderWidget;
    QStringList mAskMessageList;
    bool mPluginWasInitialized = false;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
