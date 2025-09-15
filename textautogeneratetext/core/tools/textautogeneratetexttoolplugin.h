/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QJsonObject>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginProperty>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolPlugin : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextToolPlugin(QObject *parent = nullptr);
    ~TextAutoGenerateTextToolPlugin() override;

    [[nodiscard]] virtual QString executeTool() = 0;
    [[nodiscard]] virtual QString displayName() const = 0;
    [[nodiscard]] virtual QString description() const = 0;

    [[nodiscard]] QJsonObject metadata();

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

    [[nodiscard]] QByteArray toolNameId() const;
    void setToolNameId(const QByteArray &newToolName);

    virtual void showConfigureDialog(QWidget *parent = nullptr);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] QList<TextAutoGenerateTextToolPluginProperty> properties() const;
    void setProperties(const QList<TextAutoGenerateTextToolPluginProperty> &newProperties);

Q_SIGNALS:
    void finished(const QString &result);

protected:
    [[nodiscard]] QJsonObject generateMetadata() const;
    QList<TextAutoGenerateTextToolPluginProperty> mProperties;
    QByteArray mToolNameId;
    QJsonObject mMetaData;
    bool mEnabled = true;
};
}
