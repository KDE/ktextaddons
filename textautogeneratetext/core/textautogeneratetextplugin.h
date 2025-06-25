/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
#include <QJsonArray>
#include <QObject>
#include <kconfiggroup.h>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutoGenerateMessage;
class TextAutoGenerateTextPluginPrivate;
class TextAutoGenerateManager;
class TextAutoGenerateReply;
/**
 * @brief The TextAutoGenerateTextPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextPlugin : public QObject
{
    Q_OBJECT
public:
    struct TEXTAUTOGENERATETEXT_EXPORT ModelInfoNameAndIdentifier {
        QString modelName;
        QString identifier;
        [[nodiscard]] bool isValid() const;
    };

    struct TEXTAUTOGENERATETEXT_EXPORT SendToAssistantInfo {
        QString message;
        QByteArray messageUuid;
        QByteArray chatId;
        QJsonArray messagesArray;
    };
    explicit TextAutoGenerateTextPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent = nullptr);
    ~TextAutoGenerateTextPlugin() override;

    virtual void showConfigureDialog(QWidget *parentWidget) = 0;

    virtual void clear() = 0;
    [[nodiscard]] virtual QString translatedPluginName() const = 0;

    virtual void setPrompt(const QString &text) = 0;

    void setHasError(bool error);

    [[nodiscard]] bool ready() const;
    void setReady(bool newReady);

    void sendMessage(const QByteArray &chatId, const QString &str);
    virtual void cancelRequest(const QByteArray &uuid) = 0;

    void editMessage(const QByteArray &chatId, const QByteArray &uuid, const QString &str);

    [[nodiscard]] virtual QString engineName() const = 0;

    [[nodiscard]] virtual QString currentModel() const = 0;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateManager *manager() const;
    virtual void askToAssistant(const QString &msg) = 0;

    virtual void load(const KConfigGroup &config);
    virtual void save(KConfigGroup &config);

    [[nodiscard]] virtual QList<ModelInfoNameAndIdentifier> models() const = 0;

    [[nodiscard]] virtual QString displayName() const = 0;
    virtual void setDisplayName(const QString &newName) = 0;

Q_SIGNALS:
    void errorOccurred(const QString &message);
    void finished(const TextAutoGenerateMessage &msg);
    void initializedDone();
    void askToAssistantAnswer(const QString &message);
    void askToAssistantDone();
    void configChanged();

protected:
    virtual void sendToAssistant(const SendToAssistantInfo &info) = 0;
    QMultiHash<TextAutoGenerateText::TextAutoGenerateReply *, QPair<QByteArray, QMetaObject::Connection>> mConnections;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void initializeProgress(const SendToAssistantInfo &info);
    std::unique_ptr<TextAutoGenerateTextPluginPrivate> const d;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextPlugin::SendToAssistantInfo, Q_RELOCATABLE_TYPE);
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::SendToAssistantInfo &t);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier &t);
