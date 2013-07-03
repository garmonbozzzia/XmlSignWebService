using System;
using System.Linq;
using System.Xml.Linq;

namespace XmlSignLibrary
{
  public class SignedXmlDocument
  {
    public XDocument Document { get; private set; }
    public XElement Header { get { return Document.Root.Element(soapenv + "Header"); } }
    public XElement Body { get { return Document.Root.Element(soapenv + "Body"); } }
    public XElement DigestValue { 
      get
      {
        return SignedInfo
          .Element(ds + "Reference")
          .Element(ds + "DigestValue");
      } 
    }
    public XElement SignedInfo
    {
      get
      {
        return Header
          .Element(wsse + "Security")
          .Element(ds + "Signature")
          .Element(ds + "SignedInfo");
      }
    }
    public XElement SignedValue
    {
      get
      {
        return Header
          .Element(wsse + "Security")
          .Element(ds + "Signature")
          .Element(ds + "SignatureValue");
      }
    }
    public XElement CertificateValue
    {
      get
      {
        return Header
          .Element(wsse + "Security")
          .Element(wsse + "BinarySecurityToken");
      }
    }
    public XNamespace soapenv { get; set; }
    public XNamespace wsse { get; set; }
    public XNamespace ds { get; set; }
    public XNamespace wsu { get; set; }

    public SignedXmlDocument(string document)
    {
      Document = XDocument.Parse(document, LoadOptions.None);
      AddNamespaces();
      if (!Body.HasAttributes) Body.Add(new XAttribute(wsu + "Id", "body"));
      if (Document.Element(ds + "SignedInfo") == null) 
        
      try
      {
        var a = SignedInfo;
      }
      catch (Exception)
      {
        CreateSecurityElement();
      }

    }
    public override string ToString()
    {
      return Document.ToString(SaveOptions.DisableFormatting);
    }

    private void CreateSecurityElement()
    {
      Header.Add(new XElement(wsse + "Security",
                              new XAttribute(soapenv + "actor", "http://smev.gosuslugi.ru/actors/smev"),
                              new XElement(wsse + "BinarySecurityToken",
                                           new XAttribute("EncodingType",
                                                          "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-soap-message-security-1.0#Base64Binary"),
                                           new XAttribute("ValueType",
                                                          "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-x509-token-profile-1.0#X509v3"),
                                           new XAttribute(wsu + "Id", "CertId")
                                ),
                              new XElement(ds + "Signature",
                                           new XElement(ds + "SignedInfo",
                                                        new XElement(ds + "CanonicalizationMethod",
                                                                     new XAttribute("Algorithm",
                                                                                    "http://www.w3.org/2001/10/xml-exc-c14n#")
                                                          ),
                                                        new XElement(ds + "SignatureMethod",
                                                                     new XAttribute("Algorithm",
                                                                                    "http://www.w3.org/2001/04/xmldsig-more#gostr34102001-gostr3411")
                                                          ),
                                                        new XElement(ds + "Reference",
                                                                     new XAttribute("URI", "#body"),
                                                                     new XElement(ds + "Transforms",
                                                                                  new XElement(ds + "Transform",
                                                                                               new XAttribute(
                                                                                                 "Algorithm",
                                                                                                 "http://www.w3.org/2001/10/xml-exc-c14n#"))                                                                                  
                                                                       ),
                                                                     new XElement(ds + "DigestMethod",
                                                                                  new XAttribute("Algorithm",
                                                                                                 "http://www.w3.org/2001/04/xmldsig-more#gostr3411")),
                                                                     new XElement(ds + "DigestValue")
                                                          )

                                             ),
                                           new XElement(ds + "SignatureValue"),
                                           new XElement(ds + "KeyInfo",
                                                        new XElement(wsse + "SecurityTokenReference",
                                                                     new XElement(wsse + "Reference",
                                                                                  new XAttribute("URI", "#CertId"),
                                                                                  new XAttribute("ValueType",
                                                                                                 "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-x509-token-profile-1.0#X509v3")
                                                                       )
                                                          )
                                             )
                                )
                   )
        );


    }
    private void AddNamespaces()
    {
      soapenv = "http://schemas.xmlsoap.org/soap/envelope/";
      wsse = "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd";
      wsu = "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd";
      ds = "http://www.w3.org/2000/09/xmldsig#";

      try
      {
        AddNamespace(wsse, "wsse");
        AddNamespace(wsu, "wsu");
        AddNamespace(ds, "ds");
      }
      catch (Exception)
      {

      }
    }
    private void AddNamespace(XNamespace ns, string name)
    {
      if (!Document.Root.Attributes().Any(x => x.Value == ns.NamespaceName)) 
        Document.Root.Add(new XAttribute(XNamespace.Xmlns + name, ns.NamespaceName));
    }

  }
}