using System;
using MyExtentions;
using System.Linq;

namespace XmlSignLibrary
{
  public class Signature
  {
    public Hash SignedHash { get; set; }
    public PublicKey Key { get; set; }
    public byte[] Bytes { get; set; }
    public String Base64
    {
      get { return Convert.ToBase64String(Bytes.Reverse().ToArray()); }
      set { Bytes = Convert.FromBase64String(value).Reverse().ToArray(); }
    }
  }
}