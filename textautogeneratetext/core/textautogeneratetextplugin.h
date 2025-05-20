/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
#include <QObject>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutoGenerateMessage;
class TextAutoGenerateTextPluginPrivate;
class TextAutoGenerateManager;
/**
 * @brief The TextAutoGenerateTextPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextPlugin : public QObject
{
    Q_OBJECT
public:
    struct TEXTAUTOGENERATETEXT_EXPORT SendToAssistantInfo {
        QString message;
        QByteArray messageUuid;
        QByteArray chatId;
    };
    explicit TextAutoGenerateTextPlugin(QObject *parent = nullptr);
    ~TextAutoGenerateTextPlugin() override;

    [[nodiscard]] virtual bool loadSettings() = 0;

    virtual void clear() = 0;

    virtual void setPrompt(const QString &text) = 0;

    void setHasError(bool error);

    [[nodiscard]] bool ready() const;
    void setReady(bool newReady);

    void sendMessage(const QByteArray &chatId, const QString &str);
    virtual void cancelRequest(const QByteArray &uuid) = 0;

    void editMessage(const QByteArray &chatId, const QByteArray &uuid, const QString &str);

    [[nodiscard]] virtual QString engineName() const = 0;

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

    void setManager(TextAutoGenerateText::TextAutoGenerateManager *manager);
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateManager *manager() const;
    virtual void askToAssistant(const QString &msg) = 0;
Q_SIGNALS:
    void errorOccurred(const QString &message);
    void finished(const TextAutoGenerateMessage &msg);
    void initializedDone();
    void askToAssistantAnswer(const QString &message);
    void askToAssistantDone();

protected:
    virtual void sendToAssistant(const SendToAssistantInfo &info) = 0;

private:
    std::unique_ptr<TextAutoGenerateTextPluginPrivate> const d;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextPlugin::SendToAssistantInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::SendToAssistantInfo &t);
