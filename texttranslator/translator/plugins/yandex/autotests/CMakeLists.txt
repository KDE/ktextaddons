# SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
ecm_add_test(yandexengineclienttest.cpp yandexengineclienttest.h ../yandexengineclient.cpp ../yandexengineplugin.cpp
    TEST_NAME yandexengineclienttest
    
    LINK_LIBRARIES Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n
)
