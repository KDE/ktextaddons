/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QObject>
#include <QProcess>
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_EXPORT GrammalecteResultJob : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteResultJob(QObject *parent = nullptr);
    ~GrammalecteResultJob() override;

    enum class ErrorType {
        NoError = 0,
        TextIsEmpty = 1,
        PythonPathMissing = 2,
        GrammalecteMissing = 3,
        PythonPathNotExist = 4,
        GrammarlectCliNotExist = 5,
        Unknown = 6,
    };

    void start();

    [[nodiscard]] bool canStart();

    [[nodiscard]] QString text() const;
    void setText(const QString &text);

    [[nodiscard]] QString pythonPath() const;
    void setPythonPath(const QString &pythonPath);

    [[nodiscard]] QString grammarlecteCliPath() const;
    void setGrammarlecteCliPath(const QString &grammarlecteCliPath);

    [[nodiscard]] QStringList arguments() const;
    void setArguments(const QStringList &arguments);

Q_SIGNALS:
    void finished(const QString &result);
    void error(GrammalecteResultJob::ErrorType type);

private:
    TEXTGRAMMARCHECK_NO_EXPORT void slotFinished(int exitCode, QProcess::ExitStatus exitStatus);
    TEXTGRAMMARCHECK_NO_EXPORT void receivedStdErr();
    TEXTGRAMMARCHECK_NO_EXPORT void receivedError();
    TEXTGRAMMARCHECK_NO_EXPORT void receivedStandardOutput();
    QStringList mArguments;
    QString mResult;
    QString mText;
    QString mPythonPath;
    QString mGrammarlecteCliPath;
    QString mLastError;
    GrammalecteResultJob::ErrorType mErrorType = ErrorType::NoError;
    QProcess *mProcess = nullptr;
};
}
