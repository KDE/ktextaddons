/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateTextPlugin>
class QComboBox;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonComboBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaCommonComboBoxWidget(QWidget *parent = nullptr);
    ~OllamaCommonComboBoxWidget() override;

    void setModels(const QList<TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier> &lst);
    void setCurrentModel(const QString &str);
    [[nodiscard]] QString currentModel() const;
Q_SIGNALS:
    void reloadModel();
    void showModelInfoRequested(const QString &modelName);

private:
    QComboBox *const mModelComboBox;
};
