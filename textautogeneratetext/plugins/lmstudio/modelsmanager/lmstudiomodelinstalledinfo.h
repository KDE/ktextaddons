/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "plugins/plugincommon/plugincommonmodelinstalledinfo.h"
#include "textautogeneratelmstudio_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateManager>
class QDebug;
class QJsonObject;
class TEXTAUTOGENERATELMSTUDIO_EXPORT LMStudioModelInstalledInfo : public PluginCommonModelInstalledInfo
{
public:
    LMStudioModelInstalledInfo();
    ~LMStudioModelInstalledInfo();

    [[nodiscard]] QString publisher() const;
    void setPublisher(const QString &newPublisher);

    void parseInfo(const QJsonObject &obj) override;

private:
    QString mPublisher;
};
Q_DECLARE_TYPEINFO(LMStudioModelInstalledInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const LMStudioModelInstalledInfo &t);
