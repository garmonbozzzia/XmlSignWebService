using System;
using System.IO;
using System.Security.Cryptography;
using System.Security.Cryptography.Xml;
using System.Text;
using System.Xml;
using MyExtentions;

namespace XmlSignLibrary
{
  public class Canonicalizer
  {
    private static bool Verify(string obj, byte[] sha1Hash)
    {
      return Convert.ToBase64String(sha1Hash) == Convert.ToBase64String( SHA1.Create().ComputeHash(Encoding.UTF8.GetBytes(obj)));
    }

    public static string GetDocument(SignedXmlDocument doc)
    {
      Transform transform = new XmlDsigExcC14NTransform();
      transform.LoadInput(doc.Document.GetXmlDocument());
      return new StreamReader((MemoryStream)transform.GetOutput()).ReadToEnd();
    }

    public static string GetObject(XmlDocument doc, string id)
    {
      var signedXml = new SignedXmlObject(doc) { KeyInfo = new KeyInfo(), SigningKey = (RSA)new RSACryptoServiceProvider() };

      var transform = new XmlDsigExcC14NTransform();


      var reference = new Reference { Uri = id };
      reference.AddTransform(transform);
      signedXml.AddReference(reference);

      signedXml.ComputeSignature();

      
      var result = new StreamReader((MemoryStream)transform.GetOutput()).ReadToEnd();
      if (!Verify(result, reference.DigestValue)) throw new Exception("Wrong canonicalization object");

      //using (var file = File.CreateText(id.Replace("#", "canonical-")+".txt"))
      //{
      //  file.WriteLine(result);
      //}

      return result;
    }

    public static string GetObject2(XmlDocument doc, string id)
    {
      var signedXml = new SignedXmlObject(doc) { KeyInfo = new KeyInfo(), SigningKey = (RSA)new RSACryptoServiceProvider() };

      var transform1 = new XmlDsigEnvelopedSignatureTransform();
      var transform2 = new XmlDsigC14NWithCommentsTransform();


      var reference = new Reference { Uri = id };

      reference.AddTransform(transform1);
      reference.AddTransform(transform2);
      signedXml.AddReference(reference);

      signedXml.ComputeSignature();
      //signedXml.

      AsymmetricAlgorithm algorithm = new ECDsaCng();
      signedXml.CheckSignature(algorithm);

      var result = new StreamReader((MemoryStream)transform2.GetOutput()).ReadToEnd();
      if (!Verify(result, reference.DigestValue)) throw new Exception("Wrong canonicalization object");

      //using (var file = File.CreateText(id.Replace("#", "canonical2-") + ".txt"))
      //{
      //  file.WriteLine(result);
      //}

      return result;
    }
  }
}