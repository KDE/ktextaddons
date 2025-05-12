/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QSharedData>

namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAnswerInfo : public QSharedData
{
public:
    TextAutoGenerateAnswerInfo();
    ~TextAutoGenerateAnswerInfo();

    [[nodiscard]] QString modelName() const;
    void setModelName(const QString &newModelName);

    [[nodiscard]] QString engineName() const;
    void setEngineName(const QString &newEngineName);

private:
    QString mModelName;
    QString mEngineName;
};

}
