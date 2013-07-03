using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Xml.Linq;
using System.Linq;
using MyExtentions;

namespace XmlSignLibrary
{
  public class PrivateKey
  {
    
  }

  public class VipNetCrytoProvider
  {
    private int ProviderHandle { get; set; }
    private KeyPair KeyPair { get; set; }
    
    //private int HashHandle { get; set; }
    public const string ProviderName = "Infotecs Cryptographic Service Provider";
    public string ContainerPath { get; set; }
    public string Password { get; set; }

    void CheckCapicomResult(string errorMessage, bool result)
    {
      if (!result)
      {
        throw new Exception(errorMessage + "- Error:" + Marshal.GetLastWin32Error());
      }
    }

    private void OpenContainer()
    {
      var hProv = new IntPtr();

      var result = VipNetImport.CryptAcquireContextW(
        ref hProv,
        ContainerPath,
        ProviderName, 2, 64);
      Console.WriteLine("CryptAcquireContextW - {0}", result);
      CheckCapicomResult("OpenContainer" + ContainerPath, result);
      ProviderHandle = hProv.ToInt32();
    }

    private void SetPassword(string password)
    {
      byte[] pass = Encoding.ASCII.GetBytes(password);
      var result = VipNetImport.CryptSetProvParam(ProviderHandle, 33, pass, 0);
      CheckCapicomResult("SetPassword" + password, result);
      Console.WriteLine("CryptSetProvParam - {0}", result);
    }

    private void OpenKey()
    { 
      IntPtr hUserKey = new IntPtr();
      var result = VipNetImport.CryptGetUserKey(ProviderHandle, 2, ref hUserKey);
      CheckCapicomResult("OpenKey", result);
      Console.WriteLine("CryptGetUserKey - {0}", result);
      KeyPair = new KeyPair(hUserKey.ToInt32());
    }

    public int CreateHashHandle()
    {

      IntPtr hHash = new IntPtr();
      var result = VipNetImport.CryptCreateHash(ProviderHandle, 32798, 0, 0, ref hHash);
      CheckCapicomResult("CreateHashHandle", result);
      Console.WriteLine("CryptCreateHash - {0}", result);      
      return hHash.ToInt32();
    }

    public Hash HashData(string message)
    {
      var hash = new Hash(CreateHashHandle());

      var messageBytes = Encoding.UTF8.GetBytes(message);
      var result = VipNetImport.CryptHashData(hash.Handle, messageBytes, messageBytes.Length, 0);
      //if (message.Length != messageBytes.Length) 
        //throw new Exception(messageBytes.Length + "!=" + messageBytes.Length);
      
      IntPtr pSize = new IntPtr();
      IntPtr pData = IntPtr.Zero;
      result = VipNetImport.CryptGetHashParam(hash.Handle, 0x0002, pData, ref pSize, 0);
      pData = Marshal.AllocHGlobal(pSize.ToInt32());
      result = VipNetImport.CryptGetHashParam(hash.Handle, 0x0002, pData, ref pSize, 0);
      CheckCapicomResult("HashData" + message, result);

      hash.Bytes = new byte[pSize.ToInt32()];
      Marshal.Copy(pData, hash.Bytes, 0, hash.Bytes.Length);
      Console.WriteLine("{0}, {0:X}",Marshal.GetLastWin32Error());
      Console.WriteLine("CryptHashData - {0}", result);      
      Console.WriteLine("Hash:{0}",hash.Base64);
      return hash;
    }

