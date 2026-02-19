/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QObject>
#include <QProcess>
namespace TextGrammarCheck
{
/*!
 * \class TextGrammarCheck::GrammalecteResultJob
 * \inheaderfile TextGrammarCheck/GrammalecteResultJob
 * \inmodule TextGrammarCheck
 * \brief Processes Grammalecte grammar check results.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT GrammalecteResultJob : public QObject
{
    Q_OBJECT
public:
    /*! Constructs a new GrammalecteResultJob. */
    explicit GrammalecteResultJob(QObject *parent = nullptr);
    /*! Destroys the job. */
    ~GrammalecteResultJob() override;

    enum class ErrorType : uint8_t {
        NoError = 0,
        TextIsEmpty = 1,
        PythonPathMissing = 2,
        GrammalecteMissing = 3,
        PythonPathNotExist = 4,
        GrammarlectCliNotExist = 5,
        Unknown = 6,
    };

    /*! Starts the grammar checking process. */
    void start();

    /*! Returns whether the job can be started. */
    [[nodiscard]] bool canStart();

    /*! Returns the text to be checked. */
    [[nodiscard]] QString text() const;
    /*! Sets the text to be checked. */
    void setText(const QString &text);

    /*! Returns the path to the Python interpreter. */
    [[nodiscard]] QString pythonPath() const;
    /*! Sets the path to the Python interpreter. */
    void setPythonPath(const QString &pythonPath);

    /*! Returns the path to the Grammalecte CLI. */
    [[nodiscard]] QString grammarlecteCliPath() const;
    /*! Sets the path to the Grammalecte CLI. */
    void setGrammarlecteCliPath(const QString &grammarlecteCliPath);

    /*! Returns the command-line arguments for Grammalecte. */
    [[nodiscard]] QStringList arguments() const;
    /*! Sets the command-line arguments for Grammalecte. */
    void setArguments(const QStringList &arguments);

Q_SIGNALS:
    /*! Emitted when the grammar checking is finished with the result. */
    void finished(const QString &result);
    /*! Emitted when an error occurs during grammar checking. */
    void error(TextGrammarCheck::GrammalecteResultJob::ErrorType type);

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
