using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.ServiceModel.Description;
using System.Text;
using WcfTest1Lib;

namespace WcfServiceHost
{
  class Program
  {
    static void Main(string[] args)
    {
      var uri = new Uri("http://localhost:8080/XmlSignServiceHost");
      using (ServiceHost host = new ServiceHost(typeof(XmlSignService), uri))
      {
        // Enable metadata publishing.
        ServiceMetadataBehavior smb = new ServiceMetadataBehavior();
        smb.HttpGetEnabled = true;        
        smb.MetadataExporter.PolicyVersion = PolicyVersion.Policy15;
        host.Description.Behaviors.Add(smb);

        // Open the ServiceHost to start listening for messages. Since
        // no endpoints are explicitly configured, the runtime will create
        // one endpoint per base address for each service contract implemented
        // by the service.
        //host.AddServiceEndpoint( typeof(XmlSignService), portsharingBinding, "net.tcp://localhost/MyService");


        host.Open();

        Console.WriteLine("The service is ready at {0}", uri);
        Console.WriteLine("Press <Enter> to stop the service.");
        Console.ReadLine();

        // Close the ServiceHost.
        host.Close();
      }
    }
  }
}
