using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Xml.Linq;
using XmlSignLibrary;

namespace WcfXmlSigningService
{
  // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in code, svc and config file together.
  public class Service1 : IService1
  {
    public VipNetCrytoProvider CrytoProvider { get; set; }
    private String ConfigPath { get; set; } 

    public Service1()
    {
      ConfigPath = "C:\\Work\\XmlSign\\trunk\\WcfXmlSigningService\\bin\\Service.cfg";
      using(var file = File.OpenText(ConfigPath))
      {
        var containerPath = file.ReadLine();
        var password = file.ReadLine();
        CrytoProvider = new VipNetCrytoProvider(containerPath, password);
      }
    }

    public string SignDocument(string xml)
    {
      var doc = new SignedXmlDocument(xml);
      CrytoProvider.SignDocument(doc);
      var cdata = new XCData(doc.ToString());
      return cdata.ToString();
    }

    public CompositeType GetDataUsingDataContract(CompositeType composite)
    {
      if (composite == null)
      {
        throw new ArgumentNullException("composite");
      }
      if (composite.BoolValue)
      {
        composite.StringValue += "Suffix";
      }
      return composite;
    }
  }
}
