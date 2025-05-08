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
class TextAutogenerateResultWidget;
class TextAutoGenerateTextLineEditWidget;
class TextAutoGenerateTextClient;
class TextAutoGenerateTextPlugin;
class TextAutoGenerateMessage;
class TextAutogenerateHistoryWidget;
class TextAutogenerateHeaderWidget;
/**
 * @brief The TextAutogenerateWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateWidget(QWidget *parent = nullptr);
    ~TextAutogenerateWidget() override;

    [[nodiscard]] QString textLineEdit() const;

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
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRefreshAnswer(const QModelIndex &index);

    TextAutogenerateResultWidget *const mTextAutogenerateResultWidget;
    TextAutoGenerateTextLineEditWidget *const mTextAutoGenerateTextLineEditWidget;

    TextAutoGenerateTextClient *mTextAutogenerateClient = nullptr;
    TextAutoGenerateTextPlugin *mTextAutogeneratePlugin = nullptr;
    QSplitter *const mSplitter;
    TextAutogenerateHistoryWidget *const mHistoryWidget;
    TextAutogenerateHeaderWidget *const mHeaderWidget;
    QStringList mAskMessageList;
    bool mPluginWasInitialized = false;
};
}
