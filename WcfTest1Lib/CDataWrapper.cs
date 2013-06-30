using System;
using System.IO;
using System.Runtime.Serialization;
using System.Text;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;

namespace WcfTest1Lib
{
 // example usage


  [XmlSchemaProvider("GetSchema")]
  public sealed class CDataWrapper : IXmlSerializable
  {
  
    public static XmlQualifiedName GetSchema(XmlSchemaSet xs)
    {           
      return XmlSchemaType.GetBuiltInSimpleType(XmlTypeCode.String).QualifiedName;
    }
  
    // implicit to/from string
    public static implicit operator string(CDataWrapper value)
    {
      return value == null ? null : value.Value;
    }
  
    public static implicit operator CDataWrapper(string value)
    {
      return value == null
               ? null
               : new CDataWrapper
                   {
                     Value =
                       value
                   };
    }
  
    public System.Xml.Schema.XmlSchema GetSchema()
    {            
      return null;
    }
  
    // "" => <Node/>
    // "Foo" => <Node><![CDATA[Foo]]></Node>
    public void WriteXml(XmlWriter writer)
    {
      if (!string.IsNullOrEmpty(Value))
      {
        writer.WriteCData(Value);
      }
    }
  
    // <Node/> => ""
    // <Node></Node> => ""
    // <Node>Foo</Node> => "Foo"
    // <Node><![CDATA[Foo]]></Node> => "Foo"
    public void ReadXml(XmlReader reader)
    {
      if (reader.IsEmptyElement)
      {
        Value = "";
      }
      else
      {
        reader.Read();
        
        switch (reader.NodeType)
        {
          case XmlNodeType.EndElement:
            Value = ""; // empty after all...
            break;

          case XmlNodeType.Text:
          case XmlNodeType.CDATA:
            Value = reader.ReadContentAsString();
            break;
          default:
            throw new InvalidOperationException("Expected text or CData but was: "+ reader.NodeType);
        }

        NormalizeValue();

      }
    }

    private void NormalizeValue()
    {
      string perfixData = "<![CDATA[";
      string suffixData = "]]>";
      if (Value.StartsWith(perfixData) && Value.EndsWith(suffixData))
      {
        Value = Value.Substring(perfixData.Length);
        Value = Value.Substring(0, Value.Length - suffixData.Length);
      }
    }

    // underlying value
    public string Value { get; set; }
  
    public override string ToString()
    {
      return Value;
    }
  }
}