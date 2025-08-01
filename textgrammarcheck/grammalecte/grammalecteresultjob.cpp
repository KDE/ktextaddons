/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteresultjob.h"
using namespace Qt::Literals::StringLiterals;

#include "textgrammarcheck_debug.h"

#include <QFileInfo>
#include <QTemporaryFile>
using namespace TextGrammarCheck;
GrammalecteResultJob::GrammalecteResultJob(QObject *parent)
    : QObject(parent)
{
}

GrammalecteResultJob::~GrammalecteResultJob() = default;

void GrammalecteResultJob::start()
{
    if (canStart()) {
        mProcess = new QProcess(this);

        auto file = new QTemporaryFile(this);
        file->open();
        file->setPermissions(QFile::ReadUser);
        file->write(mText.toUtf8());
        file->close();

        mProcess->setProgram(mPythonPath);
        QStringList args;
        args.reserve(6);
        args << mGrammarlecteCliPath;
        if (!mArguments.isEmpty()) {
            args << u"-on"_s << mArguments;
        }
        args << u"-f"_s << file->fileName() << QStringLiteral("-j");
        mProcess->setArguments(args);
        connect(mProcess, &QProcess::finished, this, &GrammalecteResultJob::slotFinished);
        connect(mProcess, &QProcess::errorOccurred, this, &GrammalecteResultJob::receivedError);
        connect(mProcess, &QProcess::readyReadStandardError, this, &GrammalecteResultJob::receivedStdErr);
        connect(mProcess, &QProcess::readyReadStandardOutput, this, &GrammalecteResultJob::receivedStandardOutput);

        mProcess->start();
        if (!mProcess->waitForStarted()) {
            qCWarning(TEXTGRAMMARCHECK_LOG) << "Impossible to start grammarresultjob";
            Q_EMIT error(ErrorType::Unknown);
            deleteLater();
        }
    } else {
        if (mErrorType != ErrorType::TextIsEmpty) {
            Q_EMIT error(mErrorType);
        }
        deleteLater();
    }
}

void GrammalecteResultJob::receivedStandardOutput()
{
    mResult += QString::fromUtf8(mProcess->readAllStandardOutput());
}

void GrammalecteResultJob::receivedError()
{
    mLastError += mProcess->errorString();
}

void GrammalecteResultJob::receivedStdErr()
{
    mLastError += QLatin1StringView(mProcess->readAllStandardError());
}

void GrammalecteResultJob::slotFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus != 0 || exitCode != 0) {
        qCWarning(TEXTGRAMMARCHECK_LOG) << "Error during running GrammarResultJob: " << mLastError;
    } else {
        Q_EMIT finished(mResult);
    }
    deleteLater();
}

QStringList GrammalecteResultJob::arguments() const
{
    return mArguments;
}

void GrammalecteResultJob::setArguments(const QStringList &arguments)
{
    mArguments = arguments;
}

QString GrammalecteResultJob::grammarlecteCliPath() const
{
    return mGrammarlecteCliPath;
}

void GrammalecteResultJob::setGrammarlecteCliPath(const QString &grammarlecteCliPath)
{
    mGrammarlecteCliPath = grammarlecteCliPath;
}

QString GrammalecteResultJob::pythonPath() const
{
    return mPythonPath;
}

void GrammalecteResultJob::setPythonPath(const QString &pythonPath)
{
    mPythonPath = pythonPath;
}

static bool hasNotEmptyText(const QString &text)
{
    for (int i = 0, total = text.length(); i < total; ++i) {
        if (!text.at(i).isSpace()) {
            return true;
        }
    }
    return false;
}

bool GrammalecteResultJob::canStart()
{
    if (!hasNotEmptyText(mText)) {
        mErrorType = ErrorType::TextIsEmpty;
        return false;
    }
    if (mGrammarlecteCliPath.isEmpty()) {
        mErrorType = ErrorType::GrammalecteMissing;
        return false;
    }
    if (mPythonPath.isEmpty()) {
        mErrorType = ErrorType::PythonPathMissing;
        return false;
    }
    if (!QFileInfo::exists(mPythonPath)) {
        mErrorType = ErrorType::PythonPathNotExist;
        return false;
    }
    if (!QFileInfo::exists(mGrammarlecteCliPath)) {
        mErrorType = ErrorType::GrammarlectCliNotExist;
        return false;
    }
    return true;
}

QString GrammalecteResultJob::text() const
{
    return mText;
}

void GrammalecteResultJob::setText(const QString &text)
{
    mText = text;
}

#include "moc_grammalecteresultjob.cpp"
