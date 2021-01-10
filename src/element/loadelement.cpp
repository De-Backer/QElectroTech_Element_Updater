#include "loadelement.h"

#include <QDebug>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>
#include <QtXml>

LoadElement::LoadElement(QString file)
{
    QFile element(file);

    if (! element.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "element is not open";
        throw std::invalid_argument("element is not open");
        return;
    }
    if (! element.isReadable())
    {
        qDebug() << "element is not Readable";
        throw std::invalid_argument("element is not Readable");
        return;
    }
    QXmlStreamReader* reader = new QXmlStreamReader(&element);

    while (reader->readNextStartElement())
    {
        if (reader->name() == QLatin1String("definition"))
            read_definition(reader);
        else if (reader->name() == QLatin1String("uuid"))
            read_definition_uuid(reader);
        else if (reader->name() == "names")
            read_definition_name(reader);
        else if (reader->name() == QLatin1String("informations"))
            read_definition_informations(reader);
        else if (reader->name() == QLatin1String("kindInformations"))
            read_definition_kindInformation(reader);
        else if (reader->name() == QLatin1String("elementInformations"))
            read_definition_elementInformations(reader);
        else if (reader->name() == QLatin1String("description"))
            read_definition_description(reader);
        else
        {
            qDebug() << reader->name();
            reader->skipCurrentElement();
        }
    }

    if (reader->hasError())
    {
        throw std::invalid_argument(
            "XMLerror:" + reader->errorString().toStdString()
            + " at lineNumber "
            + QString::number(reader->lineNumber()).toStdString());
    }
    element.close();
    delete reader;
}

LoadElement::~LoadElement() {}

QMap<QString, QVariant> LoadElement::definition() { return definition_element; }

QUuid LoadElement::uuid() { return uuid_element; }

QMap<QString, QString> LoadElement::name() { return name_element; }

QMap<QString, QVector<QVariant>> LoadElement::kindInformation()
{
    return kindInformation_element;
}

QMap<QString, QVector<QVariant>> LoadElement::elementInformations()
{
    return elementInformations_element;
}

QString LoadElement::informations() { return informations_element; }

QVector<QMap<QString, QVariant>> LoadElement::description()
{
    return description_element;
}

void LoadElement::read_definition(QXmlStreamReader* reader)
{
    if (reader->attributes().hasAttribute("version"))
        definition_element.insert(
            "version",
            reader->attributes().value("version").toString());
    if (reader->attributes().hasAttribute("width"))
        definition_element.insert(
            "width",
            reader->attributes().value("width").toInt());
    if (reader->attributes().hasAttribute("height"))
        definition_element.insert(
            "height",
            reader->attributes().value("height").toInt());
    if (reader->attributes().hasAttribute("hotspot_x"))
        definition_element.insert(
            "hotspot_x",
            reader->attributes().value("hotspot_x").toInt());
    if (reader->attributes().hasAttribute("hotspot_y"))
        definition_element.insert(
            "hotspot_y",
            reader->attributes().value("hotspot_y").toInt());
    if (reader->attributes().hasAttribute("type"))
        definition_element.insert(
            "type",
            reader->attributes().value("type").toString());
    if (reader->attributes().hasAttribute("link_type"))
        definition_element.insert(
            "link_type",
            reader->attributes().value("link_type").toString());
    if (reader->attributes().hasAttribute("ic"))
        definition_element.insert(
            "ic",
            reader->attributes().value("ic").toString());
    if (reader->attributes().hasAttribute("orientation"))
        definition_element.insert(
            "orientation",
            reader->attributes().value("orientation").toString());
}

void LoadElement::read_definition_uuid(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement() && reader->name() == QLatin1String("uuid"));
    uuid_element =
        QUuid::fromString(reader->attributes().value("uuid").toString());
    reader->readNextStartElement();
}

void LoadElement::read_definition_name(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement() && reader->name() == QLatin1String("names"));

    while (reader->readNextStartElement())
    {
        if (reader->name() == QLatin1String("name"))
        {
            Q_ASSERT(
                reader->isStartElement()
                && reader->name() == QLatin1String("name"));
            QString key, value;

            key   = reader->attributes().value("lang").toString();
            value = reader->readElementText();
            name_element.insert(key, value);
        }
        else
        {
            qDebug() << reader->name();
            reader->skipCurrentElement();
        }
    }

    if (reader->hasError())
    {
        throw std::invalid_argument(
            "XMLerror:" + reader->errorString().toStdString()
            + " at lineNumber "
            + QString::number(reader->lineNumber()).toStdString());
    }
}

