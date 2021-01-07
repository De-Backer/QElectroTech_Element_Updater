#include "safeelement.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMap>

SafeElement::SafeElement(QString outputfile, VElement element)
{
    element_data = element;
    QDir dir;
    if (! dir.exists(outputfile.left(outputfile.lastIndexOf("/"))))
        dir.mkpath(outputfile.left(outputfile.lastIndexOf("/")));
    QFile file(outputfile);
    if (! file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "file is not open";
        throw std::invalid_argument("file is not open");
        return;
    }
    if (! file.isWritable())
    {
        qDebug() << "file is not Writable";
        throw std::invalid_argument("file is not Writable");
        return;
    }
    QXmlStreamWriter* writer = new QXmlStreamWriter(&file);
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeComment(
        "note: this is written by QElectroTech Element Updater version: 0.0.0");
    write_definition(writer);
    writer->writeEndDocument();
    file.close();
    delete writer;
}

SafeElement::~SafeElement() {}

void SafeElement::write_definition(QXmlStreamWriter* writer)
{
    writer->writeStartElement("definition");
    QMapIterator<QString, QVariant> var(element_data.definition());
    while (var.hasNext())
    {
        var.next();
        writer->writeAttribute(var.key(), var.value().toString());
    }
    write_definition_uuid(writer);
    write_definition_name(writer);
    write_definition_kindInformation(writer);
    write_definition_elementInformations(writer);
    write_definition_informations(writer);
    write_definition_description(writer);
    writer->writeEndElement(); // definition
}

void SafeElement::write_definition_uuid(QXmlStreamWriter* writer)
{
    writer->writeStartElement("uuid");
    writer->writeAttribute("uuid", element_data.uuid().toString());
    writer->writeEndElement(); // uuid
}

void SafeElement::write_definition_name(QXmlStreamWriter* writer)
{
    writer->writeStartElement("names");
    QMapIterator<QString, QString> var(element_data.name());
    while (var.hasNext())
    {
        var.next();
        writer->writeStartElement("name");
        writer->writeAttribute("lang", var.key());
        writer->writeCharacters(var.value());
        writer->writeEndElement(); // name
    }
    writer->writeEndElement(); // names
}

void SafeElement::write_definition_kindInformation(QXmlStreamWriter* writer)
{
    writer->writeStartElement("kindInformations");
    QMapIterator<QString, QVector<QVariant>> var(
        element_data.kindInformation());
    while (var.hasNext())
    {
        var.next();
        writer->writeStartElement("kindInformation");
        writer->writeAttribute("name", var.key());
        writer->writeAttribute("show", var.value().at(0).toString());
        writer->writeCharacters(var.value().at(1).toString());
        writer->writeEndElement(); // kindInformation
    }
    writer->writeEndElement(); // kindInformations
}

void SafeElement::write_definition_elementInformations(QXmlStreamWriter* writer)
{
    writer->writeStartElement("elementInformations");
    QMapIterator<QString, QVector<QVariant>> var(
        element_data.elementInformations());
    while (var.hasNext())
    {
        var.next();
        writer->writeStartElement("elementInformation");
        writer->writeAttribute("name", var.key());
        writer->writeAttribute("show", var.value().at(0).toString());
        writer->writeCharacters(var.value().at(1).toString());
        writer->writeEndElement(); // elementInformation
    }
    writer->writeEndElement(); // elementInformations
}

void SafeElement::write_definition_informations(QXmlStreamWriter* writer)
{
    writer->writeStartElement("informations");
    writer->writeCharacters(element_data.informations());
    writer->writeEndElement(); // informations
}

void SafeElement::write_definition_description(QXmlStreamWriter* writer)
{
    writer->writeStartElement("description");
    write_PartLine(writer);
    write_PartRectangle(writer);
    write_PartCircle(writer);
    write_PartEllipse(writer);
    write_PartPolygon(writer);
    write_PartArc(writer);
    write_PartDynamicTextField(writer);
    write_PartTerminal(writer);
    writer->writeEndElement(); // description
}

void SafeElement::write_PartLine(QXmlStreamWriter* writer)
{
    for (int var = 0; var < element_data.description().size(); ++var)
    {
        if (element_data.description()
                .at(var)
                .value("XML_ElementName")
                .toString()
            == "line")
        {
            writer->writeStartElement(element_data.description()
                                          .at(var)
                                          .value("XML_ElementName")
                                          .toString());
            QMapIterator<QString, QVariant> data(
                element_data.description().at(var));
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "XML_ElementName")
                    writer->writeAttribute(data.key(), data.value().toString());
            }
            writer->writeEndElement();
        }
    }
}

void SafeElement::write_PartRectangle(QXmlStreamWriter* writer)
{
    for (int var = 0; var < element_data.description().size(); ++var)
    {
        if (element_data.description()
                .at(var)
                .value("XML_ElementName")
                .toString()
            == "rect")
        {
            writer->writeStartElement(element_data.description()
                                          .at(var)
                                          .value("XML_ElementName")
                                          .toString());
            QMapIterator<QString, QVariant> data(
                element_data.description().at(var));
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "XML_ElementName")
                    writer->writeAttribute(data.key(), data.value().toString());
            }
            writer->writeEndElement();
        }
    }
}

