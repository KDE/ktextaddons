/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QWidget>
class QComboBox;
class QToolButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
/**
 * @brief The TextAutoGenerateTextConfigureComboWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextConfigureComboWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextConfigureComboWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateTextConfigureComboWidget() override;

    void load();
    void save();

Q_SIGNALS:
    void engineChanged(const QString &engineName);
    void configureChanged(const QString &engineName);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void fillEngine();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigureEngine();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEngineChanged(int index);
    QComboBox *const mEngineComboBox;
    QToolButton *const mConfigureEngine;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