    public Signature SigningHash(Hash hash)
    {
      var signature = new Signature(){SignedHash = hash};
      var pbSignature = IntPtr.Zero;
      var pdwLength = new IntPtr();
      var result = VipNetImport.CryptSignHash(hash.Handle, 2, null, 0, pbSignature, ref pdwLength);

      signature.Bytes = new byte[pdwLength.ToInt32()];
      if (pdwLength.ToInt32()==0)
      {
        CheckCapicomResult("SigningHash" + "length == 0", result);
      }
      var size = pdwLength.ToInt32() * Marshal.SizeOf(signature.Bytes[0]);
      pbSignature = Marshal.AllocHGlobal(size);

      Console.WriteLine("SignatureLength = {0}", pdwLength.ToInt32());
      result = VipNetImport.CryptSignHash(hash.Handle, 2, null, 0, pbSignature, ref pdwLength);
      Console.WriteLine("CryptSignHash - {0}", result);
      Console.WriteLine("!!{0:x} = {0}!!", Marshal.GetLastWin32Error());

      Marshal.Copy(pbSignature, signature.Bytes, 0, signature.Bytes.Length);
      Console.WriteLine("Signature: {0}", signature.Base64);

      //y2XdxwhHeZ0nReO2zFSJdBbObXcra+w0tK/dCukZUGF0kjsWq/+AbO4S4/PL7LX9C8fUu9D0WsZStxRjvSmApw==
      signature.Key = ImportPublicKey();

      var privateKey = Convert.ToBase64String(ExportKeyData(VipNetConst.PrivateKeyBlob));
      //Private Key:"BxCKACMuAABJVENTTAAAAK0AAAAwgaoCAQMwbgIBAgICLiOgHjAcBgYqhQMCAhMwEgYHKoUDAgIjAQYHKoUDAgIeAaESBBCg4PLNAAAAAMD8/1W+Xs4BpiQwIoAPMjAxMzA2MDExMTUxMjFagQ8yMDE0MDYwMTExNTEyMVqnCwMJAIYzJMGalnL1MDUCAgQAAgJgLqcjAyEAkvgi9y7r1tivJcf6ZDJ56LEzqJZBmlAJ2yb/qyqJu56qBgIEgAAAAEwAAABvtgPbhcLo2eXmUKoVaZjWUJthcx81bqC1hg5hbJ/tnOQ6tho60A1FC2vU7/wvCqTBeQJwpCA7n0qAfXSiU2ncIG96jDkL4PWmx4a+"
      
      //Public Key: "BiAAACMuAABNQUcxAAIAADASBgcqhQMCAiMBBgcqhQMCAh4BhjMkwZqWcvXgwPu0J5QiHE6G+2NnDNYmazapb5QCt0YCCLE/UyIysDJMKQZt1bJrdDXQ5AmeTncWkatgBdbJlg=="
      //"06200000232e00004d41473100020000301206072a85030202230106072a850302021e01863324c19a9672f5e0c0fbb42794221c4e86fb63670cd6266b36a96f9402b7460208b13f532232b0324c29066dd5b26b7435d0e4099e4e771691ab6005d6c996"
      //Signature:  "QtiWoUjMcdjlNOD3SL9tEWb6bG+oU8yXygrGMn4Qc7aKELF9BUKfSJNFyOf/5f90A5FLs9b+IKOIylRODMM4zg=="
      if (!VerifySignature(signature)) throw new Exception("VerifySignature not pass");

      return signature;
    }

    private byte[] ExportKeyData(int keyType)
    {
      var pdwDataLen = new IntPtr();
      var result = VipNetImport.CryptExportKey(KeyPair.Handle, 0, keyType, 0, null, ref pdwDataLen);
      Console.Write("{0:X}", Marshal.GetLastWin32Error());
      var data = new byte[pdwDataLen.ToInt32()];
      result = VipNetImport.CryptExportKey(KeyPair.Handle, 0, keyType, 0, data, ref pdwDataLen);
      return data;
    }

    public PublicKey ImportPublicKey(byte[] keyData)
    {
      var pPublicKey = new IntPtr();
      var result = VipNetImport.CryptImportKey(ProviderHandle, keyData, keyData.Length, 0, 0, ref pPublicKey);
      return new PublicKey(pPublicKey.ToInt32()) { Bytes = keyData };
    }

    public PublicKey ImportPublicKey()
    {
      var data = ExportKeyData(VipNetConst.PublicKeyBlob);
      return ImportPublicKey(data);
    }

    public bool VerifySignature(Signature signature)
    {
      return VipNetImport.CryptVerifySignature(signature.SignedHash.Handle, signature.Bytes, signature.Bytes.Length, signature.Key.Handle, null, 0);
    }

    private string GetCertificate()
    {
      IntPtr pSize = new IntPtr();
      IntPtr pData = IntPtr.Zero;
      var result = VipNetImport.CryptGetKeyParam(KeyPair.Handle, 26, pData, ref pSize, 0);
      pData = Marshal.AllocHGlobal(pSize.ToInt32());
      result = VipNetImport.CryptGetKeyParam(KeyPair.Handle, 26, pData, ref pSize, 0);      
      var publicKeyValue = new byte[pSize.ToInt32()];
      Marshal.Copy(pData, publicKeyValue, 0, publicKeyValue.Length);
      Console.WriteLine("{0}, {0:X}", Marshal.GetLastWin32Error());
      Console.WriteLine("CryptGetKeyParam - {0}", result);
      var base64PublicKey = Convert.ToBase64String(publicKeyValue);
      Console.WriteLine("Certificate:{0}", base64PublicKey);
      return base64PublicKey;
    }

