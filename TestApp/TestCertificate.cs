using System;
using System.IO;
using System.Security.Cryptography.X509Certificates;
using System.Security.Cryptography.Xml;
using MyExtentions;
using XmlSignLibrary;

namespace TestApp
{
  public class TestCertificate
  {
    public static string CertificatePath = "C:\\Work\\certificate\\Ignatev Iurii Andreevich.cer";
    public X509Certificate Certificate { get; set; }

    public String CorrectHashExample { get; set; }
    public String HexEmptyHash { get; set; }

    public static String CorrectCertificate = "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";


    public TestCertificate()
    {
      CorrectHashExample = "XQ3+v+kTeA5PnydKtRcBFn0NH49n99z9ttqdngnTiAs=";
      HexEmptyHash = "ce85b99cc46752fffee35cab9a7b0278abb4c2d2055cff685af4912c49490f8d";
      Certificate = new X509Certificate(CertificatePath);
      
      //BECGMyTBmpZy9eDA+7QnlCIcTob7Y2cM1iZrNqlvlAK3RgIIsT9TIjKwMkwpBm3Vsmt0NdDkCZ5OdxaRq2AF1smW
      //0440863324C19A9672F5E0C0FBB42794221C4E86FB63670CD6266B36A96F9402B7460208B13F532232B0324C29066DD5B26B7435D0E4099E4E771691AB6005D6C996
      //"06200000232e00004d41473100020000301206072a85030202230106072a850302021e01863324c19a9672f5e0c0fbb42794221c4e86fb63670cd6266b36a96f9402b7460208b13f532232b0324c29066dd5b26b7435d0e4099e4e771691ab6005d6c996"
      Certificate.GetPublicKey();
      Certificate.Import(Convert.FromBase64String(CorrectCertificate));
      //Certificate.Export(X509ContentType)
      HashTest();
    }

    public void Test(SignedXmlDocument doc)
    {
      Console.WriteLine("================== Certificate Test ==================");
      var certVipNet = doc.CertificateValue.Value;
      var result = doc.CertificateValue.Value == Convert.ToBase64String(Certificate.GetRawCertData());
      Console.WriteLine("Test done: {0}", result);
      Console.WriteLine("======================================================");

      Console.WriteLine("================ Canonicalization Test ================");

      var doc2 = doc.Document.GetXmlDocument();
      
      XmlDsigExcC14NTransform t = new XmlDsigExcC14NTransform();
      var bodyNode = doc.Body.GetXmlNode();
      t.LoadInput(bodyNode);
      Stream canonicalXmlStream = (MemoryStream)t.GetOutput(typeof(Stream));
      var canonicalXml = new StreamReader(canonicalXmlStream).ReadToEnd();

      var t2 = new XmlDsigC14NTransform();
      t2.LoadInput(doc.Body.GetXmlNode());
      Stream canonicalXmlStream2 = (MemoryStream)t2.GetOutput(typeof(Stream));
      var canonicalXml2 = new StreamReader(canonicalXmlStream2).ReadToEnd();
      Console.WriteLine(canonicalXml == canonicalXml2);

      Console.WriteLine(canonicalXml);
      Console.WriteLine("======================================================");

      var signedXml = new SignedXml(doc2);
      var reference = new Reference("#body");
      reference.AddTransform(new XmlDsigExcC14NTransform());
      signedXml.AddReference(reference);

      Hash hash = new VipNetCrytoProvider().HashData(canonicalXml);
      Console.WriteLine(hash.Base64);
      Console.WriteLine(hash.Hex);

      Console.WriteLine("CorrectHashExample: {0}", CorrectHashExample);
      Console.WriteLine("CorrectHashExampleHex: {0}", Convert.FromBase64String(CorrectHashExample).ByteArrayToString());      
    }

    public void StandartSigning(SignedXmlDocument doc)
    {
      var signedXml = new SignedXml(doc.Document.GetXmlDocument());
      //signedXml.AddReference(new Reference("#CertId").AddTransform(new XmlDsigExcC14NTransform()));
    }

    public void HashTest()
    {
      string message = "This is message, length=32 bytes";
      Console.WriteLine("====================== Hash Test ======================");
      var crypto = new VipNetCrytoProvider();
      var hash1 = crypto.HashData(message);
      crypto = new VipNetCrytoProvider();
      var hash2 = crypto.HashData(message);
      if (hash1.Hex != hash2.Hex) throw new Exception("Wrong hash value");

      Console.WriteLine(hash1.Hex);      

      Console.WriteLine("======================================================");
    }
  }
}