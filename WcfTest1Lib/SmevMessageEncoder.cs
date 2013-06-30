using System;
using System.IO;
using System.ServiceModel.Channels;

namespace WcfTest1Lib
{
  class SmevMessageEncoder : MessageEncoder
  {
    public override Message ReadMessage(Stream stream, int maxSizeOfHeaders, string contentType)
    {
      throw new NotImplementedException();
    }

    public override Message ReadMessage(ArraySegment<byte> buffer, BufferManager bufferManager, string contentType)
    {
      throw new NotImplementedException();
    }

    public override void WriteMessage(Message message, Stream stream)
    {
      throw new NotImplementedException();
    }

    public override ArraySegment<byte> WriteMessage(Message message, int maxMessageSize, BufferManager bufferManager, int messageOffset)
    {
      var bytes = new byte[0];
      return  new ArraySegment<byte>(bytes);
    }

    public override string ContentType
    {
      get { throw new NotImplementedException(); }
    }

    public override string MediaType
    {
      get { throw new NotImplementedException(); }
    }

    public override MessageVersion MessageVersion
    {
      get { throw new NotImplementedException(); }
    }
  }
}