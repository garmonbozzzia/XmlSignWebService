using System;
using System.Runtime.InteropServices;
using System.Text;
using XmlSignLibrary;

namespace TestApp
{
  public class VipNetCrytoProvider
  {
    public int ProviderHandle { get; private set; }
    public int UserKeyHandle { get; private set; }
    public int HashHandle { get; private set; }
    public void OpenContainer()
    {
      var hProv = new IntPtr();

      var result = VipNetImport.CryptAcquireContextW(
        ref hProv,
        "C:\\Work\\certificate\\le-c60c3405-7918-479e-a4fe-e941118cc83e",
        "Infotecs Cryptographic Service Provider", 2, 64);
      Console.WriteLine("CryptAcquireContextW - {0}", result);

      ProviderHandle = hProv.ToInt32();
    }
    public void SetPassword(string password)
    {
      byte[] pass = Encoding.ASCII.GetBytes(password);
      var result = VipNetImport.CryptSetProvParam(ProviderHandle, 33, pass, 0);
      Console.WriteLine("CryptSetProvParam - {0}", result);
    }
    public void OpenKey()
    { 
      IntPtr hUserKey = new IntPtr();
      var result = VipNetImport.CryptGetUserKey(ProviderHandle, 2, ref hUserKey);
      Console.WriteLine("CryptGetUserKey - {0}", result);
      UserKeyHandle = hUserKey.ToInt32();
    }
    public void CreateHashHandle()
    {

      IntPtr hHash = new IntPtr();
      var result = VipNetImport.CryptCreateHash(ProviderHandle, 32798, 0, 0, ref hHash);
      Console.WriteLine("CryptCreateHash - {0}", result);
      HashHandle = hHash.ToInt32();
    }
    public string HashData(string message)
    {
      var result = VipNetImport.CryptHashData(HashHandle, Encoding.UTF8.GetBytes(message), message.Length, 0);      ;
      IntPtr pSize = new IntPtr();
      IntPtr pData = IntPtr.Zero;      
      result = VipNetImport.CryptGetHashParam(HashHandle, 0x0002, pData, ref pSize, 0);
      pData = Marshal.AllocHGlobal(pSize.ToInt32());
      result = VipNetImport.CryptGetHashParam(HashHandle, 0x0002, pData, ref pSize, 0);
      var hashValue = new byte[pSize.ToInt32()];
      Marshal.Copy(pData, hashValue, 0, hashValue.Length);
      Console.WriteLine("{0}, {0:X}",Marshal.GetLastWin32Error());
      Console.WriteLine("CryptHashData - {0}", result);
      var base64Hash = Convert.ToBase64String(hashValue);
      Console.WriteLine("Hash:{0}",base64Hash);
      return base64Hash;
    }
    public string HashSigning()
    {
      var pbSignature = IntPtr.Zero;
      var pdwLength = new IntPtr();
      var result = VipNetImport.CryptSignHash(HashHandle, 2, null, 0, pbSignature, ref pdwLength);

      var signature = new byte[pdwLength.ToInt32()];
      var size = pdwLength.ToInt32() * Marshal.SizeOf(signature[0]);
      pbSignature = Marshal.AllocHGlobal(size);

      Console.WriteLine("SignatureLength = {0}", pdwLength.ToInt32());
      result = VipNetImport.CryptSignHash(HashHandle, 2, null, 0, pbSignature, ref pdwLength);
      Console.WriteLine("CryptSignHash - {0}", result);
      Console.WriteLine("!!{0:x} = {0}!!", Marshal.GetLastWin32Error());

      Marshal.Copy(pbSignature, signature, 0, signature.Length);
      var base64Signing = Convert.ToBase64String(signature);
      Console.WriteLine("Signature: {0}", base64Signing);
      return base64Signing;
    }
    public string GetCertificate()
    {
      IntPtr pSize = new IntPtr();
      IntPtr pData = IntPtr.Zero;
      var result = VipNetImport.CryptGetKeyParam(UserKeyHandle, 26, pData, ref pSize, 0);
      pData = Marshal.AllocHGlobal(pSize.ToInt32());
      result = VipNetImport.CryptGetKeyParam(UserKeyHandle, 26, pData, ref pSize, 0);      
      var publicKeyValue = new byte[pSize.ToInt32()];
      Marshal.Copy(pData, publicKeyValue, 0, publicKeyValue.Length);
      Console.WriteLine("{0}, {0:X}", Marshal.GetLastWin32Error());
      Console.WriteLine("CryptGetKeyParam - {0}", result);
      var base64PublicKey = Convert.ToBase64String(publicKeyValue);
      Console.WriteLine("Certificate:{0}", base64PublicKey);
      return base64PublicKey;
    }
    public CryptoData SignMessage(string message)
    {
      var result = new CryptoData();
      result.Certificate = GetCertificate();
      result.Hash = HashData(message);      
      result.Sign = HashSigning();
      return result;
    }

    public VipNetCrytoProvider()
    {
      Init();
    }

    public void Init()
    {
      OpenContainer();
      SetPassword("Asdf1234");
      OpenKey();
      CreateHashHandle();
    }
  }
}