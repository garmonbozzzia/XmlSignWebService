/// @file
/// @brief Файл содержит определение методов класса, тестирующего подпись форматированного сообщения.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "sign-message.h"


SignMessage::SignMessage()
{

}


void SignMessage::Run()
{
     GetSettings()->LogStream() <<"\nSignMessage::Run()\n\n";
     GetSettings()->LogStream().flush();

     try
     {
          GetSettings()->LogStream() <<"Searching for certificate..\n";
          GetSettings()->LogStream().flush();

          //certificateSearch_.FindContext();

          GetMessage( message_ );

          MakeSignature();

          try{  WriteSignatureToFile(); } 
          catch( std::bad_exception& ){}

          VerifySignature();

          GetSettings()->LogStream() <<"Success\n";
          GetSettings()->LogStream().flush();
     }
     catch( csp_exception& e )
     {
          GetSettings()->LogStream() <<e.what();
     }
}

void SignMessage::MakeSignature()
{
     //Initialize Message's and MessageSize's arrays 
     const BYTE* MessageArray[] = { &message_[0] };
     DWORD MessageSizeArray[] = { message_.size() };

     CRYPT_SIGN_MESSAGE_PARA  SigParams = { 0 };

     //Initialize the SignParams data structure
     SigParams.cbSize = sizeof(CRYPT_SIGN_MESSAGE_PARA);
     SigParams.dwMsgEncodingType = MY_ENCODING_TYPE;
     SigParams.pSigningCert = certificateSearch_.GetContext();
     SigParams.HashAlgorithm.pszObjId = szOID_CPCSP_HASH_ALG;
     SigParams.HashAlgorithm.Parameters.cbData = NULL;
     SigParams.cMsgCert = 1;
     SigParams.rgpMsgCert = &certificateSearch_.GetContext();
     SigParams.cAuthAttr = 0;
     SigParams.dwInnerContentType = 0;
     SigParams.cMsgCrl = 0;
     SigParams.cUnauthAttr = 0;
     SigParams.dwFlags = 0;
     SigParams.pvHashAuxInfo = NULL;
     SigParams.rgAuthAttr = NULL;

     DWORD cbDetachedSignatureBlob = 0;

     GetSettings()->LogStream() <<"Getting size of detached signature blob..\n";
     GetSettings()->LogStream().flush();
     //Get the size of the output signature blob
     if(!CryptSignMessage(
          &SigParams,                //Signature parameters
          TRUE,                      //Detached
          1,                         //Number of messages
          MessageArray,              //Messages to be signed
          MessageSizeArray,          //Size of messages
          NULL,                      //Buffer for signature
          &cbDetachedSignatureBlob)) //Size of buffer
     {
          throw csp_exception( "CryptSignMessage", GetLastError() );
     }

     detachedSignature_.assign( cbDetachedSignatureBlob, 0 );

     GetSettings()->LogStream() <<"Signing message..\n";
     GetSettings()->LogStream().flush();
     //Sign message and get detached signature in signature blob
     if(!CryptSignMessage(
          &SigParams,               //Signature parameters
          TRUE,                     //Detached
          1,                        //Number of messages
          MessageArray,             //Messages to be signed
          MessageSizeArray,         //Size of messages
          &detachedSignature_[0],  //Buffer for signature
          &cbDetachedSignatureBlob))//Size of buffer
     {
          throw csp_exception( "CryptSignMessage", GetLastError() );
     }
}

void SignMessage::VerifySignature() const
{
     //Initialize Message's and MessageSize's arrays 
     const BYTE* MessageArray[] = { &message_[0] };
     DWORD MessageSizeArray[] = { message_.size() };

     CRYPT_VERIFY_MESSAGE_PARA VerifyParams = { 0 };

     //Initialize the VerifyParams data structure
     VerifyParams.cbSize = sizeof(CRYPT_VERIFY_MESSAGE_PARA);
     VerifyParams.dwMsgAndCertEncodingType = MY_ENCODING_TYPE;
     VerifyParams.hCryptProv = NULL;
     VerifyParams.pfnGetSignerCertificate = NULL;
     VerifyParams.pvGetArg = NULL;

     GetSettings()->LogStream() <<"Verifying detached message signature..\n";
     GetSettings()->LogStream().flush();
     //Verify detached message signature
     if(!CryptVerifyDetachedMessageSignature(
          &VerifyParams,           //Verify parameters.
          0,                       //Signer index.
          &detachedSignature_[0], //Pointer to signed BLOB.
          detachedSignature_.size(), //Size of signed BLOB.
          1,                       //Number of messages
          MessageArray,            //Messages to be signed
          MessageSizeArray,        //Size of buffer.
          NULL))                   //Pointer to signer certificate.
     {
          throw csp_exception( "CryptVerifyDetachedMessageSignature", GetLastError() );
     }
}

void SignMessage::WriteSignatureToFile() const
{
     tstring detachedSignatureFileName = GetSettings()->MessageFile(); 
     detachedSignatureFileName += _T( ".p7s" );

     GetSettings()->LogStream() <<"Writing detached message signature to file <";
     GetSettings()->LogStream() <<detachedSignatureFileName.c_str() <<">..\n";
     GetSettings()->LogStream().flush();

     std::ofstream detachedSignatureFile( detachedSignatureFileName.c_str() );
     if( detachedSignatureFile.bad() )
     {
          std::string errMessage = "Can't write to file: ";
          errMessage += detachedSignatureFileName;
          throw std::bad_exception( errMessage.c_str() );
     }
     detachedSignatureFile.write( (char*)&detachedSignature_[0], detachedSignature_.size() );
}
