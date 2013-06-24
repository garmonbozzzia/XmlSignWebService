using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;

namespace Extensions
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
      var result = new byte[hexText.Length/2];
      for (int i = 0; i < hexText.Length; i += 2)
      {
        var symbol = (byte)Int32.Parse(hexText.Substring(i, 2), NumberStyles.HexNumber);
        result[i/2] = symbol;
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
        c[i] = (byte)(a[i] ^ b[i]);
      }
      return c;
    }

    public static string ByteArrayToString(this byte[] ba)
    {
      StringBuilder hex = new StringBuilder(ba.Length * 2);
      foreach (byte b in ba)
        hex.AppendFormat("{0:x2}", b);
      return hex.ToString();
    }
  }
}