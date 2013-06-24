/// @file
/// @brief Файл содержит определения идентификаторов алгоритмов, необходимых для работы с криптопровайдером.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef _ITC_IMPORTITCCSP_H_
#define _ITC_IMPORTITCCSP_H_

#if !defined(__unix__) && !defined(__KERNEL__)
#include <wincrypt.h>
#endif // __unix__

#ifdef __unix__
// from wincrypt.h
#define CRYPT_MODE_CBC          1       // Cipher block chaining
#define CRYPT_MODE_ECB          2       // Electronic code book
#define CRYPT_MODE_OFB          3       // Output feedback mode
#define CRYPT_MODE_CFB          4       // Cipher feedback mode
#define CRYPT_MODE_CTS          5       // Ciphertext stealing mode

#define NTE_BUFFER_TOO_SMALL 0x80090028

#endif // __unix__


//Коды алгоритмов
#define ALG_TYPE_GR3410                         (7 << 9)
#define ALG_SID_SIGN_CPCSP    30
#define ALG_SID_HASH_CPCSP    30
#define ALG_SID_DH_CPCSP      30
#define ALG_SID_ENCRYPT_CPCSP 30

#define ALG_SID_G28147_MAC	31
#define ALG_SID_PRO_EXP		31
#define ALG_SID_DH_EX_EPHEM	31
#define ALG_SID_SIMPLE_EXP    32 
#define ALG_SID_TLS1_MASTER_HASH 32

#define ALG_SID_SIGN_ELLIP    35
#define ALG_SID_DH_EL         36
#define ALG_SID_DH_EL_EPHEM	37

#define ALG_SIG_ITCS_EXPORT   46



#define UNKNOWN_ALG_ID   0xFFFF
#define ALG_SID_SHB      0x01FF

//Совместимость с "КриптоПРО"
#define CPCSP_HASH_ID    (ALG_CLASS_HASH | ALG_SID_HASH_CPCSP )
#define CPCSP_IMITO_ID   (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_G28147_MAC)

#define CPCSP_ENCRYPT_ID (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_ENCRYPT_CPCSP)
#define CPCSP_SIGN_ID    (ALG_CLASS_SIGNATURE | ALG_TYPE_GR3410 | ALG_SID_SIGN_CPCSP)
#define ELLIP_SIGN_ID    (ALG_CLASS_SIGNATURE | ALG_TYPE_GR3410 | ALG_SID_SIGN_ELLIP)
//#define CPCSP_DH_ID      (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH |  ALG_SID_SIGN_CPCSP)
#define CPCSP_DH_EL_ID   (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH |  ALG_SID_DH_EL)

//для совместимости с Крипто-про мы при экспорте подменяем CPCSP_DH_EL_ID на ELLIP_SIGN_ID
//если задан этот флаг, то подмена не происходит.
#define NO_CHANGE_DH_EL_ID_FLAG    0x10000000
///////////////////////////////////////////////////////////////////////////////////////
//Алгоритм экспорта ключа шифрования для помещения в конверт (транспорт ключа)
//значение по умолчанию для использования в почтовых клиентах MS.
#define CALG_PRO_EXPORT (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_PRO_EXP)
//Определяет алгоритм экспорта ключа, зашифрованного в режиме простой замены без дополнительных параметров
//применяется для хранения и конвертации ключей
#define CALG_SIMPLE_EXPORT (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_SIMPLE_EXP)

//Определяет алгоритм экспорта ключа, зашифрованного в режиме CFB c дополнительной информацией,
//Доп. информация подлежит имитозащите вместе с ключем.
#define CALG_ITCS_EXPORT (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SIG_ITCS_EXPORT)

#define CALG_TLS1_MASTER_HASH   (ALG_CLASS_HASH | ALG_TYPE_ANY | ALG_SID_TLS1_MASTER_HASH )
#define CALG_TLS1_MAC_KEY (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_SECURECHANNEL | ALG_SID_SCHANNEL_MAC_KEY)
#define CALG_TLS1_ENC_KEY (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_SECURECHANNEL | ALG_SID_SCHANNEL_ENC_KEY)



//#define CALG_DH_EX_EPHEM   (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH | ALG_SID_DH_EX_EPHEM)
#define CALG_DH_EL_EPHEM   (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH | ALG_SID_DH_EL_EPHEM)


