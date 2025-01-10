/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "speechtotext_private_export.h"
#include <QWidget>
class QComboBox;
class QToolButton;
namespace TextSpeechToText
{
class TEXTSPEECHTOTEXT_TESTS_EXPORT SpeechToTextComboBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SpeechToTextComboBoxWidget(QWidget *parent);
    ~SpeechToTextComboBoxWidget() override;
    void fillEngine();

    [[nodiscard]] QString engineName() const;
    void setEngineName(const QString &engineName);

    void load();
    void save();

Q_SIGNALS:
    void configureChanged(const QString &engineName);
    void engineChanged(const QString &engineName);

private:
    TEXTSPEECHTOTEXT_NO_EXPORT void slotConfigureEngine();
    TEXTSPEECHTOTEXT_NO_EXPORT void slotEngineChanged(int index);
    QComboBox *const mEngine;
    QToolButton *const mConfigureEngine;
};
}
