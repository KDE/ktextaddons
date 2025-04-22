/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QWidget>
class QComboBox;
class QToolButton;
namespace TextAutogenerateText
{
/**
 * @brief The TextAutogenerateTextConfigureComboWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateTextConfigureComboWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateTextConfigureComboWidget(QWidget *parent = nullptr);
    ~TextAutogenerateTextConfigureComboWidget() override;

    void load();
    void save();

Q_SIGNALS:
    void engineChanged(const QString &engineName);
    void configureChanged(const QString &engineName);

private:
    void fillEngine();
    void slotConfigureEngine();
    void slotEngineChanged(int index);
    QComboBox *const mEngineComboBox;
    QToolButton *const mConfigureEngine;
};
}
