/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QObject>
#include <QProcess>
#include <QVector>
namespace TextGrammarCheck
{
/*!
 * \class TextGrammarCheck::GrammalecteGenerateConfigOptionJob
 * \inheaderfile TextGrammarCheck/GrammalecteGenerateConfigOptionJob
 * \inmodule TextGrammarCheck
 * \brief Generates configuration options for Grammalecte.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT GrammalecteGenerateConfigOptionJob : public QObject
{
    Q_OBJECT
public:
    struct Option {
        QString optionName;
        QString description;
        bool defaultValue = false;
    };

    /*!
     */
    explicit GrammalecteGenerateConfigOptionJob(QObject *parent = nullptr);
    /*!
     */
    ~GrammalecteGenerateConfigOptionJob() override;

    /*! Starts fetching the configuration options from Grammalecte. */
    void start();
    /*! Returns whether the job can be started. */
    [[nodiscard]] bool canStart() const;

    /*! Returns the path to the Python interpreter. */
    [[nodiscard]] QString pythonPath() const;
    /*! Sets the path to the Python interpreter. */
    void setPythonPath(const QString &pythonPath);

    /*! Returns the path to the Grammalecte CLI. */
    [[nodiscard]] QString grammarlecteCliPath() const;
    /*! Sets the path to the Grammalecte CLI. */
    void setGrammarlecteCliPath(const QString &grammarlecteCliPath);

Q_SIGNALS:
    /*! Emitted when an error occurs while fetching configuration options. */
    void error();
    /*! Emitted when the configuration options have been successfully fetched. */
    void finished(const QVector<TextGrammarCheck::GrammalecteGenerateConfigOptionJob::Option> &result);

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
