/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDebug>
#include <QJsonObject>
#include <TextAutoGenerateText/TextAutoGenerateTextContext>
class OllamaRequest
{
    Q_GADGET
public:
    OllamaRequest();
    ~OllamaRequest();

    [[nodiscard]] QString message() const;
    void setMessage(const QString &newMessage);

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextContext context() const;
    void setContext(const TextAutoGenerateText::TextAutoGenerateTextContext &newContext);

    [[nodiscard]] bool operator==(const OllamaRequest &other) const;

    [[nodiscard]] QString model() const;
    void setModel(const QString &newModel);

    [[nodiscard]] QJsonObject messages() const;
    void setMessages(const QJsonObject &newMessages);

private:
    QJsonObject mMessages;
    QString mMessage;
    TextAutoGenerateText::TextAutoGenerateTextContext mContext;
    QString mModel;
};

QDebug operator<<(QDebug d, const OllamaRequest &t);
