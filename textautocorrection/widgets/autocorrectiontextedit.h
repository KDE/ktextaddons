/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautocorrectionwidgets_export.h"
#include <QTextEdit>
namespace TextAutoCorrectionCore
{
class AutoCorrection;
}
namespace TextAutoCorrectionWidgets
{
class AutoCorrectionTextEditPrivate;
/**
 * @brief The AutoCorrectionTextEdit class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTIONWIDGETS_EXPORT AutoCorrectionTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit AutoCorrectionTextEdit(QWidget *parent = nullptr);
    ~AutoCorrectionTextEdit() override;

    Q_REQUIRED_RESULT TextAutoCorrectionCore::AutoCorrection *autocorrection() const;

    void setAutocorrection(TextAutoCorrectionCore::AutoCorrection *autocorrect);

    void setAutocorrectionLanguage(const QString &language);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    std::unique_ptr<AutoCorrectionTextEditPrivate> const d;
};
}
