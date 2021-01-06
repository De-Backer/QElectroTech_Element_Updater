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
            == "polygon")
        {
            // for polygon
            // Attribute closed is gone in V0.8
            QMap<QString, QVariant>         Element_data;
            QMapIterator<QString, QVariant> data(element.description().at(var));
            while (data.hasNext())
            {
                data.next();
                if (data.key() != "closed")
                { Element_data.insert(data.key(), data.value()); }
            }
            data_description.append(Element_data);
        }
        else if (
            element.description().at(var).value("XML_ElementName").toString()
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
