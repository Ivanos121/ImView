#include "teplschem.h"
#include "ui_teplschem.h"

#include <QtSvg>
#include <QSvgWidget>
#include <QGraphicsPixmapItem>

teplschem::teplschem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teplschem)
{
    ui->setupUi(this);

    ui->svgWidget->setStyleSheet("QSvgWidget {background-color: white; border: 1px; border-style: solid; border-color: #c4c8cc;}");

    QFile file("/home/elf/cerebro/data/1256.svg");

    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    ui->svgWidget->load(doc.toByteArray());
    QSvgRenderer *renderer = ui->svgWidget->renderer();
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);
}

teplschem::~teplschem()
{
    delete ui;
}

void teplschem::retrievElements(QDomElement root, QString tag, QString att)
{
    QDomNodeList elemText = root.elementsByTagName(tag);
    qDebug() << "# nodes = " << elemText.count();

    for(int i = 0; i < elemText.count(); i++)
    {
        QDomNode elm = elemText.at(i);
        if(elm.isElement())
            {
                QDomElement e = elm.toElement();

            }
    }
}

void teplschem::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked())
    {
        QDomElement root = doc.firstChildElement();
        QDomNodeList elemText = root.elementsByTagName("text");
        for(int i = 0; i < elemText.count(); i++)
        {
            QDomNode elm = elemText.at(i);
            if(elm.isElement())
            {
                QDomElement e = elm.toElement();
                if (e.attribute("id") == QString("text525"))
                {
                    e.setNodeValue("Hello");
                }
            }
        }

        ui->svgWidget->load(doc.toByteArray());
        QSvgRenderer *renderer = ui->svgWidget->renderer();
        renderer->setAspectRatioMode(Qt::KeepAspectRatio);
    }

}

