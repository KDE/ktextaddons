# SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
ecm_add_test(yandexengineclienttest.cpp yandexengineclienttest.h ../yandexengineclient.cpp ../yandexengineplugin.cpp
    TEST_NAME yandexengineclienttest
    
    LINK_LIBRARIES Qt::Test Qt::Gui KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n
)
