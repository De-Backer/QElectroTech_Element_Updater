#ifndef LOADELEMENT_H
#define LOADELEMENT_H

#include <QFile>
#include <QMap>
#include <QString>
#include <QUuid>
#include <QVariant>
#include <QXmlStreamReader>

class LoadElement
{
  public:
	LoadElement(QString file);
	~LoadElement();
	QVariant definition(QString value);
	QUuid	 uuid();
	QString	 name(QString language);
	QVariant kindInformation(QString value);
	QString	 informations();

  private:
	// definition
	int		width	  = 0;
	int		height	  = 0;
	int		hotspot_x = 0;
	int		hotspot_y = 0;
	QString type;
	QString link_type;
	// uuid
	QUuid uuid_element = QUuid::createUuid();
	// name
	QMap<QString, QString> name_element;
	// kindInformation
	QMap<QString, int>	   kindInformation_show_element; // name, show
	QMap<QString, QString> kindInformation_text_element; // name, text
	// informations_element
	QString informations_element;
	QFile*	element;

	void LoadElement0_22(QXmlStreamReader* reader);
	void LoadElement0_3(QXmlStreamReader* reader);
	void LoadElement0_4(QXmlStreamReader* reader);
	void LoadElement0_5(QXmlStreamReader* reader);
	void LoadElement0_60(QXmlStreamReader* reader);
	void LoadElement0_70(QXmlStreamReader* reader);
	void LoadElement0_80(QXmlStreamReader* reader);

	void read_definition(QXmlStreamReader* reader);
	void read_definition_uuid(QXmlStreamReader* reader);
	void read_definition_name(QXmlStreamReader* reader);
	void read_definition_kindInformation(QXmlStreamReader* reader);
	void read_definition_informations(QXmlStreamReader* reader);
	void read_definition_description(QXmlStreamReader* reader);
};

#endif // LOADELEMENT_H
