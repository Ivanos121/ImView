QT       += core gui sql webkitwidgets webenginewidgets serialport printsupport svg xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11 debug

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QCUSTOMPLOT_USE_OPENGL

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    archiverchannel.cpp \
    base.cpp \
    bvasthread.cpp \
    bvas.cpp \
    checkboxdelegate.cpp \
    checkboxheader.cpp \
    comboboxbitdelegate.cpp \
    comboboxcurrentdelegate.cpp \
    comboboxdelegate.cpp \
    comboboxerrorarchivedelegate.cpp \
    comboboxmodbusdelegate.cpp \
    comboboxvardelegate.cpp \
    datas.cpp \
    datasource.cpp \
    datasource_el.cpp \
    datasource_file.cpp \
    datasourcebvas.cpp \
    datasourcebvasw.cpp \
    device.cpp \
    draw_line.cpp \
    draw_poper.cpp \
    electromagn.cpp \
    gridlinedelegate.cpp \
    identf.cpp \
    ischodn_dannie.cpp \
    itogs.cpp \
    kalibr.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    model_el.cpp \
    modelidentf.cpp \
    modell.cpp \
    nabludatel.cpp \
    nabludatel_part.cpp \
    paintdelegate.cpp \
    plot.cpp \
    settings.cpp \
    teplovent.cpp \
    teplschem.cpp \
    trend.cpp \
    vent_izm.cpp \
    vent_model.cpp \
    vent_tract.cpp

HEADERS += \
    archiverchannel.h \
    base.h \
    bvasthread.h \
    bvas.h \
    checkboxdelegate.h \
    checkboxheader.h \
    comboboxbitdelegate.h \
    comboboxcurrentdelegate.h \
    comboboxdelegate.h \
    comboboxerrorarchivedelegate.h \
    comboboxmodbusdelegate.h \
    comboboxvardelegate.h \
    crc.h \
    datas.h \
    datasource.h \
    datasource_el.h \
    datasource_file.h \
    datasourcebvas.h \
    datasourcebvasw.h \
    device.h \
    draw_line.h \
    draw_poper.h \
    electromagn.h \
    gridlinedelegate.h \
    identf.h \
    ischodn_dannie.h \
    itogs.h \
    kalibr.h \
    mainwindow.h \
    model.h \
    model_el.h \
    modelidentf.h \
    modell.h \
    nabludatel.h \
    nabludatel_base.h \
    nabludatel_part.h \
    paintdelegate.h \
    plot.h \
    settings.h \
    teplovent.h \
    teplschem.h \
    trend.h \
    vent_izm.h \
    vent_model.h \
    vent_tract.h

FORMS += \
    about_dialog.ui \
    datas.ui \
    draw_line.ui \
    draw_poper.ui \
    electromagn.ui \
    identf.ui \
    ischodn_dannie.ui \
    itogs.ui \
    kalibr.ui \
    mainwindow.ui \
    settings.ui \
    teplovent.ui \
    teplschem.ui \
    trend.ui \
    vent_izm.ui \
    vent_model.ui \
    vent_tract.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lusb-1.0

RESOURCES += \
    Images.qrc 