void LoadElement::read_definition_kindInformation(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement()
        && reader->name() == QLatin1String("kindInformations"));
    while (reader->readNextStartElement())
    {
        if ((reader->name() == "kindInformation"))
        {
            QString           key;
            QVector<QVariant> value;
            key = reader->attributes().value("name").toString();
            value.append(reader->attributes().value("show").toInt());
            value.append(reader->readElementText());
            kindInformation_element.insert(key, value);
        }
        else
        {
            qDebug() << reader->name();
            reader->skipCurrentElement();
        }
    }

    if (reader->hasError())
    {
        throw std::invalid_argument(
            "XMLerror:" + reader->errorString().toStdString()
            + " at lineNumber "
            + QString::number(reader->lineNumber()).toStdString());
    }
}

void LoadElement::read_definition_elementInformations(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement()
        && reader->name() == QLatin1String("elementInformations"));
    while (reader->readNextStartElement())
    {
        if ((reader->name() == "elementInformation"))
        {
            QString           key;
            QVector<QVariant> value;
            key = reader->attributes().value("name").toString();
            value.append(reader->attributes().value("show").toInt());
            value.append(reader->readElementText());
            elementInformations_element.insert(key, value);
        }
        else
        {
            qDebug() << reader->name();
            reader->skipCurrentElement();
        }
    }

    if (reader->hasError())
    {
        throw std::invalid_argument(
            "XMLerror:" + reader->errorString().toStdString()
            + " at lineNumber "
            + QString::number(reader->lineNumber()).toStdString());
    }
}

void LoadElement::read_definition_informations(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement()
        && reader->name() == QLatin1String("informations"));
    informations_element = reader->readElementText();
}

void LoadElement::read_definition_description(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement()
        && reader->name() == QLatin1String("description"));
    while (reader->readNextStartElement())
    {
        if (reader->name() == "line") { read_PartLine(reader); }
        else if (reader->name() == QLatin1String("rect"))
            read_PartRectangle(reader);
        else if (reader->name() == QLatin1String("ellipse"))
            read_PartEllipse(reader);
        else if (reader->name() == QLatin1String("circle"))
            read_PartCircle(reader);
        else if (reader->name() == QLatin1String("polygon"))
            read_PartPolygon(reader);
        else if (reader->name() == QLatin1String("terminal"))
            read_PartTerminal(reader);
        else if (reader->name() == QLatin1String("text"))
            read_PartText(reader);
        else if (reader->name() == QLatin1String("arc"))
            read_PartArc(reader);
        else if (reader->name() == QLatin1String("dynamic_text"))
            read_PartDynamicTextField(reader);
        else if (reader->name() == QLatin1String("input"))
            read_PartInput(reader);
        else
        {
            qDebug() << reader->name();
            reader->skipCurrentElement();
        }
    }
    if (reader->hasError())
    {
        throw std::invalid_argument(
            "XMLerror:" + reader->errorString().toStdString());
    }
}

void LoadElement::read_PartLine(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement() && reader->name() == QLatin1String("line"));
    QMap<QString, QVariant> var;
    bool                    ok = true;
    var.insert("XML_ElementName", reader->name().toString());
    if (reader->attributes().hasAttribute("x1"))
        var.insert("x1", reader->attributes().value("x1").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("y1"))
        var.insert("y1", reader->attributes().value("y1").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("x2"))
        var.insert("x2", reader->attributes().value("x2").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("y2"))
        var.insert("y2", reader->attributes().value("y2").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("length1"))
        var.insert(
            "length1",
            reader->attributes().value("length1").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("length2"))
        var.insert(
            "length2",
            reader->attributes().value("length2").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("end1"))
        var.insert("end1", reader->attributes().value("end1").toString());
    if (reader->attributes().hasAttribute("end2"))
        var.insert("end2", reader->attributes().value("end2").toString());
    if (reader->attributes().hasAttribute("style"))
        var.insert("style", reader->attributes().value("style").toString());
    if (reader->attributes().hasAttribute("antialias"))
        var.insert(
            "antialias",
            reader->attributes().value("antialias").toString());
    description_element.append(var);
    reader->readNextStartElement();
}

void LoadElement::read_PartRectangle(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement() && reader->name() == QLatin1String("rect"));
    QMap<QString, QVariant> var;
    bool                    ok = true;
    var.insert("XML_ElementName", reader->name().toString());
    if (reader->attributes().hasAttribute("x"))
        var.insert("x", reader->attributes().value("x").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("y"))
        var.insert("y", reader->attributes().value("y").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("height"))
        var.insert(
            "height",
            reader->attributes().value("height").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("width"))
        var.insert("width", reader->attributes().value("width").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("style"))
        var.insert("style", reader->attributes().value("style").toString());
    if (reader->attributes().hasAttribute("antialias"))
        var.insert(
            "antialias",
            reader->attributes().value("antialias").toString());
    description_element.append(var);
    reader->readNextStartElement();
}

