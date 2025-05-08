/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class KMessageWidget;
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutogenerateNotWorkingWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateNotWorkingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateNotWorkingWidget(QWidget *parent = nullptr);
    ~TextAutogenerateNotWorkingWidget() override;

    void setMessageError(const QString &str);
    void clearMessage();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigure();
    KMessageWidget *const mMessageWidget;
};
}
