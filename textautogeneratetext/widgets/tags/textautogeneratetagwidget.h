/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateTag>
class QLineEdit;
class KColorButton;
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateTagWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTagWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTagWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTagWidget() override;

    /*! Fills the widget with \a tag. The tag identifier is kept and returned as-is by tag(). */
    void setTag(const TextAutoGenerateText::TextAutoGenerateTag &tag);
    /*! Returns the edited tag. */
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTag tag() const;

Q_SIGNALS:
    /*! Emitted when the tag becomes valid or invalid, so that the dialog can enable its Ok button. */
    void enableOkButton(bool enabled);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotNameChanged(const QString &name);
    QLineEdit *const mName;
    KColorButton *const mColor;
    TextAutoGenerateTag mTag;
};
}
