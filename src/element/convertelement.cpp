#include "convertelement.h"

#include <QDebug>
#include <QFont>
#include <QMap>
#include <QMapIterator>
#include <QUuid>

/**
 * @brief ConvertElement::ConvertElement
 * Convert LoadElement to VElement
 * @param element
 */
ConvertElement::ConvertElement(LoadElement element)
{
    if (element.definition().value("version") != "0.80")
    {

        qDebug() << "element is not version 0.80";
        throw std::invalid_argument("element is not version 0.80");
        return;
    }

    // verander naar het new element
    QMap<QString, QVariant>         data_definition;
    QMapIterator<QString, QVariant> data(element.definition());

    while (data.hasNext())
    {
        data.next();
        if (data.key() != "version" && data.key() != "ic"
            && data.key() != "orientation")
        { data_definition.insert(data.key(), data.value()); }
    }

    data_definition.insert("version", "0.80");
    new_element.definition(data_definition);

    QVector<QMap<QString, QVariant>> data_description;
    for (int var = 0; var < element.description().size(); ++var)
    {
        if (element.description().at(var).value("XML_ElementName").toString()
            == "terminal")
        {
            // for terminal
            // Attribute nameHidden and number is gone in V0.8
            QMap<QString, QVariant>         Element_data;
            QMapIterator<QString, QVariant> data(element.description().at(var));

            // Attribute uuid is new
            Element_data.insert("uuid", QUuid::createUuid().toString());
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "nameHidden" && data.key() != "number")
                { Element_data.insert(data.key(), data.value()); }
            }
            if (! Element_data.contains("name"))
            {
                // add name to terminal if not in element.description()
                Element_data.insert("name", "");
            }

            data_description.append(Element_data);
        }
        else if (
            element.description().at(var).value("XML_ElementName").toString()
            == "dynamic_text")
        {
            QMap<QString, QVariant>         Element_data;
            QMapIterator<QString, QVariant> data(element.description().at(var));

            // during the 0.7 dev the font property was added
            QFont font("Sans Serif", 9);
            while (data.hasNext())
            {
                data.next();
                if (data.key() == "Halignment")
                { Element_data.insert("Halignment", data.value()); }
                else if (data.key() == "Valignment")
                {
                    Element_data.insert("Valignment", data.value());
                }
                else if (data.key() == "font")
                {
                    font.fromString(data.value().toString());
                }
                else if (data.key() == "font_family")
                {
                    // during the 0.7 dev the font property was added
                    font.setFamily(data.value().toString());
                }
                else if (data.key() == "font_size")
                {
                    // during the 0.7 dev the font property was added
                    font.setPointSize(data.value().toInt());
                }
                else if (data.key() == "frame")
                {
                    Element_data.insert("frame", data.value());
                }
                else if (data.key() == "rotation")
                {
                    Element_data.insert("rotation", data.value());
                }
                else if (data.key() == "text_from")
                {
                    Element_data.insert("text_from", data.value());
                }
                else if (data.key() == "text_width")
                {
                    Element_data.insert("text_width", data.value());
                }
                else if (data.key() == "uuid")
                {
                    Element_data.insert("uuid", data.value());
                }
                else if (data.key() == "x")
                {
                    Element_data.insert("x", data.value());
                }
                else if (data.key() == "y")
                {
                    Element_data.insert("y", data.value());
                }
                else if (data.key() == "z")
                {
                    Element_data.insert("z", data.value());
                }
                else if (data.key() == "text")
                {
                    Element_data.insert("text", data.value());
                }
                else if (data.key() == "info_name")
                {
                    Element_data.insert("info_name", data.value());
                }
                else if (data.key() == "XML_ElementName")
                {
                    Element_data.insert("XML_ElementName", data.value());
                }
                else
                {
                    throw std::invalid_argument(
                        "dynamic_text description ' " + data.key().toStdString()
                        + "' mising in convertelement");
                }
            }
            Element_data.insert("font", font.toString());
            data_description.append(Element_data);
        }
        else if (
            element.description().at(var).value("XML_ElementName").toString()
            == "input")
        {
            // for input
            // converted to dynamic text
            // see 02fb84caec7ca4df682edf7e4bee2202ab1d785b
            QMap<QString, QVariant>         Element_data;
            QMapIterator<QString, QVariant> data(element.description().at(var));

            Element_data.insert("XML_ElementName", "dynamic_text");
            // Attribute uuid is new
            Element_data.insert("uuid", QUuid::createUuid().toString());

            Element_data.insert("rotation", "0");
            Element_data.insert("text_from", "UserText");
            Element_data.insert("text_width", "-1");
            Element_data.insert("frame", "false");
            Element_data.insert("Halignment", "AlignLeft");
            Element_data.insert("Valignment", "AlignTop");
            double size = 9, y = 0;
            while (data.hasNext())
            {
                data.next();
                if (data.key() == "text")
                { Element_data.insert("text", data.value()); }
                else if (data.key() == "size")
                {
                    size = data.value().toDouble();
                    // converted size in font
                    Element_data.insert(
                        "font",
                        "Sans Serif," + data.value().toString()
                            + ",-1,5,50,0,0,0,0,0");
                }
                else if (data.key() == "x")
                {
                    Element_data.insert("x", data.value());
                }
                else if (data.key() == "y")
                {
                    y = data.value().toDouble();
                }
                else if (data.key() == "tagg" && data.value() == "label")
                {
                    Element_data.insert("info_name", data.value());
                }
                else
                {
                    throw std::invalid_argument(
                        "input description ' " + data.key().toStdString()
                        + "' mising in convertelement");
                }
            }
            Element_data.insert("y", y - (size * 2 + 5) / 2);
            Element_data.insert("z", 3);

            /* <input
             * x="-44"
             * y="0"
             * size="9" 23-18=5
             * rotate="true"
             * text="/"/>*/

            /*<dynamic_text
             * x="-44"
             * z="3"
             * font="Sans Serif,9,-1,5,50,0,0,0,0,0"
             * text_from="UserText"
             * Valignment="AlignTop"
             * y="-11.5"
             * rotation="0"
             * text_width="-1"
             * uuid="{858d8e0b-bfa1-486c-a56f-ae7aea701649}"
             * frame="false"
             * Halignment="AlignLeft" >
             * <text>/</text>
             * </dynamic_text>
             */
            data_description.append(Element_data);
        }
        else
        {
            data_description.append(element.description().at(var));
        }
    }
    new_element.description(data_description);

    new_element.elementInformations(element.elementInformations());
    new_element.informations(element.informations());
    new_element.kindInformation(element.kindInformation());
    new_element.name(element.name());
    new_element.uuid(element.uuid());
}

/**
 * @brief ConvertElement::ConvertElement
 * Fix and clean VElement
 * @param element
 */
ConvertElement::ConvertElement(VElement element)
{
    throw std::invalid_argument("ConvertElement ToDo");
    new_element = element;
}

ConvertElement::~ConvertElement() {}

/**
 * @brief ConvertElement::GetElement
 * @return
 */
VElement ConvertElement::GetElement() { return new_element; }
