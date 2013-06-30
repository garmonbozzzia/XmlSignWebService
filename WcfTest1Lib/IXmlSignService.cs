using System.ServiceModel;

namespace WcfTest1Lib
{
  [ServiceContract(Namespace = "http://systemprojects.ru/")]
  public interface IXmlSignService
  {
    //[OperationContract(Name = "signXml")]
    //string SignXml(string xml);

    //[OperationContract]
    //CDataWrapper Sign(CDataWrapper request);

    [OperationContract()]
    ResponseMessage SignXml(RequestMessage xml);

    //[OperationContract]
    //RequestCData SignData(RequestCData reqest);
  }
}