/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextPlugin>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextRequest;
class TextAutoGenerateReply;
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
    explicit TextAutoGenerateManagerBase(QObject *parent = nullptr);
    ~TextAutoGenerateManagerBase() override;

    virtual void loadModels() = 0;

    [[nodiscard]] virtual TextAutoGenerateText::TextAutoGenerateReply *getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request);
    [[nodiscard]] virtual TextAutoGenerateText::TextAutoGenerateReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) = 0;
Q_SIGNALS:
    void modelsLoadDone(const TextAutoGenerateText::TextAutoGenerateManagerBase::ModelsInfo &models);
    void refreshInstalledModels();
    void finished(const QString &replyText);
    void downloadDone(const QString &modelName);

protected:
    QMetaObject::Connection mCheckConnect;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateManagerBase::ModelsInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateManagerBase::ModelsInfo &t);
