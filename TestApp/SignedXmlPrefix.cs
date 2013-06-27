using System;
using System.Reflection;
using System.Security.Cryptography;
using System.Security.Cryptography.Xml;
using System.Xml;

namespace TestApp
{
  class SignedXmlPrefix : SignedXml
  {
    public SignedXmlPrefix(XmlDocument document)
      : base(document)
    { }

    public SignedXmlPrefix(XmlElement element)
      : base(element)
    { }

    public SignedXmlPrefix()
      : base()
    { }

    public void ComputeSignature(string prefix)
    {
      this.BuildDigestedReferences();
      SignatureDescription description = CryptoConfig.CreateFromName(this.SignedInfo.SignatureMethod) as SignatureDescription;

      HashAlgorithm hash = description.CreateDigest();

      GetDigest(hash, prefix);
      this.m_signature.SignatureValue = description.CreateFormatter(this.SigningKey).CreateSignature(hash);

    }
    private void BuildDigestedReferences()
    {
      Type t = typeof(SignedXml);
      MethodInfo m = t.GetMethod("BuildDigestedReferences", BindingFlags.NonPublic | BindingFlags.Instance);
      m.Invoke(this, new object[] { });
    }
    private byte[] GetDigest(HashAlgorithm hash, string prefix)
    {
      XmlDocument document = new XmlDocument();
      document.PreserveWhitespace = true;

      XmlElement e = this.SignedInfo.GetXml();
      document.AppendChild(document.ImportNode(e, true));

      Transform canonicalizationMethodObject = this.SignedInfo.CanonicalizationMethodObject;
      SetPrefix(prefix, document);

      canonicalizationMethodObject.LoadInput(document);
      return canonicalizationMethodObject.GetDigestedOutput(hash);
    }

    private void SetPrefix(string prefix, XmlNode node)
    {
      foreach (XmlNode n in node.ChildNodes)
        SetPrefix(prefix, n);
      node.Prefix = prefix;
    }


    public XmlElement GetXml(string prefix)
    {
      XmlElement e = this.GetXml();
      SetPrefix(prefix, e);
      return e;
    }


  }
}