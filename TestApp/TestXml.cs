using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using System.Security.Cryptography.Xml;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Xml;
using System.Xml.Linq;
using MyExtentions;
using XmlSignLibrary;
using Signature = System.Security.Cryptography.Xml.Signature;

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

  public class TestXml
  {
    //public static String Xml = "<S:Envelope xmlns:S=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:ds=\"http://www.w3.org/2000/09/xmldsig#\" xmlns:wsse=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd\" xmlns:wsu=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\"><S:Header><wsse:Security S:actor=\"http://smev.gosuslugi.ru/actors/smev\"><wsse:BinarySecurityToken EncodingType=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-soap-message-security-1.0#Base64Binary\" ValueType=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-x509-token-profile-1.0#X509v3\" wsu:Id=\"CertId\">MIIFtzCCBWagAwIBAgIDIk6iMAgGBiqFAwICAzCCAfYxGTAXBgNVBAQMENCc0LXQtNCy0LXQtNC10LIxLDAqBgNVBCoMI9CQ0L3QsNGC0L7Qu9C40Lkg0JHQvtGA0LjRgdC+0LLQuNGHMRkwFwYDVQQHDBDQsy4g0JzQvtGB0LrQstCwMSMwIQYDVQQJDBrRg9C7LiDQmNC70YzQuNC90LrQsCwg0LQuOTGBojCBnwYJKoZIhvcNAQkCDIGR0JTQsNC90L3Ri9C5INGB0LXRgNGC0LjRhNC40LrQsNGCINC+0YLQutGA0YvRgtC+0LPQviDQutC70Y7Rh9CwINC40YHQv9C+0LvRjNC30YPQtdGC0YHRjyDRgdC+INGB0YDQtdC00YHRgtCy0L7QvCDQodCa0JfQmCDQmtGA0LjQv9GC0L4g0J/RgNC+IENTUDELMAkGA1UEBhMCUlUxODA2BgNVBAoML9Ck0LXQtNC10YDQsNC70YzQvdC+0LUg0LrQsNC30L3QsNGH0LXQudGB0YLQstC+MX8wfQYDVQQDDHbQo9C/0L7Qu9C90L7QvNC+0YfQtdC90L3Ri9C5INGD0LTQvtGB0YLQvtCy0LXRgNGP0Y7RidC40Lkg0YbQtdC90YLRgCDQpNC10LTQtdGA0LDQu9GM0L3QvtCz0L4g0LrQsNC30L3QsNGH0LXQudGB0YLQstCwMB4XDTExMDMyNDEyMjUxOVoXDTEyMDMyMzEyMjUxOVowggFhMQswCQYDVQQGEwJSVTEZMBcGA1UECAwQ0LMuINCc0L7RgdC60LLQsDEVMBMGA1UEBwwM0JzQvtGB0LrQstCwMU4wTAYDVQQKDEXQpNCV0JTQldCg0JDQm9Cs0J3QntCVINCa0JDQl9Cd0JDQp9CV0JnQodCi0JLQniAo0KHQldCg0JLQldCgINCh0K3QlCkxJjAkBgNVBCoMHdCu0LvQuNGPINCT0LXQvtGA0LPQuNC10LLQvdCwMRkwFwYDVQQEDBDQmtC+0L/Ri9C70L7QstCwMSgwJgYDVQQMDB/QndCw0YfQsNC70YzQvdC40Log0L7RgtC00LXQu9CwMWMwYQYDVQQDDFrQmtC+0L/Ri9C70L7QstCwINCu0LvQuNGPINCT0LXQvtGA0LPQuNC10LLQvdCwICjQotC10YXQvdC+0LvQvtCz0LjRh9C10YHQutC40Lkg0LrQu9GO0YcgMSkwYzAcBgYqhQMCAhMwEgYHKoUDAgIkAAYHKoUDAgIeAQNDAARAy9OoVph+gGTflOV66d6sHiDwdANt+vNhXwx0KnDK2sbSl041RBV0S578k3fZrdIhkacz1AeDKyQHKxzyWs46zqOCAWowggFmMAwGA1UdEwEB/wQCMAAwGAYDVR0gBBEwDzANBgsqhQMDPZ7XNgECAjBjBgNVHREEXDBaoBIGA1UEDKALEwkzMjQxMzUzNTeGATCgDgYIKoUDA4EDAQGgAhMAoBAGCiqFAwM9ntc2AQegAhMAoBAGCiqFAwM9ntc2AQWgAhMAoA0GByqFAwHgOQGgAhMAMA4GA1UdDwEB/wQEAwIE0DAhBgNVHSUEGjAYBggqhQMCAQYIBQYMKoUDAz2e1zYBBgMCMB8GA1UdIwQYMBaAFAe1ebcBOgyBvSWBc6saQOlYw/NNMGQGA1UdHwRdMFswLqAsoCqGKGh0dHA6Ly9kYy51Yy1zZnNmay5sb2NhbC9jcmwvY3VycmVudC5jcmwwKaAnoCWGI2h0dHA6Ly9jcmwucm9za2F6bmEucnUvY3JsL2xhc3QuY3JsMB0GA1UdDgQWBBQ6BizcjJIKBIGuyz7OCdySYtSE4zAIBgYqhQMCAgMDQQDRsa8Xu7mdTyKxrsVEr9YqGo2iG7Bcj1v4ttgcY+ylS3o9htFVhqu/TVXG90tTiFbR5f4j69/5y9YCkXaiGHdV</wsse:BinarySecurityToken><ds:Signature><ds:SignedInfo><ds:CanonicalizationMethod Algorithm=\"http://www.w3.org/2001/10/xml-exc-c14n#\"></ds:CanonicalizationMethod><ds:SignatureMethod Algorithm=\"http://www.w3.org/2001/04/xmldsig-more#gostr34102001-gostr3411\"></ds:SignatureMethod><ds:Reference URI=\"#body\"><ds:Transforms><ds:Transform Algorithm=\"http://www.w3.org/2001/10/xml-exc-c14n#\"></ds:Transform></ds:Transforms><ds:DigestMethod Algorithm=\"http://www.w3.org/2001/04/xmldsig-more#gostr3411\"></ds:DigestMethod><ds:DigestValue>j/09e90aqAaJd3iNVIXAx1ZveytZFCI+VVPEFwoC4j4=</ds:DigestValue></ds:Reference></ds:SignedInfo><ds:SignatureValue>jyAnuWfHRiYtCykHJmFIqD1iId7dkqpiDPyGvrmRkuA0DqmGJOQeiZXs3IigRqYSwD4CoxQQh8u2Dg7AFQcN8A==</ds:SignatureValue><ds:KeyInfo><wsse:SecurityTokenReference><wsse:Reference URI=\"#CertId\" ValueType=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-x509-token-profile-1.0#X509v3\"></wsse:Reference></wsse:SecurityTokenReference></ds:KeyInfo></ds:Signature></wsse:Security></S:Header><S:Body wsu:Id=\"body\"><ns9:UnifoTransferMsg xmlns:ns10=\"http://roskazna.ru/xsd/ExportQuittanceResponse\" xmlns:ns11=\"http://roskazna.ru/xsd/ExportIncomesResponse\" xmlns:ns12=\"http://roskazna.ru/xsd/ExportPaymentsResponse\" xmlns:ns13=\"http://roskazna.ru/xsd/PGU_ChargesResponse\" xmlns:ns14=\"http://roskazna.ru/xsd/PaymentInfo\" xmlns:ns15=\"http://roskazna.ru/xsd/Charge\" xmlns:ns2=\"http://www.w3.org/2000/09/xmldsig#\" xmlns:ns3=\"http://smev.gosuslugi.ru/rev110801\" xmlns:ns4=\"http://roskazna.ru/xsd/PGU_ImportRequest\" xmlns:ns5=\"http://rosrazna.ru/xsd/SmevUnifoService\" xmlns:ns6=\"http://roskazna.ru/xsd/Ticket\" xmlns:ns7=\"http://roskazna.ru/xsd/PGU_DataRequest\" xmlns:ns8=\"http://www.w3.org/2004/08/xop/include\" xmlns:ns9=\"http://roskazna.ru/SmevUnifoService/\"><ns3:Message><ns3:Sender><ns3:Code>0000000001</ns3:Code><ns3:Name>External Organization</ns3:Name></ns3:Sender><ns3:Recipient><ns3:Code>0000000000</ns3:Code><ns3:Name>UNIFO</ns3:Name></ns3:Recipient><ns3:Originator><ns3:Code>0000000001фыва</ns3:Code><ns3:Name>External Organization</ns3:Name></ns3:Originator><ns3:TypeCode>Request</ns3:TypeCode><ns3:Date>2011-09-08T11:26:40.137+04:00</ns3:Date></ns3:Message><ns3:MessageData><ns3:AppData><ns5:exportData><ns7:DataRequest kind=\"CHARGESTATUS\"><PostBlock><ID>055aa777-b988-4503-8ad9-e4eed14e7a06</ID><TimeStamp>2011-09-08T11:26:41.247+04:00</TimeStamp><SenderIdentifier>044525225</SenderIdentifier></PostBlock><SupplierBillIDs><SupplierBillID>18800000000000122936</SupplierBillID></SupplierBillIDs></ns7:DataRequest></ns5:exportData></ns3:AppData></ns3:MessageData></ns9:UnifoTransferMsg></S:Body></S:Envelope>";
    public static String Xml = "<S:Envelope xmlns:wsu=\"http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd\" xmlns:S=\"http://schemas.xmlsoap.org/soap/envelope/\"><S:Header></S:Header><S:Body wsu:Id=\"body\"></S:Body></S:Envelope>"; 
    public static String DocWithoutSignature = File.OpenText("DocWithoutSignature2.txt").ReadToEnd();
    public static String DocWithCorrectSignature = File.OpenText("DocWithCorrectSignature.txt").ReadToEnd();

    public static String CorrectHashExample = "XQ3+v+kTeA5PnydKtRcBFn0NH49n99z9ttqdngnTiAs=";

    //5d0dfebfe913780e4f9f274ab51701167d0d1f8f67f7dcfdb6da9d9e09d3880b
    public static String CorrectHashExampleHex = Convert.FromBase64String(CorrectHashExample).ByteArrayToString();
    public static String HexEmptyHash = "ce85b99cc46752fffee35cab9a7b0278abb4c2d2055cff685af4912c49490f8d";

    public static String SignMethod = "http://www.w3.org/2001/04/xmldsig-more#gostr34102001-gostr3411";
    public static String DigestMethod = "http://www.w3.org/2001/04/xmldsig-more#gostr3411";

    public static String CertificatePath = "C:\\Work\\certificate\\Ignatev Iurii Andreevich.cer";

    public void TestSigningElement()
    {
      
    }

    public void Run()
    {
      var testDoc = new SignedXmlDocument(DocWithoutSignature);
      var provider = new VipNetCrytoProvider();
      using(var output = File.CreateText("output.txt"))
      {
        provider.SignDocument(testDoc);
        Console.WriteLine(testDoc.Document);
        output.WriteLine(testDoc.ToString());
        var verify = new SignatureVerifier(testDoc.ToString(), provider);
      }
      var testCertificate = new TestCertificate();
      testCertificate.Test(testDoc);
      return;

      var doc = new XmlDocument();
      doc.LoadXml(DocWithoutSignature);
      new SignedXmlDoc(DocWithoutSignature);

    }

  }  

  public class SignatureVerifier
  {


    public SignatureVerifier(string xml, VipNetCrytoProvider provider)
    {
      XmlDocument doc = XDocument.Parse(xml).GetXmlDocument();
      var body = Canonicalizer.GetObject(doc, "#body");
      var bodyHash = provider.HashData(body);

      XmlNamespaceManager nsManager = new XmlNamespaceManager(doc.NameTable);
      nsManager.AddNamespace("ds", "http://www.w3.org/2000/09/xmldsig#");
      nsManager.AddNamespace("soapenv", "http://schemas.xmlsoap.org/soap/envelope/");
      nsManager.AddNamespace("wsse", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-secext-1.0.xsd");
      nsManager.AddNamespace("wsu", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd");

      var signatureValue = (doc.SelectSingleNode("//soapenv:Envelope/soapenv:Header/wsse:Security/ds:Signature/ds:SignatureValue", nsManager) as XmlElement).InnerText;
      var digestValue = (doc.SelectSingleNode("//soapenv:Envelope/soapenv:Header/wsse:Security/ds:Signature/ds:SignedInfo/ds:Reference/ds:DigestValue", nsManager) as XmlElement).InnerText;
      var isHashCorrect = bodyHash.Base64 == digestValue;
      //if (bodyHash.Base64 != doc.SelectSingleNode(""))
      {
        
      }
      var signedInfo = Canonicalizer.GetObject(doc, "#signedInfo");
    }    
  }

  public class VipNet : HMACSHA1
  {
    public VipNet()
    {

    }

    public override void Initialize()
    {
      //throw new NotImplementedException();
    }

    protected override void HashCore(byte[] array, int ibStart, int cbSize)
    {
      //throw new NotImplementedException();
      Console.WriteLine(Encoding.UTF8.GetChars(array));
    }

    protected override byte[] HashFinal()
    {
      //throw new NotImplementedException();
      return new byte[1];
    }
  }

  public class VipNetHashAlgorithm : HMACSHA1
  {
    public override void Initialize()
    {
      throw new NotImplementedException();
    }

    protected override void HashCore(byte[] array, int ibStart, int cbSize)
    {
      throw new NotImplementedException();
    }

    protected override byte[] HashFinal()
    {
      throw new NotImplementedException();
    }
  }

  public class SmevTransform : XmlDsigExcC14NTransform
  {    
    public override byte[] GetDigestedOutput(HashAlgorithm hash)
    {
      var output = new StreamReader((MemoryStream)base.GetOutput()).ReadToEnd();
      var gostHash = new VipNetCrytoProvider().HashData(output);
      //return base.GetDigestedOutput(hash);
      return gostHash.Bytes;
    }

    public override object GetOutput()
    {      
      var result = new StreamReader((MemoryStream)base.GetOutput()).ReadToEnd();      
      Console.WriteLine(result);
      var sha1 = SHA1.Create();
      var resultBytes = Encoding.UTF8.GetBytes(result);
      Console.WriteLine(Convert.ToBase64String(sha1.ComputeHash(Encoding.UTF8.GetBytes(result))));
      Console.WriteLine(Convert.ToBase64String(sha1.ComputeHash((Stream)base.GetOutput())));

      var hash = new VipNetCrytoProvider().HashData(result);
      Console.WriteLine(hash.Base64);
      Console.WriteLine(hash.Hex);

      //var input = File.OpenWrite("C:\\Users\\Yura\\Downloads\\rhash-1.2.10-win32\\input.txt");
      //input.Write(resultBytes,0, resultBytes.Length);
      //input.Close();

      return base.GetOutput();
    }
  }  

  public class SignedXmlObject : SignedXml
  {
    public override XmlElement GetIdElement(XmlDocument doc, string id)
    {
      XmlElement idElem = base.GetIdElement(doc, id);

      if (idElem == null)
      {
        XmlNamespaceManager nsManager = new XmlNamespaceManager(doc.NameTable);
        nsManager.AddNamespace("wsu", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd");


        idElem = doc.SelectSingleNode("//*[@wsu:Id=\"" + id + "\"]", nsManager) as XmlElement;
      }

      return idElem;
    }
    
  }

  public class SignedXml2 : SignedXml
  {
    protected override AsymmetricAlgorithm GetPublicKey()
    {
      return base.GetPublicKey();
    }

    public byte[] Sha1(String s)
    {
      var sha1 = SHA1.Create();
      return sha1.ComputeHash(Encoding.UTF8.GetBytes(s));

    }

    public SignedXml2(XmlDocument doc): base(doc)
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
      }


      
      var sha1_2 = Sha1(idElem.OuterXml);

      Console.WriteLine(idElem.OuterXml);
      Console.WriteLine(sha1_2.ByteArrayToString());
      Console.WriteLine(Convert.ToBase64String(sha1_2));


      return idElem;
    }
  }

  public class SignedXmlDoc
  {
    public SignedXmlDoc(string xml)
    {      
      var doc = new XmlDocument();

      

      doc.LoadXml(xml);
      SignedXml signedXml = new SignedXml2(doc);
      var reference = new Reference();

      var transform = new SmevTransform();

      reference.AddTransform(transform);     
      reference.Uri = "#body";
      

      signedXml.AddReference(reference);

      var vipnet = new VipNet();
      signedXml.KeyInfo = new KeyInfo();
      signedXml.SigningKey = (RSA)new RSACryptoServiceProvider();
      //vipnet.Key = signedXml.SigningKey;

        signedXml.ComputeSignature();

      Console.WriteLine( Convert.ToBase64String(reference.DigestValue) );
      Console.WriteLine(signedXml.GetXml().ToString());
      Console.WriteLine(reference.DigestValue);


      var body = new StreamReader((MemoryStream)transform.GetOutput()).ReadToEnd();  
      Console.WriteLine(body);

      Console.WriteLine(signedXml.GetXml().OuterXml);
    }
  }

}
