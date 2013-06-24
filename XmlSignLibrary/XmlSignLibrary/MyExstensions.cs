using System;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Linq;

namespace MyExtentions
{
  public static class StringExtensions
  {
    public static String ToHex(this string text)
    {
      var parsed = new StringBuilder();
      foreach (var symbol in text)
      {
        int i = symbol;
        parsed.Append(i.ToString("x2"));
      }
      return parsed.ToString();
    }

    public static byte[] ToBytes(this string hexText)
    {
      var result = new byte[hexText.Length / 2];
      for (int i = 0; i < hexText.Length; i += 2)
      {
        var symbol = (byte)Int32.Parse(hexText.Substring(i, 2), NumberStyles.HexNumber);
        result[i / 2] = symbol;
      }
      return result;
    }

    public static String HexToString(this string hexText)
    {
      var parsed = new StringBuilder();
      Console.WriteLine(hexText);
      for (int i = 0; i < hexText.Length; i += 2)
      {
        var symbol = (char)Int32.Parse(hexText.Substring(i, 2), NumberStyles.HexNumber);
        parsed.Append((char)(symbol));
      }
      return parsed.ToString();
    }
  }

  public static class ByteArrayExtensions
  {
    public static byte[] Xor(this byte[] a, byte[] b)
    {
      var c = new byte[a.Length];
      for (int i = 0; i < Math.Min(a.Length, b.Length); i++)
      {
        c[i] = (byte) (a[i] ^ b[i]);
      }
      return c;
    }

    public static string ByteArrayToString(this byte[] ba)
    {
      StringBuilder hex = new StringBuilder(ba.Length*2);
      foreach (byte b in ba)
        hex.AppendFormat("{0:x2}", b);
      return hex.ToString();
    }

  }

  public static class MyExstensions
  {
    public static string ToString(this System.Xml.XmlElement node, int indentation)
    {
      using (var sw = new System.IO.StringWriter())
      {
        using (var xw = new System.Xml.XmlTextWriter(sw))
        {
          xw.Formatting = System.Xml.Formatting.None;
          //xw.Indentation = indentation;
          node.WriteContentTo(xw);
        }
        return sw.ToString();
      }
    }

    public static XElement GetXElement(this XmlNode node)
    {
      XDocument xDoc = new XDocument();
      using (XmlWriter xmlWriter = xDoc.CreateWriter())
        node.WriteTo(xmlWriter);
      return xDoc.Root;
    }

    public static XmlNode GetXmlNode(this XElement element)
    {
      using (XmlReader xmlReader = element.CreateReader(ReaderOptions.None))
      {
        XmlDocument xmlDoc = new XmlDocument();
        xmlDoc.Load(xmlReader);
        return xmlDoc;
      }
    }

    public static XDocument GetXDocument(this XmlDocument document)
    {
      XDocument xDoc = new XDocument();
      using (XmlWriter xmlWriter = xDoc.CreateWriter())
        document.WriteTo(xmlWriter);
      XmlDeclaration decl =
        document.ChildNodes.OfType<XmlDeclaration>().FirstOrDefault();
      if (decl != null)
        xDoc.Declaration = new XDeclaration(decl.Version, decl.Encoding,
                                            decl.Standalone);
      return xDoc;
    }

    public static XmlDocument GetXmlDocument(this XDocument document)
    {
      using (XmlReader xmlReader = document.CreateReader())
      {
        XmlDocument xmlDoc = new XmlDocument();
        xmlDoc.Load(xmlReader);
        if (document.Declaration != null)
        {
          XmlDeclaration dec = xmlDoc.CreateXmlDeclaration(document.Declaration.Version,
                                                           document.Declaration.Encoding,
                                                           document.Declaration.Standalone);
          xmlDoc.InsertBefore(dec, xmlDoc.FirstChild);
        }
        return xmlDoc;
      }
    }
  }
}