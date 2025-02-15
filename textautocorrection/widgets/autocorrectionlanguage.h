/*
  SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautocorrectionwidgets_export.h"
#include <QComboBox>

namespace TextAutoCorrectionWidgets
{
class AutoCorrectionLanguageModel;
/**
 * @brief The AutoCorrectionLanguage class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONWIDGETS_EXPORT AutoCorrectionLanguage : public QComboBox
{
public:
    explicit AutoCorrectionLanguage(QWidget *parent);
    ~AutoCorrectionLanguage() override;

    [[nodiscard]] QString language(int index) const;

    /**
     * @brief language
     * @return specified language
     */
    [[nodiscard]] QString language() const;

    /**
     * @brief setLanguage
     * @param language define specified language
     */
    void setLanguage(const QString &language);

private:
    AutoCorrectionLanguageModel *const mAutoCorrectionLanguageModel;
};
}
