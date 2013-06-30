using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using XmlSignLibrary;

namespace TestApp2
{
  class Program
  {
    static void Main(string[] args)
    {
      try
      {
        if (args.Length > 1)
        {
          var provider = new VipNetCrytoProvider(args[0], args[1]);
          var xml = "";
          using (var file = File.OpenText("input.txt"))
          {
            xml = file.ReadToEnd();
          }
          var doc = new SignedXmlDocument(xml);
          provider.SignDocument(doc);
          Console.WriteLine(doc.ToString());
        }
      }
      catch (Exception exc)
      {
        Console.WriteLine(exc.Message);
        Console.ReadKey();
        //throw;
      }
    }
  }
}
