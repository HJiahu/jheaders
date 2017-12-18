#include<iostream>
#include"format.h"
#include"ezlog.h"
#include"filesystem.h"
#include"json.h"
#include"string_utils.h"
#include"xml_utils.h"
using namespace std;
namespace jh = jheaders;
using namespace rapidxml;

extern string xml_sample;


int main()
{
    //   xml_document<> doc;    // character type defaults to char
    //   doc.parse<0> ( (char*) xml_sample.c_str()); // 0 means default parse flags
    //   cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
    //xml_node<> *node = doc.first_node()->first_node("object")->first_node("bndbox");
    //cout << *node;
    //   //xml_node<> *node = doc.first_node ("bndbox");
    //   cout << "Node object has value " << node->value() << "\n";
    //
    //   for (xml_attribute<> *attr = node->first_attribute();
    //           attr; attr = attr->next_attribute())
    //   {
    //       cout << "Node foobar has attribute " << attr->name() << " ";
    //       cout << "with value " << attr->value() << "\n";
    //   }
    jh::XML xml (R"(D:\MyPaperData\over_head\xml\a739.xml)");
    cout << xml.node_str ({"annotation", "object", "bndbox"}, true) << endl;
    cout << xml.node_str ({ "annotation", "object", "bndbox", "xmin" }, true) << endl;
    cout << xml.node_str ({ "annotation", "object", "name" }, true) << endl;
#ifdef _MSC_VER
    system ("pause");
#endif
}




string xml_sample = R"(
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<annotation verified="no">
  <folder>series1</folder>
  <filename>a739.jpeg</filename>
  
  <source>
    <database>Unknown</database>
  </source>
  <size>
    <width>640</width>
    <height>480</height>
    <depth>3</depth>
  </size>
  <segmented>0</segmented>
  <object>
    <name>head</name>
    <pose>Unspecified</pose>
    <truncated>0</truncated>
    <difficult>0</difficult>
    <bndbox>
      <xmin>500</xmin>
      <ymin>190</ymin>
      <xmax>592</xmax>
      <ymax>283</ymax>
    </bndbox>
  </object>
</annotation>
)";