///////////////////////////////////////////////////////////////////////////////////////
    

#define VPN_DEF_PROV_A  "Infotecs Cryptographic Service Provider"
#define VPN_DEF_PROV_W L"Infotecs Cryptographic Service Provider"

#define VPN_RSA_GOST_PROV_A  "Infotecs RSA/GOST Cryptographic Service Provider"
#define VPN_RSA_GOST_PROV_W  L"Infotecs RSA/GOST Cryptographic Service Provider"

#ifdef UNICODE 
#define VPN_DEF_PROV VPN_DEF_PROV_W 
#define VPN_RSA_GOST_PROV VPN_RSA_GOST_PROV_W 
#else 
#define VPN_DEF_PROV VPN_DEF_PROV_A 
#define VPN_RSA_GOST_PROV VPN_RSA_GOST_PROV_A 
#endif 

#define ITC_PROV_TYPE 80
#define VPN_PROV_TYPE 2
#define WIN_DEF_PROV_TYPE  1
#define UNKNOWN_PROVIDER_TYPE 0xffffffffL

#define CRYPT_SESSIONCONTEXT    0x00000040 //Контекст временного ( сессионного ) ключа
                                           //Действует только в совокупности с CRYPT_VERIFYCONTEXT

#define CRYPT_LONGIMITO         0x00002000 //байт имиты


// Дополнительные параметры провайдера и ключей

#define PP_HASHOID            92
#define PP_CIPHEROID          93
#define PP_SIGNATUREOID       94
#define PP_DHOID              95
#define PP_DEFENCE_KEY        99
#define PP_CHANGE_DEFENCE_KEY 100
#define PP_CERTIFICATE        101 //Получение, сохранение сертификата для текущего ключа в провайдере
#define PP_RND_PARAM          103 //Параметры используемые в ДСЧ

#define PP_VERIFYPASS_FLAG  0x00000001//Проверить пароль при установке, флаг для PP_SIGNATURE_PIN
#define PP_SAVEPASS_FLAG    0x00000002//Сохранить пароль если верен, работает только в комбинации с PP_VERIFYPASS_FLAG
#define PP_DONTSHOWDLG_FLAG 0x00000004

#define KP_MIXMODE 101
#define KP_OID 102
#define KP_HASHOID 103
#define KP_CIPHEROID 104
#define KP_SIGNATUREOID 105
#define KP_DHOID 106
#define KP_CONTAINER 107
#define KP_EXPORTID  108

//Ветка идентификации "КриптоПРО"
#define szOID_CPCSP_ALGORITHMS     "1.2.643.2.2"

//Ветка идентификации "Инфотекс"
#define szOID_VIPNET_ALGORITHMS    "1.3.6.1.4.1.10812.2.1"
#define szOID_DOMEN_ENCRYPT_ALG     szOID_VIPNET_ALGORITHMS".3.2"

#define szOID_DEFS_ENCRYPT_PARAMS     szOID_VIPNET_ALGORITHMS".3.2.1"
#define szOID_DSRF_ENCRYPT_PARAMS     szOID_VIPNET_ALGORITHMS".3.2.6"


//Алгоритмы подписи
#define szOID_DOMEN_ELIP_SIGN_ALG  szOID_CPCSP_ALGORITHMS".19"
#define szOID_CPCSP_SIGN_ALG       szOID_CPCSP_ALGORITHMS".20"

// Алгоритм шифрования
#define szOID_CPCSP_ENCRYPT_ALG     szOID_CPCSP_ALGORITHMS".21"
//Имитозащита
#define szOID_CPCSP_IMITO_ALG       szOID_CPCSP_ALGORITHMS".22"
//Выработка псевдослучайной последовательности
#define szOID_CPCSP_PRF_ALG         szOID_CPCSP_ALGORITHMS".23"

//Хеширования
#define szOID_CPCSP_HASH_ALG       szOID_CPCSP_ALGORITHMS".9"

//Хеширования + подпись
#define szOID_CPCSP_HASH_SIGN_ALG     szOID_CPCSP_ALGORITHMS".4"
#define szOID_CPCSP_HASH_SIGN_EL_ALG  szOID_CPCSP_ALGORITHMS".3"



//Ключи DH
#define szOID_DH_EL_KEY_ALG        szOID_CPCSP_ALGORITHMS".98"
#define szOID_DH_CPCSP_KEY_ALG     szOID_CPCSP_ALGORITHMS".99"


