#ifndef SAFEELEMENT_H
#define SAFEELEMENT_H

#include "virtualelement.h"

#include <QFile>
#include <QXmlStreamWriter>

class SafeElement
{
  public:
    SafeElement(QString outputfile, VElement element);
    ~SafeElement();

  private:
    VElement element_data;

    void write_definition(QXmlStreamWriter* writer);
    void write_definition_uuid(QXmlStreamWriter* writer);
    void write_definition_name(QXmlStreamWriter* writer);
    void write_definition_kindInformation(QXmlStreamWriter* writer);
    void write_definition_elementInformations(QXmlStreamWriter* writer);
    void write_definition_informations(QXmlStreamWriter* writer);
    void write_definition_description(QXmlStreamWriter* writer);

    void write_PartLine(QXmlStreamWriter* writer);
    void write_PartRectangle(QXmlStreamWriter* writer);
    void write_PartEllipse(QXmlStreamWriter* writer);
    void write_PartCircle(QXmlStreamWriter* writer);
    void write_PartPolygon(QXmlStreamWriter* writer);
    void write_PartTerminal(QXmlStreamWriter* writer);
    void write_PartText(QXmlStreamWriter* writer);
    void write_PartArc(QXmlStreamWriter* writer);
    void write_PartDynamicTextField(QXmlStreamWriter* writer);
};

#endif // SAFEELEMENT_H
