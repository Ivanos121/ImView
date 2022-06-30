#include "mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QuaZip-Qt5-1.3/quazip/JlCompress.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QFile file(QString("/home/elf/ImView/data/yyyyy.imview"));
//    JlCompress::extractDir(file,"/home/elf/ImView/data/");
//        if (!file.open(QFile::ReadOnly | QFile::Text))
//        {
//           // QMessageBox::warning(this, "Ошибка файла", "Не удалось открыть файл", QMessageBox::Ok);
//        }
//        else
//        {
//            QXmlStreamReader xmlReader;
//            xmlReader.setDevice(&file);
//            xmlReader.readNext();
//            while(!xmlReader.atEnd())
//            {
//                if(xmlReader.isStartElement())
//                {
//                    if(xmlReader.name() == "project_name")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item4->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_1")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item88->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "project_path")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item106->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_2")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item80->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "project_path_2")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item82->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "checkbox_1")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "boolean")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                if(attribute_value=="true")
//                                {
//                                    w.item68->setCheckState(Qt::Checked);
//                                }
//                                else
//                                {
//                                    w.item68->setCheckState(Qt::Unchecked);
//                                };
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_3")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item109->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "checkbox_2")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "boolean")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                if(attribute_value=="true"){
//                                    w.item70->setCheckState(Qt::Checked);}
//                                else {w.item70->setCheckState(Qt::Unchecked);};
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_4")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item111->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "checkbox_3")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "boolean")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                if(attribute_value=="true"){
//                                w.item72->setCheckState(Qt::Checked);}
//                                else {w.item72->setCheckState(Qt::Unchecked);};
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_5")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item113->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "checkbox_4")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "boolean")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                if(attribute_value=="true"){
//                                w.item74->setCheckState(Qt::Checked);}
//                                else {w.item74->setCheckState(Qt::Unchecked);};
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_6")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item115->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "checkbox_5")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "boolean")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                if(attribute_value=="true"){
//                                w.item76->setCheckState(Qt::Checked);}
//                                else {w.item76->setCheckState(Qt::Unchecked);};
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_7")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item117->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "checkbox_6")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "boolean")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                if(attribute_value=="true"){
//                                w.item78->setCheckState(Qt::Checked);}
//                                else {w.item78->setCheckState(Qt::Unchecked);};
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_8")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item119->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_9")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item14->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "coeff_1")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item94->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "coeff_2")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item96->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "coeff_3")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item98->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "coeff_4")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item100->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "coeff_5")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item102->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "coeff_6")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item104->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_10")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item20->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "time_cikle")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item22->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "time_raboty")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item24->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "moment")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item90->setText(attribute_value);
//                            }
//                        }
//                    }
//                    else if(xmlReader.name() == "combobox_11")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w.item92->setText(attribute_value);
//                            }
//                        }
//                    }
//                    if(xmlReader.name() == "start_temp")
//                    {
//                        foreach(const QXmlStreamAttribute &attr, xmlReader.attributes())
//                        {
//                            if (attr.name().toString() == "value")
//                            {
//                                QString attribute_value = attr.value().toString();
//                                w. item28->setText(attribute_value);
//                            }
//                        }
//                    }
//                }
//                xmlReader.readNext(); // Переходим к следующему элементу файла
//            }
//            file.close(); // Закрываем файл
//        }
        return a.exec();
}