//Параметры алгоритмов
#define szOID_CPCSP_HASH_DEF_PARAM szOID_CPCSP_ALGORITHMS".30.1" //Верба-О Хеш
#define szOID_CPCSP_HASH_TEST_PARAM szOID_CPCSP_ALGORITHMS".30.0" //Тест Хеш

#define szOID_CPCSP_ENCR_DEF_PARAM szOID_CPCSP_ALGORITHMS".31.1" //Верба-О Шифрование
#define szOID_CPCSP_ENCR_B_PARAM   szOID_CPCSP_ALGORITHMS".31.2" //B
#define szOID_CPCSP_ENCR_C_PARAM   szOID_CPCSP_ALGORITHMS".31.3" //C
#define szOID_CPCSP_ENCR_D_PARAM   szOID_CPCSP_ALGORITHMS".31.4" //D
#define szOID_CPCSP_ENCR_TEST_PARAM   szOID_CPCSP_ALGORITHMS".31.0" //Test

#define szOID_DSRF_ENCR_D_PARAM   szOID_CPCSP_ALGORITHMS".31.4" //D



#define szOID_CPCSP_SIGN_DEF_PARAM szOID_CPCSP_ALGORITHMS".32.2" //Верба - 0 подпись
#define szOID_CPCSP_SIGN_1_PARAM szOID_CPCSP_ALGORITHMS".32.3" // 1
#define szOID_CPCSP_SIGN_2_PARAM szOID_CPCSP_ALGORITHMS".32.4" // 2
#define szOID_CPCSP_SIGN_3_PARAM szOID_CPCSP_ALGORITHMS".32.5" // 3

#define szOID_CPCSP_EL_SIGN_TEST_PARAM szOID_CPCSP_ALGORITHMS".35.0" //Test
#define szOID_CPCSP_EL_SIGN_DEF_PARAM szOID_CPCSP_ALGORITHMS".35.1" //Default
#define szOID_CPCSP_EL_SIGN_1_PARAM szOID_CPCSP_ALGORITHMS".35.2" // B Оскар - 2х
#define szOID_CPCSP_EL_SIGN_2_PARAM szOID_CPCSP_ALGORITHMS".35.3" // C

#define szOID_CPCSP_DH_1_PARAM szOID_CPCSP_ALGORITHMS".33.1" // 1 
#define szOID_CPCSP_DH_2_PARAM szOID_CPCSP_ALGORITHMS".33.2" // 2
#define szOID_CPCSP_DH_3_PARAM szOID_CPCSP_ALGORITHMS".33.3" // 3

#define szOID_CPCSP_EL_DH_DEF_PARAM  szOID_CPCSP_ALGORITHMS".36.0" //Default
#define szOID_CPCSP_EL_DH_1_PARAM    szOID_CPCSP_ALGORITHMS".36.1" // 1

// Масленников 16.09.2009
#define szOID_CPCSP_ENCR_KEY_MESHING_DEF  szOID_CPCSP_ALGORITHMS".14.1" //Default, ключ меняется через 1 Kb
#define szOID_CPCSP_ENCR_KEY_MESHING_ALT  szOID_CPCSP_ALGORITHMS".14.0" //альтернативное значение, ключ не меняется
// End Масленников

//Для совместимости с КриптоПРО
//Определение специфических назначений сертификатов
#define szOID_CPCSP_TLS_PROXY           szOID_CPCSP_ALGORITHMS".34.1"
#define szOID_CPCSP_RA_CLIENT_AUTH      szOID_CPCSP_ALGORITHMS".34.2"
#define szOID_CPCSP_WEB_CONTENT_SIGNING szOID_CPCSP_ALGORITHMS".34.3"
#define szOID_CPCSP_RA_ADMINISTRATOR    szOID_CPCSP_ALGORITHMS".34.4"
#define szOID_CPCSP_RA_OPERATOR         szOID_CPCSP_ALGORITHMS".34.5"

#ifdef __unix__
typedef int (__stdcall *FARPROC)();
typedef unsigned int ALG_ID;


typedef struct _PUBKEY {
        DWORD   magic;
        DWORD   bitlen;                 // # of bits in modulus
} DHPUBKEY, DSSPUBKEY, KEAPUBKEY, TEKPUBKEY;

