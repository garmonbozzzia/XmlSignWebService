using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;
using System.Xml;
using System.Xml.Linq;
using XmlSignLibrary;

namespace WcfTest1Lib
{
  [DataContract]
  public class RequestCData
  {
    [DataMember]
    public CDataWrapper Xml { get; set; }
  }



  [MessageContract(WrapperName = "signXML", WrapperNamespace = "http://systemprojects.ru/")]
  public class RequestMessage
  {
    [MessageBodyMember(Name = "request", Namespace = "http://systemprojects.ru/")]
    public CDataWrapper Xml { get; set; }
  }



  [MessageContract(WrapperName = "signXML", WrapperNamespace = "http://systemprojects.ru/")]
  public class ResponseMessage
  {
    [MessageBodyMember(Name = "response", Namespace = "http://systemprojects.ru/")]
    public CDataWrapper Xml { get; set; }

    [MessageBodyMember(Name = "error", Namespace = "http://systemprojects.ru/")]
    public String Error { get; set; }
  }

  public class XmlSignService : IXmlSignService
  {
    public VipNetCrytoProvider CrytoProvider { get; set; }
    public String ErrorMessage { get; set; }

    public XmlSignService()
    {
      ErrorMessage = "";
      try
      {
        var configPath = AppDomain.CurrentDomain.BaseDirectory + "config.txt";
        using (var file = File.OpenText(configPath))
        {
          CrytoProvider = new VipNetCrytoProvider(containerPath:file.ReadLine(), password:file.ReadLine());          
        }
      }
      catch (Exception exception)
      {
        ErrorMessage = exception.Message + "\n" + exception.StackTrace;
      }
    }

    //public string SignXml(string xml)
    //{
    //  return xml;
    //}

    //public CDataWrapper Sign(CDataWrapper request)
    //{ 
    //  return new CDataWrapper() { Value = request.Value };
    //}

    public ResponseMessage SignXml(RequestMessage xml)
    {
      try
      {
        var doc = new SignedXmlDocument(xml.Xml.Value);
        CrytoProvider.SignDocument(doc);
        return new ResponseMessage(){Xml = doc.ToString()};
      }
      catch (Exception exception)
      {
        ErrorMessage += exception.Message + "\n" + exception.StackTrace;
      }
      return new ResponseMessage{ Xml = null, Error = ErrorMessage};
    }

    //public RequestCData SignData(RequestCData reqest)
    //{
    //  return new RequestCData{Xml = reqest.Xml};
    //}
  }

}
