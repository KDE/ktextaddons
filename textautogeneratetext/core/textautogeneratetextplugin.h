/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <KConfigGroup>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutoGenerateMessage;
class TextAutoGenerateTextPluginPrivate;
class TextAutoGenerateManager;
class TextAutoGenerateReply;
class TextAutoGenerateTextInstance;
/**
 * @brief The TextAutoGenerateTextPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextPlugin : public QObject
{
    Q_OBJECT
public:
    enum class EngineType : uint8_t {
        Local,
        Network,
    };
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
    explicit TextAutoGenerateTextPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                        TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                                        QObject *parent = nullptr);
    ~TextAutoGenerateTextPlugin() override;

    virtual void showConfigureDialog(QWidget *parentWidget) = 0;

    virtual void clear();
    [[nodiscard]] virtual QString translatedPluginName() const = 0;

    void setHasError(bool error);

    [[nodiscard]] bool ready() const;
    void setReady(bool newReady);

    void sendMessage(const QByteArray &chatId, const QString &str, const QList<QByteArray> &lstTools);
    virtual void cancelRequest(const QByteArray &uuid);

    void editMessage(const QByteArray &chatId, const QByteArray &uuid, const QString &str, const QList<QByteArray> &lstTools);

    [[nodiscard]] virtual QString engineName() const = 0;

    [[nodiscard]] virtual QString currentModel() const = 0;
    virtual void setCurrentModel(const QString &) = 0;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateManager *manager() const;
    virtual void askToAssistant(const QString &msg) = 0;

    virtual void load(const KConfigGroup &config);
    virtual void save(KConfigGroup &config);
    virtual void remove();

    [[nodiscard]] virtual QString displayName() const = 0;
    virtual void setDisplayName(const QString &newName) = 0;

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier> models() const;

    [[nodiscard]] QByteArray instanceUuid() const;

    [[nodiscard]] virtual TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType engineType() const = 0;

    [[nodiscard]] static QString convertEngineType(TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType type);

    [[nodiscard]] virtual bool hasVisionSupport() const = 0;
    [[nodiscard]] virtual bool hasToolsSupport() const = 0;
Q_SIGNALS:
    void errorOccurred(const QString &message);
    void finished(const TextAutoGenerateMessage &msg);
    void initializedDone();
    void askToAssistantAnswer(const QString &message);
    void askToAssistantDone();
    void configChanged();
    void downloadModelFinished(const QString &modelName);

protected:
    virtual void sendToAssistant(const SendToAssistantInfo &info) = 0;
    [[nodiscard]] QString fallBackModel() const;
    QMultiHash<TextAutoGenerateText::TextAutoGenerateReply *, QPair<QByteArray, QMetaObject::Connection>> mConnections;
    QList<ModelInfoNameAndIdentifier> mModels;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void initializeProgress(const SendToAssistantInfo &info);
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QJsonObject createPromptMessage() const;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QJsonArray createListMessages(const QList<QJsonObject> &objs) const;
    std::unique_ptr<TextAutoGenerateTextPluginPrivate> const d;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextPlugin::SendToAssistantInfo, Q_RELOCATABLE_TYPE);
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::SendToAssistantInfo &t);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier &t);
