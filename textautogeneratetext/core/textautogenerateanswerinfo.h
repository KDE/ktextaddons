/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
#include <QSharedData>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAnswerInfo : public QSharedData
{
public:
    TextAutoGenerateAnswerInfo();
    ~TextAutoGenerateAnswerInfo();
    explicit TextAutoGenerateAnswerInfo(const TextAutoGenerateAnswerInfo &other);

    [[nodiscard]] QString modelName() const;
    void setModelName(const QString &newModelName);

    [[nodiscard]] QString engineName() const;
    void setEngineName(const QString &newEngineName);

    [[nodiscard]] QString instanceName() const;
    void setInstanceName(const QString &newInstanceName);

    [[nodiscard]] bool operator==(const TextAutoGenerateAnswerInfo &other) const;

    [[nodiscard]] bool isValid() const;

private:
    QString mModelName;
    QString mEngineName;
    QString mInstanceName;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAnswerInfo &t);
