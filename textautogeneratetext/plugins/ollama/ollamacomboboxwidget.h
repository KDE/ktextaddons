/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QComboBox;
class OllamaComboBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaComboBoxWidget(QWidget *parent = nullptr);
    ~OllamaComboBoxWidget() override;

    void setModels(const QStringList &lst);
    void setCurrentModel(const QString &str);
    [[nodiscard]] QString currentModel() const;
Q_SIGNALS:
    void reloadModel();

private:
    QComboBox *const mModelComboBox;
};
