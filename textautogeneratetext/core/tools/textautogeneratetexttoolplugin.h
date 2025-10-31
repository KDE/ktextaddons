/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QJsonObject>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateReply>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginProperty>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextToolPluginJob;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolPlugin : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToolPlugin(QObject *parent = nullptr);
    ~TextAutoGenerateTextToolPlugin() override;

    [[nodiscard]] virtual QString displayName() const = 0;
    [[nodiscard]] virtual QString description() const = 0;
    [[nodiscard]] virtual int order() const = 0;

    [[nodiscard]] QJsonObject metadata();

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

    [[nodiscard]] QByteArray toolNameId() const;
    void setToolNameId(const QByteArray &newToolName);

    virtual void showConfigureDialog(QWidget *parent = nullptr);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] QList<TextAutoGenerateTextToolPluginProperty> properties() const;
    void setProperties(const QList<TextAutoGenerateTextToolPluginProperty> &newProperties);

    virtual TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *callTool() = 0;

    [[nodiscard]] virtual QString iconName() const;

Q_SIGNALS:
    void finished(const QString &str, const QByteArray &messageUuid, const QByteArray &chatId, const QByteArray &toolIdentifier);
    void toolInProgress(const QString &str);

protected:
    [[nodiscard]] QJsonObject generateMetadata() const;
    QList<TextAutoGenerateTextToolPluginProperty> mProperties;
    QByteArray mToolNameId;
    QJsonObject mMetaData;
    bool mEnabled = true;
};
}
