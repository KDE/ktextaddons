/*
  SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Volker Krause <vkrause@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautocorrectionwidgets_export.h"

#include <QObject>

class QPlainTextEdit;
class QTextEdit;

namespace TextAutoCorrectionCore
{
class AutoCorrection;
}

namespace TextAutoCorrectionWidgets
{
class AutoCorrectorPrivate;
/*!
 * \brief Adds auto-correction to QTextEdit or QPlainTextEdit instances.
 * \class TextAutoCorrectionWidgets::AutoCorrector
 * \inmodule TextAutoCorrectionWidgets
 * \inheaderfile TextAutoCorrectionWidgets/AutoCorrector
 * \since 2.2
 */
class TEXTAUTOCORRECTIONWIDGETS_EXPORT AutoCorrector : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Apply auto-correction to \p textEdit
     * \param textEdit
     */
    explicit AutoCorrector(QTextEdit *textEdit);
    /*!
     * \brief Apply auto-correction to \p textEdit
     * \param textEdit
     */
    explicit AutoCorrector(QPlainTextEdit *textEdit);

    ~AutoCorrector() override;

    /*!
     */
    [[nodiscard]] TextAutoCorrectionCore::AutoCorrection *autocorrection() const;

    /*!
     */
    void setAutocorrection(TextAutoCorrectionCore::AutoCorrection *autocorrect);

    /*!
     */
    void setAutocorrectionLanguage(const QString &language);

private:
    bool eventFilter(QObject *receiver, QEvent *event) override;
    std::unique_ptr<AutoCorrectorPrivate> const d;
};
}
