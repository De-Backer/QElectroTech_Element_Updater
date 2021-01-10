#include "loadelement.h"

#include <QString>
#include <QUuid>
#include <QtDebug>
#include <catch2/catch.hpp>
#include <exception>

TEST_CASE("LoadElement 0.3.0", "0.3.0")
{
	try
	{
		LoadElement mytest(TEST_CATCH_PATH "/testfile_0_3_0.elmt");
		QMap<QString, QVariant> test_definition;
		test_definition.insert("width", 10);
		test_definition.insert("height", 30);
		test_definition.insert("hotspot_x", 5);
		test_definition.insert("hotspot_y", 0);
		test_definition.insert("type", "element");
		test_definition.insert("version", "0.3");
		CHECK(test_definition == mytest.definition());

		// uuid
		CHECK(
			QUuid("0EE598EC-C72A-43A3-B330-741E2D41940A")
				.toString()
				.toStdString()
			== mytest.uuid().toString().toStdString());

		// name
		QMap<QString, QString> test_name;
		test_name.insert("ar", "قابس و مقبس متعدد الأقطاب, تمثيل أحادي الخط");
		test_name.insert("de", "Steckverbindung komplett mit 6 Kontakten");
		test_name.insert("en", "Plug and multipolar representation\nunifilar");
		test_name.insert(
			"it",
			"Spina e presa multipolari, rappresentazione unifilare");
		test_name.insert(
			"fr",
			"Prise et fiche multipolaires, représentation\nunifilaire\n");
		test_name.insert("pl", "Złącze wielostykowe");
		test_name.insert("es", "Conector multipolar, representación unifilar");
		test_name.insert(
			"cs",
			"Zásuvka a zástrčka vícepólová, v jednopólovém znázornění");
		test_name.insert("nl", "Steker en Contact veelpolig enkellijns");
		CHECK(test_name.toStdMap() == mytest.name().toStdMap());

		// informations
		CHECK("EN 60617: 03-03-08" == mytest.informations().toStdString());

		// description
		// dit moeten we anders testen door is het een getal?, is er text, ..
		QVector<QMap<QString, QVariant>> test_description;
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "line");
			test_var.insert("x1", -5);
			test_var.insert("y1", 13);
			test_var.insert("x2", 4);
			test_var.insert("y2", 20);
			test_var.insert("length1", 1.5);
			test_var.insert("length2", 1.5);
			test_var.insert("end1", "none");
			test_var.insert("end2", "none");
			test_var.insert(
				"style",
				"line-style:normal;line-weight:thin;filling:none;color:black");
			test_var.insert("antialias", "false");
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "line");
			test_var.insert("x1", -1);
			test_var.insert("y1", 12);
			test_var.insert("x2", -1);
			test_var.insert("y2", 19);
			test_var.insert("length1", 1.5);
			test_var.insert("length2", 1.5);
			test_var.insert("end1", "none");
			test_var.insert("end2", "none");
			test_var.insert(
				"style",
				"line-style:normal;line-weight:normal;filling:none;color:"
				"black");
			test_var.insert("antialias", "false");
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "input");
			test_var.insert("rotate", "true");
			test_var.insert("size", 5);
			test_var.insert("text", "6");
			test_var.insert("x", 1);
			test_var.insert("y", 20.5);
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "input");
			test_var.insert("rotate", "true");
			test_var.insert("size", 8);
			test_var.insert("text", "_");
			test_var.insert("x", 7);
			test_var.insert("y", 14.5);
			test_var.insert("tagg", "label");
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "line");
			test_var.insert("x1", 0);
			test_var.insert("y1", 12);
			test_var.insert("x2", 0);
			test_var.insert("y2", 30);
			test_var.insert("length1", 1.5);
			test_var.insert("length2", 1.5);
			test_var.insert("end1", "none");
			test_var.insert("end2", "none");
			test_var.insert(
				"style",
				"line-style:normal;line-weight:normal;filling:none;color:"
				"black");
			test_var.insert("antialias", "false");
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "line");
			test_var.insert("x1", 0);
			test_var.insert("y1", 9);
			test_var.insert("x2", 0);
			test_var.insert("y2", 0);
			test_var.insert("length1", 1.5);
			test_var.insert("length2", 1.5);
			test_var.insert("end1", "none");
			test_var.insert("end2", "none");
			test_var.insert(
				"style",
				"line-style:normal;line-weight:normal;filling:none;color:"
				"black");
			test_var.insert("antialias", "false");
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "line");
			test_var.insert("x1", 1);
			test_var.insert("y1", 12);
			test_var.insert("x2", 1);
			test_var.insert("y2", 19);
			test_var.insert("length1", 1.5);
			test_var.insert("length2", 1.5);
			test_var.insert("end1", "none");
			test_var.insert("end2", "none");
			test_var.insert(
				"style",
				"line-style:normal;line-weight:normal;filling:none;color:"
				"black");
			test_var.insert("antialias", "false");
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "arc");
			test_var.insert("angle", -180);
			test_var.insert("antialias", "true");
			test_var.insert("height", 6);
			test_var.insert("start", -180);
			test_var.insert("width", 6);
			test_var.insert("x", -3);
			test_var.insert("y", 10);
			test_var.insert(
				"style",
				"line-style:normal;line-weight:normal;filling:none;color:"
				"black");
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "terminal");
			test_var.insert("orientation", "n");
			test_var.insert("x", 0);
			test_var.insert("y", 0);
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "terminal");
			test_var.insert("orientation", "s");
			test_var.insert("x", 0);
			test_var.insert("y", 30);
			test_description.append(test_var);
		}
		int var = 0;
		INFO("Test case start");
		for (QMap<QString, QVariant> vars : mytest.description())
		{
			INFO("vars");
			CHECK(test_description.at(var++).toStdMap() == vars.toStdMap());
		}
	}
	catch (std::exception& e)
	{
		CHECK(0 == e.what()); // what is exception?
	}
}

