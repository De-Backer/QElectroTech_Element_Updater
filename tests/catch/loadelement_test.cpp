#include "loadelement.h"

#include <QUuid>
#include <QtDebug>
#include <catch2/catch.hpp>
#include <exception>

TEST_CASE("LoadElement 0.3.0", "0.3.0")
{
	try
	{
		LoadElement mytest(TEST_CATCH_PATH "/testfile_0_3_0.elmt");
		CHECK(10 == mytest.definition("width").toInt());
		CHECK(30 == mytest.definition("height").toInt());
		CHECK(5 == mytest.definition("hotspot_x").toInt());
		CHECK(0 == mytest.definition("hotspot_y").toInt());
		CHECK("element" == mytest.definition("type").toString().toStdString());
		// no link_type
		// Todo wat moet dit zijn def?
		CHECK("" == mytest.definition("link_type").toString().toStdString());
		// no version in definition but in file => version="0.3"
		// Todo wat moet dit zijn?
		CHECK("0.3" == mytest.definition("version"));

		// Todo een beter manier vinden voor random waarden
		REQUIRE_THROWS_WITH(mytest.definition("definition"), "unknown value");
		REQUIRE_THROWS_WITH(mytest.definition("name"), "unknown value");
		REQUIRE_THROWS_WITH(mytest.definition("description"), "unknown value");

		QMap<QString, QVariant> test_definition;
		test_definition.insert("width", 10);
		test_definition.insert("height", 30);
		test_definition.insert("hotspot_x", 5);
		test_definition.insert("hotspot_y", 0);
		test_definition.insert("type", "element");
		test_definition.insert("link_type", "");
		test_definition.insert("version", "0.3");
		CHECK(test_definition == mytest.definition());

		// uuid
		CHECK(
			QUuid("0EE598EC-C72A-43A3-B330-741E2D41940A")
				.toString()
				.toStdString()
			== mytest.uuid().toString().toStdString());

		// name
		CHECK(
			"قابس و مقبس متعدد الأقطاب, تمثيل أحادي الخط"
			== mytest.name("ar").toStdString());
		CHECK(
			"Steckverbindung komplett mit 6 Kontakten"
			== mytest.name("de").toStdString());
		CHECK(
			"Plug and multipolar representation\nunifilar"
			== mytest.name("en").toStdString());
		CHECK(
			"Spina e presa multipolari, rappresentazione unifilare"
			== mytest.name("it").toStdString());
		CHECK(
			"Prise et fiche multipolaires, représentation\nunifilaire\n"
			== mytest.name("fr").toStdString());
		CHECK("Złącze wielostykowe" == mytest.name("pl").toStdString());
		CHECK(
			"Conector multipolar, representación unifilar"
			== mytest.name("es").toStdString());
		CHECK(
			"Zásuvka a zástrčka vícepólová, v jednopólovém znázornění"
			== mytest.name("cs").toStdString());
		CHECK(
			"Steker en Contact veelpolig enkellijns"
			== mytest.name("nl").toStdString());

		// test defkey en
		CHECK(
			"Plug and multipolar representation\nunifilar"
			== mytest.name("ww").toStdString());
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
			test_var.insert("tagg", "");
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
			test_var.insert("nameHidden", "");
			test_var.insert("number", 0);
			test_var.insert("orientation", "n");
			test_var.insert("name", "");
			test_var.insert("x", 0);
			test_var.insert("y", 0);
			test_description.append(test_var);
		}
		{
			QMap<QString, QVariant> test_var;
			test_var.insert("XML_ElementName", "terminal");
			test_var.insert("nameHidden", "");
			test_var.insert("number", 0);
			test_var.insert("orientation", "s");
			test_var.insert("name", "");
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