void teplschem::on_radioButton_5_toggled(bool checked)
{
    if(checked)
    {
        QDomElement root = doc.firstChildElement();

        QDomNodeList elemText = root.elementsByTagName("text");
        for(int i = 0; i < elemText.count(); i++)
        {
            QDomNode elm = elemText.at(i);
            if(elm.isElement())
            {
                QDomElement e = elm.toElement();
                if (e.attribute("id") == QString("text413"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text417"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text525"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text529"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text393"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text421"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text397"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text401"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text385"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text389"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text385-3"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text503"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text405"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text409"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text377"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text381"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text361"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text365"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text369"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text373"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text273"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text277"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text335"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text339"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text353"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text357"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text443"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text447"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text509"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text513"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text485"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text489"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
            }
        }

    ui->svgWidget->load(doc.toByteArray());
    QSvgRenderer *renderer = ui->svgWidget->renderer();
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);
    }
    else
    {
        QDomElement root = doc.firstChildElement();

        QDomNodeList elemText = root.elementsByTagName("text");
        for(int i = 0; i < elemText.count(); i++)
        {
            QDomNode elm = elemText.at(i);
            if(elm.isElement())
            {
                QDomElement e = elm.toElement();
                if (e.attribute("id") == QString("text417"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text413"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text525"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text529"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text393"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text421"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text397"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text401"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text385"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text389"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text385-3"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text503"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text405"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text409"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text377"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text381"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text361"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text365"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text369"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text373"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text273"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text277"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text335"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text339"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text353"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text357"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text443"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text447"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text509"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text513"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text485"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text489"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
            }
        }
    }
    ui->svgWidget->load(doc.toByteArray());
    QSvgRenderer *renderer = ui->svgWidget->renderer();
    renderer->setAspectRatioMode(Qt::KeepAspectRatio);
}

void teplschem::on_radioButton_toggled(bool checked)
{
    if(checked)
    {
        QDomElement root = doc.firstChildElement();

        QDomNodeList elemText = root.elementsByTagName("text");
        for(int i = 0; i < elemText.count(); i++)
        {
            QDomNode elm = elemText.at(i);
            if(elm.isElement())
            {
                QDomElement e = elm.toElement();
                if (e.attribute("id") == QString("text517"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text249"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text345"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text241"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text255"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text205"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text327"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text237"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text261"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text209"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text435"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text245"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text499"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text233"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text267"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text213"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text285"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text217"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text293"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text221"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text307"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text229"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text299"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text225"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }

            }
        }
        ui->svgWidget->load(doc.toByteArray());
        QSvgRenderer *renderer = ui->svgWidget->renderer();
        renderer->setAspectRatioMode(Qt::KeepAspectRatio);
    }
    else
    {
        QDomElement root = doc.firstChildElement();

        QDomNodeList elemText = root.elementsByTagName("text");
        for(int i = 0; i < elemText.count(); i++)
        {
            QDomNode elm = elemText.at(i);
            if(elm.isElement())
            {
                QDomElement e = elm.toElement();
                if (e.attribute("id") == QString("text517"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text249"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text345"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text241"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text255"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text205"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text327"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text237"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text261"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text209"))
                {
                    e.setAttribute("style", "visibility: visible");
                }

                if (e.attribute("id") == QString("text435"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text245"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text499"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text233"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text267"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text213"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text285"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text217"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text293"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text221"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text307"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text229"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text299"))
                {
                    e.setAttribute("style", "font-size:30.713px;font-family:Arial;fill:#000000");
                }
                if (e.attribute("id") == QString("text225"))
                {
                    e.setAttribute("style", "visibility: visible");
                }
            }
        }
        ui->svgWidget->load(doc.toByteArray());
        QSvgRenderer *renderer = ui->svgWidget->renderer();
        renderer->setAspectRatioMode(Qt::KeepAspectRatio);
    }

}


void teplschem::on_radioButton_4_toggled(bool checked)
{
    if (checked)
    {
        QDomElement root = doc.firstChildElement();

        QDomNodeList elemText = root.elementsByTagName("text");
        for(int i = 0; i < elemText.count(); i++)
        {
            QDomNode elm = elemText.at(i);
            if(elm.isElement())
            {
                QDomElement e = elm.toElement();
                if (e.attribute("id") == QString("text475"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text479"))
                {
                   e.setAttribute("style", "visibility: hidden");
                }

                if (e.attribute("id") == QString("text467"))
                {
                    e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text471"))
                {
                    e.setAttribute("style", "visibility: hidden");
                }

                if (e.attribute("id") == QString("text451"))
                {
                    e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text455"))
                {
                    e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text459"))
                {
                    e.setAttribute("style", "visibility: hidden");
                }
                if (e.attribute("id") == QString("text463"))
                {
                    e.setAttribute("style", "visibility: hidden");
                }
            }
        }

        elemText = root.elementsByTagName("path");
        for(int i = 0; i < elemText.count(); i++)
        {
            QDomNode elm = elemText.at(i);
            if(elm.isElement())
            {
                QDomElement e = elm.toElement();
                if (e.attribute("id") == QString("path167"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path159"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path165"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path161"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path163"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path157"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }

                if (e.attribute("id") == QString("path149"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path153"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path155"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path151"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path137"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path135"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path133"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path131"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path129"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path147"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path139"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path141"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path143"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path145"))
                {
                    QString oldStyle = e.attribute("style");
                    oldStyle += ";visibility: hidden";
                    e.setAttribute("style", oldStyle);
                }
            }
        }

        ui->svgWidget->load(doc.toByteArray());
        QSvgRenderer *renderer = ui->svgWidget->renderer();
        renderer->setAspectRatioMode(Qt::KeepAspectRatio);
    }



    else
    {
        QDomElement root = doc.firstChildElement();

        QDomNodeList elemText = root.elementsByTagName("text");
        for(int i = 0; i < elemText.count(); i++)
        {
            QDomNode elm = elemText.at(i);
            if(elm.isElement())
            {
                QDomElement e = elm.toElement();
                if (e.attribute("id") == QString("text475"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text479"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text467"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text471"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text451"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text455"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
                if (e.attribute("id") == QString("text459"))
                {
                   e.setAttribute("style", "font-size:30.713px;font-family:Arial;fill:#000000");
                }
                if (e.attribute("id") == QString("text463"))
                {
                   e.setAttribute("style", "visibility: visible");
                }
            }
        }

        QDomNodeList elemText2 = root.elementsByTagName("path");
        for(int i = 0; i < elemText2.count(); i++)
        {
            QDomNode elm = elemText2.at(i);
            if(elm.isElement())
            {
                QDomElement e = elm.toElement();
                if (e.attribute("id") == QString("path167"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path159"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path165"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path161"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path163"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path157"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path149"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path153"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path155"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path151"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path131"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path129"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path147"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path139"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path141"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path143"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
                if (e.attribute("id") == QString("path145"))
                {
                   QString oldStyle = e.attribute("style");
                   oldStyle = oldStyle.leftRef(oldStyle.lastIndexOf(";visibility: hidden")).toString();
                   e.setAttribute("style", oldStyle);
                }
            }
        }

        ui->svgWidget->load(doc.toByteArray());
        QSvgRenderer *renderer = ui->svgWidget->renderer();
        renderer->setAspectRatioMode(Qt::KeepAspectRatio);
    }
}


void teplschem::on_radioButton_2_toggled(bool checked)
{

}

