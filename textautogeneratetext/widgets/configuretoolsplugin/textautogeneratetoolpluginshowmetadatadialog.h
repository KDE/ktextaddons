/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateToolPluginShowMetaDataDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateToolPluginShowMetaDataDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateToolPluginShowMetaDataDialog() override;
};
}
