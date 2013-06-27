using System;
using System.IO;
using System.Security.Cryptography.X509Certificates;
using System.Xml;
using System.Xml.Linq;
using MyExtentions;
using XmlSignLibrary;

namespace TestApp
{
  public class SignatureVerifier
  {


    public static bool Verify(string xml, VipNetCrytoProvider provider)
    {
      XmlDocument doc = XDocument.Parse(xml).GetXmlDocument();
      var body = Canonicalizer.GetObject(doc, "#body");
      var bodyHash = provider.HashData(body);

      XmlNamespaceManager nsManager = new XmlNamespaceManager(doc.NameTable);
      nsManager.AddNamespace("ds", "http://www.w3.org/2000/09/xmldsig#");
      nsManager.AddNamespace("soapenv", "http://schemas.xmlsoap.org/soap/envelope/");
      nsManager.AddNamespace("wsse", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd");
      nsManager.AddNamespace("wsu", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd");

      var digestValue = (doc.SelectSingleNode("//soapenv:Envelope/soapenv:Header/wsse:Security/ds:Signature/ds:SignedInfo/ds:Reference/ds:DigestValue", nsManager) as XmlElement).InnerText;
      if(bodyHash.Base64 != digestValue) 
        return false;
     
      var signedInfo = Canonicalizer.GetObject(doc, "#SignedInfo");
      //using (var file = File.CreateText("original-signedInfo" + ".txt"))
      //{
      //  file.WriteLine(signedInfo);
      //}

      using (var file = File.OpenText("original-signedInfo" + ".txt"))
      {
        var signedInfoWithoutDs = file.ReadToEnd();
        Signature sig = provider.SigningHash(provider.HashData(signedInfoWithoutDs));
      }
      
      var signedInfoHash = provider.HashData(signedInfo);
      var signature = provider.SigningHash(signedInfoHash);
      
      var signatureValue = (doc.SelectSingleNode("//soapenv:Envelope/soapenv:Header/wsse:Security/ds:Signature/ds:SignatureValue", nsManager) as XmlElement).InnerText;
      
      var certificateBase64 = (doc.SelectSingleNode("//soapenv:Envelope/soapenv:Header/wsse:Security/wsse:BinarySecurityToken", nsManager) as XmlElement).InnerText;
      X509Certificate certificate = new X509Certificate(Convert.FromBase64String(certificateBase64));


      //var signature = new Signature {SignedHash = signedInfoHash, Bytes = Convert.FromBase64String(signatureValue)};
      signature.Bytes = Convert.FromBase64String(signatureValue);

      return provider.VerifySignature(signature);
    }    
  }
}