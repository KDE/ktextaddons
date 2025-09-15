/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QToolButton;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateToolsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolsWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateToolsWidget() override;

    [[nodiscard]] QList<QByteArray> generateListOfActiveTools() const;

    void setActivatedTools(const QList<QByteArray> &lst);

private:
    QList<QToolButton *> mListButton;
};
}