    public void SignDocument(SignedXmlDocument document)
    {
      //String testBody = "<soapenv:Body wsu:Id=\"body\"><typ:ChangeOrderStatusV243Request><smev:Message><smev:Sender><smev:Code>EPGU_SYS_1</smev:Code><smev:Name>ЕПГУ</smev:Name></smev:Sender><smev:Recipient><smev:Code>MINPROM_SYS_1</smev:Code><smev:Name>Минпромторг России</smev:Name></smev:Recipient><smev:Originator><smev:Code>EPGU_SYS_1</smev:Code><smev:Name>ЕПГУ</smev:Name></smev:Originator><smev:TypeCode>GSRV</smev:TypeCode><smev:Status>REQUEST</smev:Status><smev:Date>2012-06-05T17:14:19+04:00</smev:Date><smev:ExchangeType>1</smev:ExchangeType><smev:ServiceCode>10001014881</smev:ServiceCode></smev:Message><smev:MessageData><smev:AppData wsu:Id=\"AppData\"><chan:changeOrderInfo><chan:serviceInfo><chan:serviceOrgCode>MPT0</chan:serviceOrgCode><chan:eServiceId/><chan:reestrId>10001014881</chan:reestrId></chan:serviceInfo><chan:orderId><chan:pguId>7d6476ac-a728-4863-804e-a5789d29c630</chan:pguId><chan:orgId/></chan:orderId><chan:statusCode><chan:orgCode/><chan:techCode>2</chan:techCode></chan:statusCode><chan:comment>Заявление отправлено в ведомство</chan:comment><chan:cancelAllowed>false</chan:cancelAllowed><chan:authToken>TEST_TOKEN_1</chan:authToken></chan:changeOrderInfo><smev:error><smev:errorCode/><smev:errorMessage/></smev:error></smev:AppData><smev:AppDocument><smev:RequestCode>req_7d6476ac-a728-4863-804e-a5789d29c630</smev:RequestCode><smev:BinaryData>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</smev:BinaryData></smev:AppDocument></smev:MessageData></typ:ChangeOrderStatusV243Request></soapenv:Body>";
      document.CertificateValue.Value = GetCertificate();

      //var objectToHash = SignedXmlDocument.Canonicalize(document.Body);
      var body = Canonicalizer.GetObject( document.Document.GetXmlDocument(), "#body");
      var hashBody = HashData(body);
      document.DigestValue.Value = hashBody.Base64;
      

      //var signedInfo = SignedXmlDocument.Canonicalize(document.SignedInfo);
      //var signedInfo = Canonicalizer.GetObject2(document.Document.GetXmlDocument(), "#signedInfo");
      var signedInfo = Canonicalizer.GetObject(document.Document.GetXmlDocument(), "#SignedInfo");      
      var signature = SigningHash(HashData(signedInfo));
      document.SignedValue.Value = signature.Base64;

      Console.WriteLine(document);

      //if (!Verify(document.ToString().Replace("</soapenv:body>", " </soapenv:body>"), body, signedInfo)) throw new Exception("Not Correct Final Xml");
      //if (!Verify(document.ToString(), body, signedInfo)) throw new Exception("Not Correct Final Xml");



      //document.Signing( SignMessage( testBody ) );
      //document.Signing( SignMessage( document.Body.ToString() ) );
      //Console.WriteLine(testBody);
    }

    public bool Verify(string xml, string body, string signedInfo)
    {
      var document = new SignedXmlDocument(xml).Document.GetXmlDocument();
      var correctBody = Canonicalizer.GetObject(document, "#body") == body;
      var correctSignedInfo = Canonicalizer.GetObject(document, "#signedInfo") == signedInfo;

      return correctBody && correctSignedInfo;
    }

    public static VipNetCrytoProvider GetInstance()
    {
      using (var config = File.OpenText("Config.txt"))
      {
        var containerPath = config.ReadLine();
        var password = config.ReadLine();
        return new VipNetCrytoProvider(containerPath, password);
      }
    }
    
    public VipNetCrytoProvider()
    {
      ContainerPath = "C:\\Work\\certificate\\le-c60c3405-7918-479e-a4fe-e941118cc83e";
      Password = "Asdf1234";
      Init();
    }

    public VipNetCrytoProvider(string containerPath, string password)
    {
      ContainerPath = containerPath;
      Password = password;
      Init();
    }

    private void Init()
    {
      OpenContainer();
      SetPassword(Password);
      OpenKey();
      CreateHashHandle();
    }
  }


}