void LoadElement::read_PartEllipse(QXmlStreamReader* reader)
{
    // diameter
    Q_ASSERT(
        reader->isStartElement() && reader->name() == QLatin1String("ellipse"));
    QMap<QString, QVariant> var;
    bool                    ok = true;
    var.insert("XML_ElementName", reader->name().toString());
    if (reader->attributes().hasAttribute("x"))
        var.insert("x", reader->attributes().value("x").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("y"))
        var.insert("y", reader->attributes().value("y").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("height"))
        var.insert(
            "height",
            reader->attributes().value("height").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("width"))
        var.insert("width", reader->attributes().value("width").toDouble());
    if (reader->attributes().hasAttribute("style"))
        var.insert("style", reader->attributes().value("style").toString());
    if (reader->attributes().hasAttribute("antialias"))
        var.insert(
            "antialias",
            reader->attributes().value("antialias").toString());
    description_element.append(var);
    reader->readNextStartElement();
}

void LoadElement::read_PartCircle(QXmlStreamReader* reader)
{
    // diameter
    Q_ASSERT(
        reader->isStartElement() && reader->name() == QLatin1String("circle"));
    QMap<QString, QVariant> var;
    bool                    ok = true;
    var.insert("XML_ElementName", reader->name().toString());
    if (reader->attributes().hasAttribute("x"))
        var.insert("x", reader->attributes().value("x").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("y"))
        var.insert("y", reader->attributes().value("y").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("diameter"))
        var.insert(
            "diameter",
            reader->attributes().value("diameter").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("style"))
        var.insert("style", reader->attributes().value("style").toString());
    if (reader->attributes().hasAttribute("antialias"))
        var.insert(
            "antialias",
            reader->attributes().value("antialias").toString());
    description_element.append(var);
    reader->readNextStartElement();
}

void LoadElement::read_PartPolygon(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement() && reader->name() == QLatin1String("polygon"));
    QMap<QString, QVariant> var;
    bool                    ok = true;
    var.insert("XML_ElementName", reader->name().toString());
    if (reader->attributes().hasAttribute("style"))
        var.insert("style", reader->attributes().value("style").toString());
    if (reader->attributes().hasAttribute("antialias"))
        var.insert(
            "antialias",
            reader->attributes().value("antialias").toString());
    if (reader->attributes().hasAttribute("closed"))
        var.insert("closed", reader->attributes().value("closed").toString());
    int nr = 1;
    while (reader->attributes().hasAttribute(QString("x%1").arg(nr)))
    {
        var.insert(
            QString("x%1").arg(nr),
            reader->attributes().value(QString("x%1").arg(nr)).toDouble(&ok));
        if (! ok)
            throw std::invalid_argument(
                QString::number(__LINE__).toStdString() + __FILE__);
        var.insert(
            QString("y%1").arg(nr),
            reader->attributes().value(QString("y%1").arg(nr)).toDouble(&ok));
        if (! ok)
            throw std::invalid_argument(
                QString::number(__LINE__).toStdString() + __FILE__);
        ++nr;
    }
    description_element.append(var);

    reader->readNextStartElement();
}

void LoadElement::read_PartTerminal(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement()
        && reader->name() == QLatin1String("terminal"));
    QMap<QString, QVariant> var;
    bool                    ok = true;
    var.insert("XML_ElementName", reader->name().toString());
    if (reader->attributes().hasAttribute("x"))
        var.insert("x", reader->attributes().value("x").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("y"))
        var.insert("y", reader->attributes().value("y").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("orientation"))
        var.insert(
            "orientation",
            reader->attributes().value("orientation").toString());
    if (reader->attributes().hasAttribute("number"))
        var.insert("number", reader->attributes().value("number").toInt(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("name"))
        var.insert("name", reader->attributes().value("name").toString());
    if (reader->attributes().hasAttribute("nameHidden"))
        var.insert(
            "nameHidden",
            reader->attributes().value("nameHidden").toString());
    if (reader->attributes().hasAttribute("uuid"))
        var.insert("uuid", reader->attributes().value("uuid").toString());
    description_element.append(var);

    reader->readNextStartElement();
}

