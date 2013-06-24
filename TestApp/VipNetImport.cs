using System;
using System.Runtime.InteropServices;

namespace TestApp
{
  public class VipNetImport
  {
    [DllImport("advapi32.dll", CharSet=CharSet.Auto, SetLastError=true)]
    public static extern bool CryptAcquireContextW(
      ref IntPtr phProv,
      [MarshalAs(UnmanagedType.LPWStr)] string pszContainer,
      [MarshalAs(UnmanagedType.LPWStr)] string pszProvider,
      Int32 dwProvType,
      Int32 dwFlags
    );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptSetProvParam(
      int hProv,
      int dwParam,
      [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] byte[] pbData,
      Int32 dwFlags
    );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptGetUserKey(
      int hProv,
      int dwKeySpec,
      ref IntPtr phUserKey
    );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptGetKeyParam(
      int hKey,
      int dwParam,
      IntPtr pbData,
      ref IntPtr dwDataLen,
      int dwFlags
    );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptCreateHash(
      int hProv,
      int algId,
      int hKey,
      int dwFlags,
      ref IntPtr phHash
    );   

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptHashData (
      int hHash,
      [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] byte[] pbData,
      int dwDataLen,
      int dwFlags
    );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptGetHashParam(
      int hHash,
      int dwParam,
      IntPtr pbData,
      ref IntPtr dwDataLen,
      int dwFlags
    );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptSetHashParam(
      int hHash,
      int dwParam,
      [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] byte[] pbData,
      int dwFlags
    );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptDuplicateHash(
      int hHash,
      IntPtr pdwReserved,
      int dwFlags,
      ref IntPtr phHash
    );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptDestroyHash( int hHash );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptSignHash(
      int hHash,
      int dwKeySpec,
      [MarshalAs(UnmanagedType.LPWStr)] string sDescription,
      int dwFlags,
      IntPtr pbSignature,
      ref IntPtr pdwSigLen
    );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptVerifySignature(
      int hHash,
      [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] byte[] pbSignature,
      int dwSigLen,
      int hPubKey,
      [MarshalAs(UnmanagedType.LPWStr)] string sDescription,
      int dwFlags
    );

    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptExportKey(
      int hKey,
      int hExpKey,
      int dwBlobType,
      int dwFlags,
      [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] byte[] pbData,
      ref IntPtr pdwDataLen
    );


    [DllImport("advapi32.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern bool CryptImportKey(
      int hProv,
      [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 1)] byte[] pbData,
      int dwDataLen,
      int hPubKey,
      int dwFlags,
      ref IntPtr phKey
    );

  }
}