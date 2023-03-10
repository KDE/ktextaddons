/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautocorrection_export.h"
#include <QTextEdit>
namespace TextAutoCorrection
{
class AutoCorrection;
class AutoCorrectionTextEditPrivate;
/**
 * @brief The AutoCorrectionTextEdit class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOCORRECTION_EXPORT AutoCorrectionTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit AutoCorrectionTextEdit(QWidget *parent = nullptr);
    ~AutoCorrectionTextEdit() override;

    Q_REQUIRED_RESULT TextAutoCorrection::AutoCorrection *autocorrection() const;

    void setAutocorrection(TextAutoCorrection::AutoCorrection *autocorrect);

    void setAutocorrectionLanguage(const QString &language);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    std::unique_ptr<AutoCorrectionTextEditPrivate> const d;
};
}
