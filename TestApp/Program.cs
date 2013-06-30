using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestApp
{
  class Program
  {
    static void Main(string[] args)
    {
      new ServiceTest();
      var testXml = new TestXml();
      testXml.Run();
    }
  }
}
