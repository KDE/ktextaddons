/*
  SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautocorrectionwidgets_export.h"

#include <QPlainTextEdit>
namespace TextAutoCorrectionCore
{
class AutoCorrection;
}
namespace TextAutoCorrectionWidgets
{
class AutoCorrectionLineEditPrivate;
/**
 * @brief The AutoCorrectionLineEdit class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONWIDGETS_EXPORT AutoCorrectionLineEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit AutoCorrectionLineEdit(QWidget *parent = nullptr);
    ~AutoCorrectionLineEdit() override;

    [[nodiscard]] TextAutoCorrectionCore::AutoCorrection *autocorrection() const;

    void setAutocorrection(TextAutoCorrectionCore::AutoCorrection *autocorrect);
    void setAutocorrectionLanguage(const QString &language);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    std::unique_ptr<AutoCorrectionLineEditPrivate> const d;
};
}
