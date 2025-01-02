# SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
ecm_add_test(googleengineclienttest.cpp googleengineclienttest.h ../googleengineclient.cpp ../googleengineplugin.cpp ${translator_debug_google_SRCS}
    TEST_NAME googleengineclienttest
    LINK_LIBRARIES Qt::Test Qt::Gui KF6::TextTranslator KF6::I18n
)
