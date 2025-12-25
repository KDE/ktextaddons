/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
class QMenu;
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGeneratePluginTextInterface class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGeneratePluginTextInterface : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGeneratePluginTextInterface(QObject *parent = nullptr);
    ~TextAutoGeneratePluginTextInterface() override;

    virtual void addAction(QMenu *menu) = 0;

    virtual void setSelectedText(const QString &str) = 0;
};
}
