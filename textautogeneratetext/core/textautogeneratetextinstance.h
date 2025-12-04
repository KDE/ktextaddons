/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"

#include <KConfigGroup>
class QDebug;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextPlugin;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstance
{
public:
    TextAutoGenerateTextInstance();
    ~TextAutoGenerateTextInstance();

    [[nodiscard]] QString displayName() const;

    [[nodiscard]] QString pluginName() const;
    void setPluginName(const QString &newPluginName);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] QByteArray instanceUuid() const;
    void setInstanceUuid(const QByteArray &newInstanceUuid);

    [[nodiscard]] QString pluginIdentifier() const;
    void setPluginIdentifier(const QString &newPluginIdentifier);

    void load(const KConfigGroup &config);
    void save(KConfigGroup &config);

    [[nodiscard]] QString currentModel() const;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextPlugin *plugin() const;
    void setPlugin(TextAutoGenerateText::TextAutoGenerateTextPlugin *newPlugin);

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

private:
    QString mPluginName;
    QString mPluginIdentifier;
    QByteArray mInstanceUuid;
    TextAutoGenerateText::TextAutoGenerateTextPlugin *mPlugin = nullptr;
    bool mEnabled = true;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextInstance, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextInstance &t);
