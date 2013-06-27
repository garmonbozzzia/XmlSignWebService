using System.Security.Cryptography.Xml;
using System.Xml;

namespace XmlSignLibrary
{
  public class SignedXmlObject : SignedXml
  {
    public SignedXmlObject(XmlDocument doc) : base(doc)
    {
      
    }
    public override XmlElement GetIdElement(XmlDocument doc, string id)
    {
      XmlElement idElem = base.GetIdElement(doc, id);

      if (idElem == null)
      {
        XmlNamespaceManager nsManager = new XmlNamespaceManager(doc.NameTable);

        nsManager.AddNamespace("wsu", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd");
        idElem = doc.SelectSingleNode("//*[@wsu:Id=\"" + id + "\"]", nsManager) as XmlElement;            
        
        if(idElem == null)
        {
          nsManager.AddNamespace("ds", "http://www.w3.org/2000/09/xmldsig#");
          idElem = doc.SelectSingleNode("//ds:"+id, nsManager) as XmlElement;
        }
      }
      

      return idElem;
    }
  }
}