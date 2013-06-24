using System;
using MyExtentions;

namespace XmlSignLibrary
{
  public class Hash
  {
    public int Handle { get; private set; }
    public byte[] Bytes { get; set; }
    public string Base64
    {
      get { return Convert.ToBase64String(Bytes); }
    }
    public string Hex
    {
      get { return Bytes.ByteArrayToString(); }
    }

    public Hash(int handle)
    {
      Handle = handle;
    }
  }
}