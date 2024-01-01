# SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
ecm_add_test(bingengineclienttest.cpp bingengineclienttest.h ../bingengineclient.cpp ../bingengineplugin.cpp ${translator_debug_bing_SRCS}
    TEST_NAME bingengineclienttest
    
    LINK_LIBRARIES Qt::Test Qt::Gui KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n
)
