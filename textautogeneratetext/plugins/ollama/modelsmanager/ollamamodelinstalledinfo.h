/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "plugins/plugincommon/plugincommonmodelinstalledinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateManager>
class QDebug;
class QJsonObject;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelInstalledInfo : public PluginCommonModelInstalledInfo
{
public:
    OllamaModelInstalledInfo();
    ~OllamaModelInstalledInfo();

    [[nodiscard]] QString family() const;
    void setFamily(const QString &newFamily);

    void parseInfo(const QJsonObject &obj) override;

    [[nodiscard]] QString modifyAt() const;
    void setModifyAt(const QString &newModifyAt);

    [[nodiscard]] QString modifyAtInLocal() const;

    [[nodiscard]] bool operator==(const OllamaModelInstalledInfo &other) const;

    [[nodiscard]] QString generateModelName() const;

    [[nodiscard]] static QString convertModelNameToDisplay(const QString &modelName);

    [[nodiscard]] QString parentModel() const;
    void setParentModel(const QString &newParentModel);

    [[nodiscard]] QStringList languages() const;
    void setLanguages(const QStringList &newLanguages);

    [[nodiscard]] QString modelUrl() const;
    void setModelUrl(const QString &newModelUrl);

private:
    QString mFamily;
    QString mModifyAt;
    QString mGeneratedModelName;
    QString mParentModel;
    QString mModelUrl;
    QStringList mLanguages;
};
Q_DECLARE_TYPEINFO(OllamaModelInstalledInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const OllamaModelInstalledInfo &t);
