/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateProject>
class QLineEdit;
class KColorButton;
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateProjectWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateProjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateProjectWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateProjectWidget() override;

    /*! Fills the widget with \a project. The project identifier is kept and returned as-is by project(). */
    void setProject(const TextAutoGenerateText::TextAutoGenerateProject &project);
    /*! Returns the edited project. */
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateProject project() const;

Q_SIGNALS:
    /*! Emitted when the project becomes valid or invalid, so that the dialog can enable its Ok button. */
    void enableOkButton(bool enabled);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotNameChanged(const QString &name);
    QLineEdit *const mName;
    KColorButton *const mColor;
    TextAutoGenerateProject mProject;
};
}
