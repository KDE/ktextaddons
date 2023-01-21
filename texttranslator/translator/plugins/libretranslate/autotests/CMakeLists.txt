# SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
if (QT_MAJOR_VERSION STREQUAL "6")
    set(translator_libretranslate_LIB qt6keychain)
else()
    set(translator_libretranslate_LIB qt5keychain)
endif()
ecm_add_test(libretranslateengineclienttest.cpp libretranslateengineclienttest.h ../libretranslateengineclient.cpp ../libretranslateengineplugin.cpp
    ../libretranslateengineconfiguredialog.cpp ../libretranslateengineconfigurewidget.cpp ../libretranslateengineutil.h ../libretranslateengineutil.cpp
    ${translator_libretranslate_debug_SRCS}
    TEST_NAME libretranslateengineclienttest
    
    LINK_LIBRARIES Qt::Test Qt::Gui KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::ConfigCore ${translator_libretranslate_LIB}
)

######
ecm_add_test(libretranslateengineconfigurewidgettest.cpp libretranslateengineconfigurewidgettest.h
    ../libretranslateengineconfigurewidget.cpp
    TEST_NAME libretranslateengineconfigurewidgettest
    
    LINK_LIBRARIES Qt::Test Qt::Gui KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n
)

######
ecm_add_test(libretranslateengineconfiguredialogtest.cpp libretranslateengineconfiguredialogtest.h
    ../libretranslateengineconfiguredialog.cpp ../libretranslateengineconfigurewidget.cpp
    TEST_NAME libretranslateengineconfiguredialogtest
    
    LINK_LIBRARIES Qt::Test Qt::Gui KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n
)

######
ecm_add_test(libretranslateengineutiltest.cpp libretranslateengineutiltest.h
    ../libretranslateengineutil.cpp
    TEST_NAME libretranslateengineutiltest
    
    LINK_LIBRARIES Qt::Test Qt::Gui KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n
)