TEST_CASE("LoadElement line x is - 0.foo")
{
	try
	{
		LoadElement mytest(TEST_CATCH_PATH "/test_xy.elmt");
		QVector<QMap<QString, QVariant>> test_description;
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "line");
			test_var.insert("x1", 0);
			test_var.insert("y1", -16);
			test_var.insert("x2", 0);
			test_var.insert("y2", 13);
			test_var.insert("length1", 1.5);
			test_var.insert("length2", 1.5);
			test_var.insert("end1", "none");
			test_var.insert("end2", "none");
			test_var.insert(
				"style",
				"line-style:normal;line-weight:thin;filling:none;color:black");
			test_var.insert("antialias", "false");
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "line");
			test_var.insert("x1", -13.6493);
			test_var.insert("y1", 14);
			test_var.insert("x2", 12.62);
			test_var.insert("y2", 14);
			test_var.insert("length1", 1.5);
			test_var.insert("length2", 1.5);
			test_var.insert("end1", "none");
			test_var.insert("end2", "none");
			test_var.insert(
				"style",
				"line-style:normal;line-weight:thin;filling:none;color:black");
			test_var.insert("antialias", "false");
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "dynamic_text");
			test_var.insert("uuid", "{7f02ce13-533d-4501-980d-6cb67bd1110d}");
			test_var.insert("Halignment", "AlignLeft");
			test_var.insert("frame", "false");
			test_var.insert("Valignment", "AlignTop");
			test_var.insert("text_from", "ElementInfo");
			test_var.insert("font", "Sans Serif,9,-1,5,50,0,0,0,0,0");
			test_var.insert("rotation", 0);
			test_var.insert("text_width", -1);
			test_var.insert("text", "");
			test_var.insert("info_name", "label");
			test_var.insert("z", 3);
			test_var.insert("x", 8);
			test_var.insert("y", -9);
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "terminal");
			test_var.insert("orientation", "n");
			test_var.insert("x", 0);
			test_var.insert("y", -20);
			test_description.append(test_var);
		}
		int var = 0;
		INFO("Test case start");
		for (QMap<QString, QVariant> vars : mytest.description())
		{
			INFO(var);
			CHECK(test_description.at(var++).toStdMap() == vars.toStdMap());
		}
	}
	catch (std::exception& e)
	{
		CHECK(0 == e.what()); // what is exception?
	}
}
