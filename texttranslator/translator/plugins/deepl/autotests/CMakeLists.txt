# SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
if (QT_MAJOR_VERSION STREQUAL "6")
    set(translator_deepl_LIB qt6keychain)
else()
    set(translator_deepl_LIB qt5keychain)
endif()
ecm_add_test(deeplengineclienttest.cpp deeplengineclienttest.h ../deeplengineclient.cpp ../deeplengineplugin.cpp ../deeplengineutil.cpp ${translator_debug_deepl_SRCS}
    ../deeplengineconfiguredialog.cpp
    ../deeplengineconfigurewidget.cpp
    TEST_NAME deeplengineclienttest

    LINK_LIBRARIES Qt::Test Qt::Gui KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::ConfigCore ${translator_deepl_LIB}
)

#####
ecm_add_test(deeplengineconfiguredialogtest.cpp deeplengineconfiguredialogtest.h ../deeplengineconfiguredialog.cpp ../deeplengineconfigurewidget.cpp ${translator_debug_deepl_SRCS}
    TEST_NAME deeplengineconfiguredialogtest

    LINK_LIBRARIES Qt::Test Qt::Gui KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::ConfigCore
)

#####
ecm_add_test(deeplengineconfigurewidgettest.cpp deeplengineconfigurewidgettest.h ../deeplengineconfigurewidget.cpp
    TEST_NAME deeplengineconfigurewidgettest

    LINK_LIBRARIES Qt::Test Qt::Gui KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::ConfigCore
)
