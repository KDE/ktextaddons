/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <KConfigGroup>
#include <QUrl>
class QDebug;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextMcpServer
{
public:
    TextAutoGenerateTextMcpServer();
    ~TextAutoGenerateTextMcpServer();
    [[nodiscard]] QUrl serverUrl() const;
    void setServerUrl(const QUrl &newServerUrl);

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QByteArray identifier() const;
    void setIdentifier(const QByteArray &newIdentifier);

    void load(const KConfigGroup &config);
    void save(KConfigGroup &config);

private:
    bool mEnabled = true;
    QUrl mServerUrl;
    QString mName;
    QByteArray mIdentifier;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextMcpServer, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextMcpServer &t);
