/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QObject>
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_EXPORT GrammalecteManager : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteManager(QObject *parent = nullptr);
    ~GrammalecteManager() override;

    static GrammalecteManager *self();

    [[nodiscard]] QString pythonPath() const;
    [[nodiscard]] QString grammalectePath() const;

    void setPythonPath(const QString &pythonPath);
    void setGrammalectePath(const QString &grammalectePath);
    [[nodiscard]] QStringList options() const;
    void setOptions(const QStringList &saveOptions);

    void loadSettings();
    void saveSettings();

private:
    Q_DISABLE_COPY(GrammalecteManager)
    QStringList mOptions;
    QString mPythonPath;
    QString mGrammalectePath;
};
}
