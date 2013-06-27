namespace XmlSignLibrary
{
  public class KeyPair
  {
    public int Handle { get; private set; }
    
    public KeyPair(int handle)
    {
      Handle = handle;
    }
  }
}