typedef struct _PUBLICKEYSTRUC {
    BYTE   bType;
    BYTE   bVersion;
    WORD   reserved;
    ALG_ID aiKeyAlg;
} BLOBHEADER, PUBLICKEYSTRUC;

#endif

#if !defined( __KERNEL__ )

     typedef struct _VTableProvStruc {
         DWORD   Version;
         FARPROC FuncVerifyImage;
         FARPROC FuncReturnhWnd;
          DWORD   dwProvType;
          BYTE *pbContextInfo;
          DWORD     cbContextInfo;
          LPSTR pszProvName;
     } VTableProvStruc, *PVTableProvStruc;

     typedef BOOL ( WINAPI * PFNReturnhWnd  )( DWORD * phWnd );
     typedef BOOL ( WINAPI * PFNVerifyImage )( LPCSTR lpszImage, BYTE *pSigData );


#define ITCS_MAGIC_STR  "ITCS"
#define CPCSP_MAGIC_STR "MAG1"
#define GR3410_1_MAGIC  0x3147414D //"MAG1"
#define G28147_MAGIC    0x374a51fd
#define G3410_MAGIC     0x53435449
#define ITCS_MAGIC      G3410_MAGIC   
//Структуры для экспорта/импорта и хранения ключей

typedef _PUBKEY CRYPT_PUBKEYPARAM;

struct CRYPT_PUBKEY_INFO_HEADER {
   BLOBHEADER BlobHeader;
   CRYPT_PUBKEYPARAM KeyParam;
};

struct ITCS_PUBKEY_STRUCT
{
     CRYPT_PUBKEY_INFO_HEADER m_Header;
     LPBYTE m_pbAddInfo;//ASN блоб с доп. информацией об алгоритме
     LPBYTE m_pbPublicKey;//Собственно ключ размера m_Header.KeyParam.bitlen/8
};



struct CRYPT_SIMPLEBLOB_HEADER {
   BLOBHEADER m_BlobHeader;
   DWORD  m_Magic;
   ALG_ID m_EncryptKeyAlgId; //На чем зашифрован ключ
};


#define ITCS_BLOB_VER         1
#define ITCS_ASN_ENCODED_VER  0x10
#define CSP_EXPORT_PRO_VER    0x20 //Алгоритм PRO экспорта КриптоПРО
#define CSP_EXPORT_SIMPLE_VER 0x10 //Экспорт по простому алгоритму КриптоПРО


struct ITCS_SIMPLEBLOB {
   CRYPT_SIMPLEBLOB_HEADER  m_SimpleBlobHeader;
   BYTE                     m_Synchr [ 8 ];
   BYTE                     m_EncryptedKey [ 32 ];
   BYTE                     m_Imito [ 4 ];
};

#endif

//////////////////////////////////////////////////////////////////////////////

#define VPN_CNG_PROVIDER_NAME              L"Infotecs Primitive Provider"

#define CPCSP_HASH_ALG_CANONICAL_NAME_A    "GOST R 34.11-94"
#define CPCSP_HASH_ALG_CANONICAL_NAME_W    L"GOST R 34.11-94"
#define CPCSP_HASH_CNG_ALGID               CPCSP_HASH_ALG_CANONICAL_NAME_W
#define CPCSP_ENCRYPT_ALG_CANONICAL_NAME_A "GOST 28147-89"
#define CPCSP_ENCRYPT_ALG_CANONICAL_NAME_W L"GOST 28147-89"
#define CPCSP_ENCRYPT_CNG_ALGID            CPCSP_ENCRYPT_ALG_CANONICAL_NAME_W

#ifdef _UNICODE
#define CPCSP_HASH_ALG_CANONICAL_NAME CPCSP_HASH_ALG_CANONICAL_NAME_W
#define CPCSP_ENCRYPT_ALG_CANONICAL_NAME CPCSP_ENCRYPT_ALG_CANONICAL_NAME_W
#else // !_UNICODE
#define CPCSP_HASH_ALG_CANONICAL_NAME CPCSP_HASH_ALG_CANONICAL_NAME_A
#define CPCSP_ENCRYPT_ALG_CANONICAL_NAME CPCSP_ENCRYPT_ALG_CANONICAL_NAME_A
#endif // !_UNICODE

//////////////////////////////////////////////////////////////////////////////

#endif
