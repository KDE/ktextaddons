/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>

namespace TextAutoGenerateText
{
class TextAutoGeneratePluginTextInterface;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGeneratePluginText : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGeneratePluginText(QObject *parent = nullptr);
    ~TextAutoGeneratePluginText() override;

    virtual TextAutoGeneratePluginTextInterface *createInterface(QObject *parent) = 0;

    [[nodiscard]] virtual int order() const = 0;

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

    [[nodiscard]] virtual bool hasConfigureDialog() const;
    virtual void showConfigureDialog(QWidget *parent = nullptr) const;

Q_SIGNALS:
    void errorMessage(const QString &message);
    void successMessage(const QString &message);

protected:
    bool mEnabled = true;
};
}
