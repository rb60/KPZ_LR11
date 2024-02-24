isEmpty(GOOGLETEST_DIR):GOOGLETEST_DIR=$$(GOOGLETEST_DIR)

isEmpty(GOOGLETEST_DIR) {
    GOOGLETEST_DIR = "E:/user_02/gtest/googletest-1.14.0"
    !isEmpty(GOOGLETEST_DIR) {
        warning("Using googletest src dir specified at Qt Creator wizard")
        message("set GOOGLETEST_DIR as environment variable or qmake variable to get rid of this message")
    }
}

!isEmpty(GOOGLETEST_DIR): {
    INCLUDEPATH *= "$$GOOGLETEST_DIR/include"

    LIBS *= -L"$$GOOGLETEST_DIR/lib" -lgtest -lgmock
} else {
    LIBS *= -lgtest -lgmock
}

INCLUDEPATH += \
    $$GOOGLETEST_DIR/googlemock \
    $$GOOGLETEST_DIR/googlemock/include \
    $$GOOGLETEST_DIR/googletest \
    $$GOOGLETEST_DIR/googletest/include

SOURCES += \
    $$GOOGLETEST_DIR/googlemock/src/gmock-all.cc \
    $$GOOGLETEST_DIR/googletest/src/gtest-all.cc