void LoadElement::read_PartText(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement() && reader->name() == QLatin1String("text"));
    QMap<QString, QVariant> var;
    bool                    ok = true;
    var.insert("XML_ElementName", reader->name().toString());
    if (reader->attributes().hasAttribute("x"))
        var.insert("x", reader->attributes().value("x").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("y"))
        var.insert("y", reader->attributes().value("y").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("rotation"))
        var.insert(
            "rotation",
            reader->attributes().value("rotation").toString());
    if (reader->attributes().hasAttribute("font"))
        var.insert("font", reader->attributes().value("font").toString());
    if (reader->attributes().hasAttribute("text"))
        var.insert("text", reader->attributes().value("text").toString());
    if (reader->attributes().hasAttribute("color"))
        var.insert("color", reader->attributes().value("color").toString());
    description_element.append(var);

    reader->readNextStartElement();
}

void LoadElement::read_PartArc(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement() && reader->name() == QLatin1String("arc"));
    QMap<QString, QVariant> var;
    bool                    ok = true;
    var.insert("XML_ElementName", reader->name().toString());
    if (reader->attributes().hasAttribute("x"))
        var.insert("x", reader->attributes().value("x").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("y"))
        var.insert("y", reader->attributes().value("y").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("height"))
        var.insert(
            "height",
            reader->attributes().value("height").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("width"))
        var.insert("width", reader->attributes().value("width").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("start"))
        var.insert("start", reader->attributes().value("start").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("angle"))
        var.insert("angle", reader->attributes().value("angle").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("style"))
        var.insert("style", reader->attributes().value("style").toString());
    if (reader->attributes().hasAttribute("antialias"))
        var.insert(
            "antialias",
            reader->attributes().value("antialias").toString());
    description_element.append(var);
    reader->readNextStartElement();
}

void LoadElement::read_PartDynamicTextField(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement()
        && reader->name() == QLatin1String("dynamic_text"));
    QMap<QString, QVariant> var;
    bool                    ok = true;
    var.insert("XML_ElementName", reader->name().toString());
    if (reader->attributes().hasAttribute("x"))
        var.insert("x", reader->attributes().value("x").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("y"))
        var.insert("y", reader->attributes().value("y").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("z")) // stacking order
        var.insert("z", reader->attributes().value("z").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("rotation"))
        var.insert(
            "rotation",
            reader->attributes().value("rotation").toString());
    if (reader->attributes().hasAttribute("text_width"))
        var.insert(
            "text_width",
            reader->attributes().value("text_width").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("text_from"))
        var.insert(
            "text_from",
            reader->attributes().value("text_from").toString());
    if (reader->attributes().hasAttribute("Valignment"))
        var.insert(
            "Valignment",
            reader->attributes().value("Valignment").toString());
    if (reader->attributes().hasAttribute("Halignment"))
        var.insert(
            "Halignment",
            reader->attributes().value("Halignment").toString());
    if (reader->attributes().hasAttribute("font"))
        var.insert("font", reader->attributes().value("font").toString());
    if (reader->attributes().hasAttribute("font_family"))
        var.insert(
            "font_family",
            reader->attributes().value("font_family").toString());
    if (reader->attributes().hasAttribute("font_size"))
        var.insert(
            "font_size",
            reader->attributes().value("font_size").toString());
    if (reader->attributes().hasAttribute("frame"))
        var.insert("frame", reader->attributes().value("frame").toString());
    if (reader->attributes().hasAttribute("uuid"))
        var.insert(
            "uuid",
            QUuid::fromString(reader->attributes().value("uuid").toString()));
    while (reader->readNextStartElement())
    {
        if (reader->name() == "text")
            var.insert("text", reader->readElementText());
        else if (reader->name() == QLatin1String("info_name"))
            var.insert("info_name", reader->readElementText());
        else
            reader->skipCurrentElement();
    }
    if (reader->hasError())
    {
        throw std::invalid_argument(
            "XMLerror:" + reader->errorString().toStdString());
    }
    description_element.append(var);
}

void LoadElement::read_PartInput(QXmlStreamReader* reader)
{
    Q_ASSERT(
        reader->isStartElement() && reader->name() == QLatin1String("input"));
    QMap<QString, QVariant> var;
    bool                    ok = true;
    var.insert("XML_ElementName", reader->name().toString());
    if (reader->attributes().hasAttribute("x"))
        var.insert("x", reader->attributes().value("x").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("y"))
        var.insert("y", reader->attributes().value("y").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("size"))
        var.insert("size", reader->attributes().value("size").toDouble(&ok));
    if (! ok)
        throw std::invalid_argument(
            QString::number(__LINE__).toStdString() + __FILE__);
    if (reader->attributes().hasAttribute("rotate"))
        var.insert("rotate", reader->attributes().value("rotate").toString());
    if (reader->attributes().hasAttribute("tagg"))
        var.insert("tagg", reader->attributes().value("tagg").toString());
    if (reader->attributes().hasAttribute("text"))
        var.insert("text", reader->attributes().value("text").toString());
    description_element.append(var);
    reader->readNextStartElement();
}
