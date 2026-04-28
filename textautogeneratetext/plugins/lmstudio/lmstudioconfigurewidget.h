/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratelmstudio_export.h"
#include <KPasswordLineEdit>
#include <QWidget>
class QLineEdit;
class QSpinBox;
class LMStudioManager;
namespace TextAutoGenerateText
{
class TextAutoGenerateNotWorkingMessageWidget;
}
class TEXTAUTOGENERATELMSTUDIO_EXPORT LMStudioConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LMStudioConfigureWidget(LMStudioManager *manager, QWidget *parent = nullptr);
    ~LMStudioConfigureWidget() override;

    void loadSettings();
    void saveSettings();
    void restoreToDefaults();

Q_SIGNALS:
    void lmStudioProcessOk(bool status);
    void enableOkButton(bool status);

private:
    TEXTAUTOGENERATELMSTUDIO_NO_EXPORT void fillModels();
    TEXTAUTOGENERATELMSTUDIO_NO_EXPORT void slotStartLMStudio();
    TEXTAUTOGENERATELMSTUDIO_NO_EXPORT void displayModelInfo(const QString &modelStr);
    TEXTAUTOGENERATELMSTUDIO_NO_EXPORT void showModelInfo(const QString &modelName);
    QLineEdit *const mName;
    QLineEdit *const mUrl;
    KPasswordLineEdit *const mApiKey;
    TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget *const mMessageWidget;
    LMStudioManager *const mManager;
};
