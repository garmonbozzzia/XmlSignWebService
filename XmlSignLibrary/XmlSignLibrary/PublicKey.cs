using System;
using MyExtentions;

namespace XmlSignLibrary
{
  public class PublicKey
  {
    public int Handle { get; private set; }
    public byte[] Bytes { get; set; }
    public String Hex { get { return Bytes.ByteArrayToString(); } }
    public String Base64 { get { return Convert.ToBase64String(Bytes); } }
    public PublicKey(int handle)
    {
      Handle = handle;
    }
  }
}