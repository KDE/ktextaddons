/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextPlugin>
class QDebug;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextRequest;
class TextAutoGenerateReply;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateManagerBase
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateManagerBase
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateManagerBase : public QObject
{
    Q_OBJECT
public:
    struct TEXTAUTOGENERATETEXT_EXPORT ModelsInfo {
        QList<TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier> models;
        QString errorOccured;
        bool hasError = false;
        bool isReady = false;
    };
    /*!
     * Constructs a new TextAutoGenerateManagerBase object.
     * \param parent The parent QObject
     */
    explicit TextAutoGenerateManagerBase(QObject *parent = nullptr);
    /*!
     * Destroys the TextAutoGenerateManagerBase object.
     */
    ~TextAutoGenerateManagerBase() override;
    /*!
     * Loads the available models from the text generation service.
     */
    virtual void loadModels() = 0;

    /*!
     * Gets a completion for the given text generation request.
     * \param request The request containing the prompt and settings
     * \return A TextAutoGenerateReply object representing the reply
     */
    [[nodiscard]] virtual TextAutoGenerateText::TextAutoGenerateReply *getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);
    /*!
     * Gets a chat completion for the given text generation request.
     * \param request The request containing the conversation and settings
     * \return A TextAutoGenerateReply object representing the reply
     */
    [[nodiscard]] virtual TextAutoGenerateText::TextAutoGenerateReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) = 0;
Q_SIGNALS:
    /*!
     * Emitted when the models have finished loading.
     * \param models Information about the loaded models
     */
    void modelsLoadDone(const TextAutoGenerateText::TextAutoGenerateManagerBase::ModelsInfo &models);
    /*!
     * Emitted when installed models need to be refreshed.
     */
    void refreshInstalledModels();
    /*!
     * Emitted when the text generation reply is finished.
     * \param replyText The response from the LLM
     */
    void finished(const TextAutoGenerateText::TextAutoGenerateReply::Response &replyText);
    /*!
     * Emitted when a model download is complete.
     * \param modelName The name of the downloaded model
     */
    void downloadDone(const QString &modelName);
    /*!
     * Emitted when a model operation is canceled.
     * \param modelName The name of the model
     */
    void canceled(const QString &modelName);
    /*!
     * Emitted when model information display is complete.
     * \param replyText The model information
     */
    void showModelInfoDone(const QString &replyText);

protected:
    QMetaObject::Connection mCheckConnect;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateManagerBase::ModelsInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateManagerBase::ModelsInfo &t);