void SafeElement::write_PartEllipse(QXmlStreamWriter* writer)
{
    for (int var = 0; var < element_data.description().size(); ++var)
    {
        if (element_data.description()
                .at(var)
                .value("XML_ElementName")
                .toString()
            == "ellipse")
        {
            writer->writeStartElement(element_data.description()
                                          .at(var)
                                          .value("XML_ElementName")
                                          .toString());
            QMapIterator<QString, QVariant> data(
                element_data.description().at(var));
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "XML_ElementName")
                    writer->writeAttribute(data.key(), data.value().toString());
            }
            writer->writeEndElement();
        }
    }
}

void SafeElement::write_PartCircle(QXmlStreamWriter* writer)
{
    for (int var = 0; var < element_data.description().size(); ++var)
    {
        if (element_data.description()
                .at(var)
                .value("XML_ElementName")
                .toString()
            == "circle")
        {
            writer->writeStartElement(element_data.description()
                                          .at(var)
                                          .value("XML_ElementName")
                                          .toString());
            QMapIterator<QString, QVariant> data(
                element_data.description().at(var));
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "XML_ElementName")
                    writer->writeAttribute(data.key(), data.value().toString());
            }
            writer->writeEndElement();
        }
    }
}

void SafeElement::write_PartPolygon(QXmlStreamWriter* writer)
{
    for (int var = 0; var < element_data.description().size(); ++var)
    {
        if (element_data.description()
                .at(var)
                .value("XML_ElementName")
                .toString()
            == "polygon")
        {
            writer->writeStartElement(element_data.description()
                                          .at(var)
                                          .value("XML_ElementName")
                                          .toString());
            QMapIterator<QString, QVariant> data(
                element_data.description().at(var));
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "XML_ElementName")
                    writer->writeAttribute(data.key(), data.value().toString());
            }
            writer->writeEndElement();
        }
    }
}

void SafeElement::write_PartTerminal(QXmlStreamWriter* writer)
{
    for (int var = 0; var < element_data.description().size(); ++var)
    {
        if (element_data.description()
                .at(var)
                .value("XML_ElementName")
                .toString()
            == "terminal")
        {
            writer->writeStartElement(element_data.description()
                                          .at(var)
                                          .value("XML_ElementName")
                                          .toString());
            QMapIterator<QString, QVariant> data(
                element_data.description().at(var));
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "XML_ElementName")
                    writer->writeAttribute(data.key(), data.value().toString());
            }
            writer->writeEndElement();
        }
    }
}

void SafeElement::write_PartText(QXmlStreamWriter* writer)
{
    for (int var = 0; var < element_data.description().size(); ++var)
    {
        if (element_data.description()
                .at(var)
                .value("XML_ElementName")
                .toString()
            == "text")
        {
            writer->writeStartElement(element_data.description()
                                          .at(var)
                                          .value("XML_ElementName")
                                          .toString());
            QMapIterator<QString, QVariant> data(
                element_data.description().at(var));
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "XML_ElementName")
                    writer->writeAttribute(data.key(), data.value().toString());
            }
            writer->writeEndElement();
        }
    }
}

void SafeElement::write_PartArc(QXmlStreamWriter* writer)
{
    for (int var = 0; var < element_data.description().size(); ++var)
    {
        if (element_data.description()
                .at(var)
                .value("XML_ElementName")
                .toString()
            == "arc")
        {
            writer->writeStartElement(element_data.description()
                                          .at(var)
                                          .value("XML_ElementName")
                                          .toString());
            QMapIterator<QString, QVariant> data(
                element_data.description().at(var));
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "XML_ElementName")
                    writer->writeAttribute(data.key(), data.value().toString());
            }
            writer->writeEndElement();
        }
    }
}

void SafeElement::write_PartDynamicTextField(QXmlStreamWriter* writer)
{
    for (int var = 0; var < element_data.description().size(); ++var)
    {
        if (element_data.description()
                .at(var)
                .value("XML_ElementName")
                .toString()
            == "dynamic_text")
        {
            writer->writeStartElement(element_data.description()
                                          .at(var)
                                          .value("XML_ElementName")
                                          .toString());
            QMapIterator<QString, QVariant> data(
                element_data.description().at(var));
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "XML_ElementName" && data.key() != "text"
                    && data.key() != "info_name")
                    writer->writeAttribute(data.key(), data.value().toString());
            }
            if (element_data.description().at(var).contains("text"))
            {
                writer->writeStartElement("text");
                writer->writeCharacters(element_data.description()
                                            .at(var)
                                            .value("text")
                                            .toString());
                writer->writeEndElement();
            }
            if (element_data.description().at(var).contains("info_name"))
            {
                writer->writeStartElement("info_name");
                writer->writeCharacters(element_data.description()
                                            .at(var)
                                            .value("info_name")
                                            .toString());
                writer->writeEndElement();
            }

            writer->writeEndElement();
        }
    }
}
