#include "convertelement.h"

#include <QDebug>
#include <QMap>
#include <QMapIterator>
#include <QUuid>

ConvertElement::ConvertElement(LoadElement element)
{
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

ConvertElement::~ConvertElement() {}

VElement ConvertElement::GetElement() { return new_element; }
