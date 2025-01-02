/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QObject>
#include <QProcess>
#include <QVector>
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_EXPORT GrammalecteGenerateConfigOptionJob : public QObject
{
    Q_OBJECT
public:
    struct Option {
        QString optionName;
        QString description;
        bool defaultValue = false;
    };

    explicit GrammalecteGenerateConfigOptionJob(QObject *parent = nullptr);
    ~GrammalecteGenerateConfigOptionJob() override;

    void start();
    [[nodiscard]] bool canStart() const;

    [[nodiscard]] QString pythonPath() const;
    void setPythonPath(const QString &pythonPath);

    [[nodiscard]] QString grammarlecteCliPath() const;
    void setGrammarlecteCliPath(const QString &grammarlecteCliPath);

Q_SIGNALS:
    void error();
    void finished(const QVector<GrammalecteGenerateConfigOptionJob::Option> &result);

private:
    Q_DISABLE_COPY(GrammalecteGenerateConfigOptionJob)
    TEXTGRAMMARCHECK_NO_EXPORT void receivedStandardOutput();
    TEXTGRAMMARCHECK_NO_EXPORT void slotFinished(int exitCode, QProcess::ExitStatus exitStatus);
    TEXTGRAMMARCHECK_NO_EXPORT void receivedError();
    TEXTGRAMMARCHECK_NO_EXPORT void receivedStdErr();
    TEXTGRAMMARCHECK_NO_EXPORT QVector<GrammalecteGenerateConfigOptionJob::Option> parseResult() const;
    QString mResult;
    QString mPythonPath;
    QString mGrammarlecteCliPath;
    QString mLastError;
    QProcess *mProcess = nullptr;
};
}
Q_DECLARE_TYPEINFO(TextGrammarCheck::GrammalecteGenerateConfigOptionJob::Option, Q_MOVABLE_TYPE);
