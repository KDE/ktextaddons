/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDebug>
#include <QObject>
#include <TextAutogenerateText/TextAutogenerateTextContext>
class OllamaRequest
{
    Q_GADGET
public:
    OllamaRequest();
    ~OllamaRequest();

    [[nodiscard]] QString message() const;
    void setMessage(const QString &newMessage);

private:
    QString mMessage;
    TextAutogenerateText::TextAutogenerateTextContext mContext;
};

QDebug operator<<(QDebug d, const OllamaRequest &t);
