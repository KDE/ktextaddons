/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libbergamot_export.h"
#include "translator.h"
#include <QObject>

class LIBBERGAMOT_EXPORT ManagerModelTranslator : public QObject
{
    Q_OBJECT
public:
    explicit ManagerModelTranslator(QObject *parent = nullptr);
    ~ManagerModelTranslator() override;

    static ManagerModelTranslator *self();

    void downloadListModels();

    Q_REQUIRED_RESULT QVector<Translator> translators() const;
    void setTranslators(const QVector<Translator> &newTranslators);

    void loadModelList(const QString &fileName);

    void downloadLanguage(const QString &url);

Q_SIGNALS:
    void errorText(const QString &str);

private:
    LIBBERGAMOT_NO_EXPORT void extractLanguage();
    LIBBERGAMOT_NO_EXPORT void parseListModel(const QJsonObject &obj);
    LIBBERGAMOT_NO_EXPORT void slotExtractDone();
    QVector<Translator> mTranslators;
};
