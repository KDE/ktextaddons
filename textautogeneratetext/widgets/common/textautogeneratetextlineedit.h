/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <KTextEdit>
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateTextLineEdit class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextLineEdit : public KTextEdit
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextLineEdit(QWidget *parent = nullptr);
    ~TextAutoGenerateTextLineEdit() override;

    [[nodiscard]] QString text() const;

    [[nodiscard]] QSize sizeHint() const override;
    [[nodiscard]] QSize minimumSizeHint() const override;

Q_SIGNALS:
    void sendMessage(const QString &);
    void keyPressed(QKeyEvent *ev);

protected:
    void keyPressEvent(QKeyEvent *e) override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void loadSpellCheckingSettings();
    TEXTAUTOGENERATETEXT_NO_EXPORT void switchAutoCorrectionLanguage(const QString &lang);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotLanguageChanged(const QString &lang);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotSpellCheckingEnableChanged(bool b);
};
}
