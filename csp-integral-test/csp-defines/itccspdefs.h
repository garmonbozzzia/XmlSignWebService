/// @file
/// @brief Файл содержит определения идентификаторов алгоритмов, необходимых для работы с криптопровайдером.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef _ITC_ITCCSPDEFS_H_
#define _ITC_ITCCSPDEFS_H_

#include "importitccsp.h"
//Коды алгоритмов
#define ALG_SID_HASH_VPN2     40
#define ALG_SID_HASH_DOMAIN   41
#define ALG_SID_MAC_VPN2      42
#define ALG_SID_MAC_DOMAIN    43
#define ALG_SID_MASTER_DOMAIN 44
#define ALG_SID_ENCRYPT_VPN2  45
#define ALG_SID_ENCRYPT_DOMAIN  46
#define ALG_SID_DH_DOMAIN          47

#define ALG_SID_VPN_DES           49
#define ALG_SID_VPN_3DES          50
#define ALG_SID_VPN_RC6           51
#define ALG_SID_VPN_AES           52



#define UNKNOWN_ALG_ID   0xFFFF
#define ALG_SID_SHB      0x01FF
#define DOMAIN_SIGN_ID   (ALG_CLASS_SIGNATURE | ALG_TYPE_GR3410 | ALG_SID_HASH_DOMAIN)

#define VPN2_HASH_ID     (ALG_CLASS_HASH | ALG_SID_HASH_VPN2)
#define DOMAIN_HASH_ID   (ALG_CLASS_HASH | ALG_SID_HASH_DOMAIN)

#define DOMAIN_MAC_ID    (ALG_CLASS_HASH | ALG_SID_MAC_DOMAIN)
#define VPN2_MAC_ID      (ALG_CLASS_HASH | ALG_SID_MAC_VPN2)

#define VPN_ENCRYPT_ID     (ALG_CLASS_DATA_ENCRYPT | ALG_SID_ENCRYPT_VPN2)
#define DOMAIN_ENCRYPT_ID  (ALG_CLASS_DATA_ENCRYPT | ALG_SID_ENCRYPT_DOMAIN)
#define DOMAIN_MASTER_ID  (ALG_CLASS_DATA_ENCRYPT | ALG_SID_MASTER_DOMAIN)

#define VPN_DES_ENCRYPT_ID  ( ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_VPN_DES )
#define VPN_3DES_ENCRYPT_ID ( ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_VPN_3DES )
#define VPN_RC6_ENCRYPT_ID  ( ALG_CLASS_DATA_ENCRYPT | ALG_SID_VPN_RC6 ) // Алгоритм с ошибкой зацепления при контекстном шифровании
#define VPN_AES_ENCRYPT_ID  ( ALG_CLASS_DATA_ENCRYPT | ALG_SID_VPN_AES ) // Алгоритм с ошибкой зацепления при контекстном шифровании
#define DOMAIN_RC6_ENCRYPT_ID  ( ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_VPN_RC6 )
#define DOMAIN_AES_ENCRYPT_ID  ( ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK | ALG_SID_VPN_AES )

///////////////////////////////////////////////////////////////////////////////////////
    

#define GOST_HASH_SIZE             32
#define GOST_SIGNATURE_PART_LEN    32
#define GOST_SIGNATURE_FULL_LEN    32

// ------------------------------------------------------
// Определение, используемое для указания хэширования даты 
#define szOID_SIGNING_TIME         szOID_RSA_signingTime

#define CRYPT_SESSIONCONTEXT    0x00000040 //Контекст временного ( сессионного ) ключа
                                           //Действует только в совокупности с CRYPT_VERIFYCONTEXT

//Дополнительные определения
#define PP_CHANGE_DEFENCE_KEY   100 //Смена ключа защиты
#define PP_CERTIFICATE          101 //Получение, сохранение сертификата для текущего ключа в провайдере
#define PP_INFO                 102 //Получение информации о дефолтном ключе контейнера
#define PP_RND_PARAM            103 //Параметры используемые в ДСЧ

#define KP_KEYUID             40 // Unique ID ключа (ключ, зашифрованный сам на себе)

#define CRYPT_INITKEYSET        0x00000100 //  Системный контейнер
#define CRYPT_ASKPATH           0x00000200 //Спец.флаг, позвол. отображать диалог ввода пароля к контейнеру
                                           //из самого провайдера, игнорируя флаги приложения DONT_WRITE_CONT_INFO_FLAG
                                           //Только для ITCSCAPI
// Определения OID алгоритмов для криптографии версий 2.7 :

// Определение всей ветки алгоритмов
#define szOID_VIPNET_ALGORITHMS    "1.3.6.1.4.1.10812.2.1"

// Алгоритм шифрования
#define szOID_VPN_ENCRYPT_ALG          szOID_VIPNET_ALGORITHMS".3.1"
#define szOID_VPN_GOST_ENCRYPT_ALG      szOID_VIPNET_ALGORITHMS".3.1.1"
#define szOID_VPN_DES_ENCRYPT_ALG      szOID_VIPNET_ALGORITHMS".3.1.2"
#define szOID_VPN_3DES_ENCRYPT_ALG      szOID_VIPNET_ALGORITHMS".3.1.3"
#define szOID_VPN_RC6_ENCRYPT_ALG      szOID_VIPNET_ALGORITHMS".3.1.4"
#define szOID_VPN_AES_ENCRYPT_ALG      szOID_VIPNET_ALGORITHMS".3.1.5"


// Алгоритм хэширования (ГОСТ Р 34.11 - 94)
#define szOID_VPN_HASH_ALG         szOID_VIPNET_ALGORITHMS".1.1"

// Алгоритм имитозащиты (ГОСТ 28147-89 Имитозащита (VPN2))
#define szOID_VPN_MAC_ALG         szOID_VIPNET_ALGORITHMS".1.3"

// Алгоритм подписи (ГОСТ Р 34.10 - 94)
#define szOID_VPN_SIGN_ALG         szOID_VIPNET_ALGORITHMS".2.1"

// Алгоритм хэширования + подписи (ГОСТ Р 34.11 - 94, Р 34.10 - 94)
#define szOID_VPN_HASH_SIGN_ALG    szOID_VIPNET_ALGORITHMS".4.1"


// Алгоритм шифрования
#define szOID_DOMEN_ENCRYPT_ALG     szOID_VIPNET_ALGORITHMS".3.2"
#define szOID_DOMEN_RC6_ENCRYPT_ALG szOID_VIPNET_ALGORITHMS".3.2.4"
#define szOID_DOMEN_AES_ENCRYPT_ALG szOID_VIPNET_ALGORITHMS".3.2.5"

// Алгоритм хэширования + подписи
#define szOID_DOMEN_HASH_SIGN_ALG   szOID_VIPNET_ALGORITHMS".4.2"    
//#define szOID_DOMEN_HASH_SIGN_ALG      szOID_CP_GOST_R3411_R3410

// Алгоритм хэширования
#define szOID_DOMEN_HASH_ALG        szOID_VIPNET_ALGORITHMS".1.2"
//#define szOID_DOMEN_HASH_ALG        szOID_CP_GOST_R3411
// Алгоритм имитозащиты (ГОСТ 28147-89 Имитозащита (VPN2))
#define szOID_DOMEN_MAC_ALG         szOID_VIPNET_ALGORITHMS".1.4"

// Алгоритм подписи
#define szOID_DOMEN_SIGN_ALG         szOID_VIPNET_ALGORITHMS".2.2"

//////////////////////////////////////////////////////////////////////////
// дерево oid-ов ОАО «ИнфоТеКС»

// корень
#define szOID_INFOTECS_ROOT			"1.2.643.2.4"
// ветка идентификаторов
#define szOID_IDENTS				szOID_INFOTECS_ROOT".1"
// ветка для идентификаторов в нотации ASN.1
#define szOID_ASN1					szOID_IDENTS".1"
// ветка типов, введенных ОАО «ИнфоТеКС»
#define szOID_TYPES					szOID_ASN1".1"
// ветка расширений сертификатов, введенных ОАО «ИнфоТеКС»
#define szOID_ITCS_CERT_EXTENSIONS	szOID_TYPES".1"
// ветка атрибутов подписи
#define szSIGN_PURPOSES			szOID_ITCS_CERT_EXTENSIONS".1"			
// подпись согласования
#define szOID_KP_AGREEMENT_SIGNING	szSIGN_PURPOSES".1"
// подпись утверждения
#define szOID_KP_VALIDATION_SIGNING szSIGN_PURPOSES".2"
// подпись визирования
#define szOID_KP_VISA_SIGNING		szSIGN_PURPOSES".3"

#define szOID_RDN_INN    "1.2.643.3.131.1.1"

//////////////////////////////////////////////////////////////////////////


#ifdef __unix__
//Add neeeded define
typedef unsigned int ALG_ID;
typedef unsigned long HCRYPTHASH;
typedef unsigned long HCRYPTPROV;
typedef unsigned long HCRYPTKEY;

#define CP_ACP      0       /* default to ANSI code page */
//#define CP_OEMCP    1       /* default to OEM  code page */

/* Algorithm IDs */
#define GET_ALG_CLASS(x)                (x & (7 << 13))
#define GET_ALG_TYPE(x)                 (x & (15 << 9))
#define GET_ALG_SID(x)                  (x & (511))

/* Algorithm Classes */
#define ALG_CLASS_ANY                        (0)
#define ALG_CLASS_SIGNATURE             (1 << 13)
#define ALG_CLASS_MSG_ENCRYPT        (2 << 13)
#define ALG_CLASS_DATA_ENCRYPT       (3 << 13)
#define ALG_CLASS_HASH                       (4 << 13)
#define ALG_CLASS_KEY_EXCHANGE      (5 << 13)

// Algorithm types
#define ALG_TYPE_ANY                    (0)
#define ALG_TYPE_DSS                    (1 << 9)
#define ALG_TYPE_RSA                    (2 << 9)
#define ALG_TYPE_BLOCK                  (3 << 9)
#define ALG_TYPE_STREAM                 (4 << 9)
#define ALG_TYPE_DH                     (5 << 9)
#define ALG_TYPE_SECURECHANNEL          (6 << 9)

// Generic sub-ids
#define ALG_SID_ANY                     (0)

// Some RSA sub-ids
#define ALG_SID_RSA_ANY                 0
#define ALG_SID_RSA_PKCS                1
#define ALG_SID_RSA_MSATWORK            2
#define ALG_SID_RSA_ENTRUST             3
#define ALG_SID_RSA_PGP                 4

// Some DSS sub-ids
//
#define ALG_SID_DSS_ANY                 0
#define ALG_SID_DSS_PKCS                1
#define ALG_SID_DSS_DMS                 2

// Block cipher sub ids
// DES sub_ids
#define ALG_SID_DES                     1
#define ALG_SID_3DES                    3

// RC2 sub-ids
#define ALG_SID_RC2                     2

// Stream cipher sub-ids
#define ALG_SID_RC4                     1
#define ALG_SID_SEAL                    2

/* Hash SIDs */
#define ALG_SID_MD2                     1
#define ALG_SID_MD4                     2
#define ALG_SID_MD5                     3
#define ALG_SID_SHA                     4
#define ALG_SID_SHA1                    4

// Diffie-Hellman sub-ids
#define ALG_SID_DH_SANDF                1
#define ALG_SID_DH_EPHEM                2
#define ALG_SID_AGREED_KEY_ANY          3
#define ALG_SID_KEA                     4

// algorithm identifier definitions
#define CALG_RSA_SIGN                   (ALG_CLASS_SIGNATURE | ALG_TYPE_RSA | ALG_SID_RSA_ANY)
#define CALG_DSS_SIGN                   (ALG_CLASS_SIGNATURE | ALG_TYPE_DSS | ALG_SID_DSS_ANY)

/* Algorithm Definitions */
#define CALG_MD2         (ALG_CLASS_HASH         | ALG_TYPE_ANY    | ALG_SID_MD2)
#define CALG_MD4         (ALG_CLASS_HASH         | ALG_TYPE_ANY    | ALG_SID_MD4)
#define CALG_MD5         (ALG_CLASS_HASH         | ALG_TYPE_ANY    | ALG_SID_MD5)
#define CALG_SHA         (ALG_CLASS_HASH         | ALG_TYPE_ANY    | ALG_SID_SHA)
#define CALG_SHA1        (ALG_CLASS_HASH         | ALG_TYPE_ANY    | ALG_SID_SHA1)

#define CALG_RSA_KEYX    (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_RSA    | ALG_SID_RSA_ANY)

#define CALG_NO_SIGN     (ALG_CLASS_SIGNATURE    | ALG_TYPE_ANY    | ALG_SID_ANY)

#define CALG_DES         (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK  | ALG_SID_DES)
#define CALG_3DES        (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK  | ALG_SID_3DES)
#define CALG_RC2         (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK  | ALG_SID_RC2)
#define CALG_RC4         (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_STREAM | ALG_SID_RC4)

#define CALG_DH_SF       (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH     | ALG_SID_DH_SANDF)
#define CALG_DH_EPHEM    (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_DH     | ALG_SID_DH_EPHEM)


#define szOID_COMMON_NAME                   "2.5.4.3"  // case-ignore string
#define szOID_SUR_NAME                      "2.5.4.4"  // case-ignore string
#define szOID_DEVICE_SERIAL_NUMBER          "2.5.4.5"  // printable string

#define szOID_COUNTRY_NAME                  "2.5.4.6"  // printable 2char string
#define szOID_LOCALITY_NAME                 "2.5.4.7"  // case-ignore string
#define szOID_STATE_OR_PROVINCE_NAME        "2.5.4.8"  // case-ignore string
#define szOID_STREET_ADDRESS                "2.5.4.9"  // case-ignore string

#define szOID_ORGANIZATION_NAME             "2.5.4.10" // case-ignore string
#define szOID_ORGANIZATIONAL_UNIT_NAME      "2.5.4.11" // case-ignore string
#define szOID_TITLE                         "2.5.4.12" // case-ignore string

// Explanatory attribute types:
#define szOID_DESCRIPTION                   "2.5.4.13" // case-ignore string

// Postal addressing attribute types:
#define szOID_POSTAL_ADDRESS                "2.5.4.16"
#define szOID_POSTAL_CODE                   "2.5.4.17" // case-ignore string
#define szOID_POST_OFFICE_BOX               "2.5.4.18" // case-ignore string

// Telecommunications addressing attribute types:
#define szOID_TELEPHONE_NUMBER              "2.5.4.20" // telephone number
#define szOID_X21_ADDRESS                   "2.5.4.24" // numeric string

#define szOID_GIVEN_NAME                    "2.5.4.42" // case-ignore string
#define szOID_INITIALS                      "2.5.4.43" // case-ignore string

// The DN Qualifier attribute type specifies disambiguating information to add
// to the relative distinguished name of an entry. It is intended to be used
// for entries held in multiple DSAs which would otherwise have the same name,
// and that its value be the same in a given DSA for all entries to which
// the information has been added.
#define szOID_DN_QUALIFIER                  "2.5.4.46"

// Pilot user attribute types:
#define szOID_DOMAIN_COMPONENT  "0.9.2342.19200300.100.1.25" // IA5, UTF8 string

#define szOID_AUTHORITY_KEY_IDENTIFIER  "2.5.29.1"
#define szOID_KEY_ATTRIBUTES            "2.5.29.2"

#define szOID_KEY_USAGE_RESTRICTION     "2.5.29.4"
#define szOID_SUBJECT_ALT_NAME          "2.5.29.7"
#define szOID_ISSUER_ALT_NAME           "2.5.29.8"
#define szOID_BASIC_CONSTRAINTS         "2.5.29.10"
#define szOID_SUBJECT_KEY_IDENTIFIER    "2.5.29.14"

#define szOID_PRIVATEKEY_USAGE_PERIOD   "2.5.29.16"

#define szOID_KEY_USAGE                 "2.5.29.15"

#define szOID_SUBJECT_ALT_NAME2         "2.5.29.17"
#define szOID_ISSUER_ALT_NAME2          "2.5.29.18"
#define szOID_BASIC_CONSTRAINTS2        "2.5.29.19"

#define szOID_CRL_REASON_CODE           "2.5.29.21"
#define szOID_CRL_DIST_POINTS           "2.5.29.31"
#define szOID_CERT_POLICIES             "2.5.29.32"
#define szOID_AUTHORITY_KEY_IDENTIFIER2 "2.5.29.35"
#define szOID_ENHANCED_KEY_USAGE        "2.5.29.37"


// Internet Public Key Infrastructure (PKIX)
#define szOID_AUTHORITY_INFO_ACCESS     "1.3.6.1.5.5.7.1.1"

// Microsoft extensions or attributes
#define szOID_CERT_EXTENSIONS           "1.3.6.1.4.1.311.2.1.14"
#define szOID_NEXT_UPDATE_LOCATION      "1.3.6.1.4.1.311.10.2"

#define szOID_YESNO_TRUST_ATTR          "1.3.6.1.4.1.311.10.4.1"

// NIST OSE Implementors' Workshop (OIW) Security SIG algorithm identifiers


#define szOID_PKIX_NO_SIGNATURE         "1.3.6.1.5.5.7.6.2"

#define szOID_OIWSEC_md4RSA      "1.3.14.3.2.2"
#define szOID_OIWSEC_md5RSA      "1.3.14.3.2.3"
#define szOID_OIWSEC_md4RSA2     "1.3.14.3.2.4"
#define szOID_OIWSEC_desCBC      "1.3.14.3.2.7"

#define szOID_OIWSEC_dsa         "1.3.14.3.2.12"
#define szOID_OIWSEC_shaDSA      "1.3.14.3.2.13"
#define szOID_OIWSEC_shaRSA      "1.3.14.3.2.15"
#define szOID_OIWSEC_sha         "1.3.14.3.2.18"
#define szOID_OIWSEC_rsaXchg     "1.3.14.3.2.22"

#define szOID_OIWSEC_sha1        "1.3.14.3.2.26"
#define szOID_OIWSEC_dsaSHA1     "1.3.14.3.2.27"

#define szOID_OIWSEC_sha1RSASign "1.3.14.3.2.29"

#define szOID_OIWDIR_md2RSA      "1.3.14.7.2.3.1"

#define szOID_ANSI_X942_DH       "1.2.840.10046.2.1"

#define szOID_X957_DSA           "1.2.840.10040.4.1"
#define szOID_X957_SHA1DSA       "1.2.840.10040.4.3"

#define szOID_RSA_RSA            "1.2.840.113549.1.1.1"
#define szOID_RSA_MD2RSA         "1.2.840.113549.1.1.2"
#define szOID_RSA_MD4RSA         "1.2.840.113549.1.1.3"
#define szOID_RSA_MD5RSA         "1.2.840.113549.1.1.4"
#define szOID_RSA_SHA1RSA        "1.2.840.113549.1.1.5"
#define szOID_RSA_DH             "1.2.840.113549.1.3.1"

#define szOID_RSA_emailAddr      "1.2.840.113549.1.9.1"
#define szOID_RSA_unstructName   "1.2.840.113549.1.9.2"
#define szOID_RSA_contentType    "1.2.840.113549.1.9.3"
#define szOID_RSA_messageDigest  "1.2.840.113549.1.9.4"
#define szOID_RSA_signingTime    "1.2.840.113549.1.9.5"
#define szOID_RSA_counterSign    "1.2.840.113549.1.9.6"
#define szOID_RSA_challengePwd   "1.2.840.113549.1.9.7"
#define szOID_RSA_unstructAddr   "1.2.840.113549.1.9.8"
#define szOID_RSA_extCertAttrs   "1.2.840.113549.1.9.9"
#define szOID_RSA_certExtensions "1.2.840.113549.1.9.14"
#define szOID_RSA_SMIMECapabilities "1.2.840.113549.1.9.15"
#define szOID_RSA_preferSignedData "1.2.840.113549.1.9.15.1"

#define szOID_RSA_SMIMEalgCMS3DESwrap   "1.2.840.113549.1.9.16.3.6"
#define szOID_RSA_SMIMEalgCMSRC2wrap    "1.2.840.113549.1.9.16.3.7"
#define szOID_RSA_SMIMEalgESDH          "1.2.840.113549.1.9.16.3.5"

#define szOID_RSA_MD2           "1.2.840.113549.2.2"
#define szOID_RSA_MD4           "1.2.840.113549.2.4"
#define szOID_RSA_MD5           "1.2.840.113549.2.5"

#define szOID_RSA_RC2CBC        "1.2.840.113549.3.2"
#define szOID_RSA_RC4           "1.2.840.113549.3.4"
#define szOID_RSA_DES_EDE3_CBC  "1.2.840.113549.3.7"

#define szOID_INFOSEC_mosaicUpdatedSig      "2.16.840.1.101.2.1.1.19"
#define szOID_INFOSEC_mosaicKMandUpdSig     "2.16.840.1.101.2.1.1.20"

//+-------------------------------------------------------------------------
//  Qualifiers that may be part of the szOID_CERT_POLICIES and
//  szOID_CERT_POLICIES95 extensions
//+-------------------------------------------------------------------------
#define szOID_PKIX_POLICY_QUALIFIER_CPS               "1.3.6.1.5.5.7.2.1"
#define szOID_PKIX_POLICY_QUALIFIER_USERNOTICE        "1.3.6.1.5.5.7.2.2"

//+-------------------------------------------------------------------------
//  PKIX Access Description: Access Method Object Identifiers
//--------------------------------------------------------------------------
//#define szOID_PKIX_ACC_DESCR            "1.3.6.1.5.5.7.48"
#define szOID_PKIX_OCSP                 "1.3.6.1.5.5.7.48.1"
#define szOID_PKIX_CA_ISSUERS           "1.3.6.1.5.5.7.48.2"

// Extension contain certificate type
#define szOID_ENROLL_CERTTYPE_EXTENSION "1.3.6.1.4.1.311.20.2"
#define szOID_CERT_MANIFOLD             "1.3.6.1.4.1.311.20.3"

//+-------------------------------------------------------------------------
//  Netscape Certificate Extension Object Identifiers
//--------------------------------------------------------------------------
#define szOID_NETSCAPE                  "2.16.840.1.113730"
#define szOID_NETSCAPE_CERT_EXTENSION   "2.16.840.1.113730.1"
#define szOID_NETSCAPE_CERT_TYPE        "2.16.840.1.113730.1.1"
#define szOID_NETSCAPE_BASE_URL         "2.16.840.1.113730.1.2"
#define szOID_NETSCAPE_REVOCATION_URL   "2.16.840.1.113730.1.3"
#define szOID_NETSCAPE_CA_REVOCATION_URL "2.16.840.1.113730.1.4"
#define szOID_NETSCAPE_CERT_RENEWAL_URL "2.16.840.1.113730.1.7"
#define szOID_NETSCAPE_CA_POLICY_URL    "2.16.840.1.113730.1.8"
#define szOID_NETSCAPE_SSL_SERVER_NAME  "2.16.840.1.113730.1.12"
#define szOID_NETSCAPE_COMMENT          "2.16.840.1.113730.1.13"

//+-------------------------------------------------------------------------
//  Object Identifiers for use with the MS Certificate Server
//--------------------------------------------------------------------------
#ifndef szOID_CERTSRV_CA_VERSION
#define szOID_CERTSRV_CA_VERSION        "1.3.6.1.4.1.311.21.1"
#endif

// serialized serial numbers for PRS
#ifndef szOID_SERIALIZED
#define szOID_SERIALIZED                "1.3.6.1.4.1.311.10.3.3.1"
#endif

// UPN principal name in SubjectAltName
#ifndef szOID_NT_PRINCIPAL_NAME
#define szOID_NT_PRINCIPAL_NAME         "1.3.6.1.4.1.311.20.2.3"
#endif

// Windows product update unauthenticated attribute
#ifndef szOID_PRODUCT_UPDATE
#define szOID_PRODUCT_UPDATE            "1.3.6.1.4.1.311.31.1"
#endif

// CryptUI
#define szOID_ANY_APPLICATION_POLICY    "1.3.6.1.4.1.311.10.12.1"

// szOID_CRL_NUMBER -- Base CRLs only.  Monotonically increasing sequence
// number for each CRL issued by a CA.
#define szOID_CRL_NUMBER                "2.5.29.20"
// szOID_DELTA_CRL_INDICATOR -- Delta CRLs only.  Marked critical.
// Contains the minimum base CRL Number that can be used with a delta CRL.
#define szOID_DELTA_CRL_INDICATOR       "2.5.29.27"
#define szOID_ISSUING_DIST_POINT        "2.5.29.28"

// szOID_FRESHEST_CRL -- Base CRLs only.  Formatted identically to a CDP
// extension that holds URLs to fetch the delta CRL.
#define szOID_FRESHEST_CRL              "2.5.29.46"
#define szOID_NAME_CONSTRAINTS          "2.5.29.30"

// Note on 1/1/2000 szOID_POLICY_MAPPINGS was changed from "2.5.29.5"
#define szOID_POLICY_MAPPINGS           "2.5.29.33"
#define szOID_LEGACY_POLICY_MAPPINGS    "2.5.29.5"
#define szOID_POLICY_CONSTRAINTS        "2.5.29.36"

#define szOID_ANY_CERT_POLICY           "2.5.29.32.0"

// Microsoft PKCS10 Attributes
#define szOID_RENEWAL_CERTIFICATE           "1.3.6.1.4.1.311.13.1"
#define szOID_ENROLLMENT_NAME_VALUE_PAIR    "1.3.6.1.4.1.311.13.2.1"
#define szOID_ENROLLMENT_CSP_PROVIDER       "1.3.6.1.4.1.311.13.2.2"
#define szOID_OS_VERSION                    "1.3.6.1.4.1.311.13.2.3"

// Microsoft extensions or attributes
#define szOID_CERT_EXTENSIONS           "1.3.6.1.4.1.311.2.1.14"
#define szOID_NEXT_UPDATE_LOCATION      "1.3.6.1.4.1.311.10.2"
#define szOID_REMOVE_CERTIFICATE            "1.3.6.1.4.1.311.10.8.1"
#define szOID_CROSS_CERT_DIST_POINTS    "1.3.6.1.4.1.311.10.9.1"

// Application Policies extension -- same encoding as szOID_CERT_POLICIES
#define szOID_APPLICATION_CERT_POLICIES     "1.3.6.1.4.1.311.21.10"
// Application Policy Mappings -- same encoding as szOID_POLICY_MAPPINGS
#define szOID_APPLICATION_POLICY_MAPPINGS   "1.3.6.1.4.1.311.21.11"
// Application Policy Constraints -- same encoding as szOID_POLICY_CONSTRAINTS
#define szOID_APPLICATION_POLICY_CONSTRAINTS    "1.3.6.1.4.1.311.21.12"

// szOID_CERTSRV_PREVIOUS_CERT_HASH -- Contains the sha1 hash of the previous
// version of the CA certificate.
#define szOID_CERTSRV_PREVIOUS_CERT_HASH    "1.3.6.1.4.1.311.21.2"
// szOID_CRL_VIRTUAL_BASE -- Delta CRLs only.  Contains the base CRL Number
// of the corresponding base CRL.
#define szOID_CRL_VIRTUAL_BASE          "1.3.6.1.4.1.311.21.3"
// szOID_CRL_NEXT_PUBLISH -- Contains the time when the next CRL is expected
// to be published.  This may be sooner than the CRL's NextUpdate field.
#define szOID_CRL_NEXT_PUBLISH          "1.3.6.1.4.1.311.21.4"
// Enhanced Key Usage for CA encryption certificate
#define szOID_KP_CA_EXCHANGE            "1.3.6.1.4.1.311.21.5"
// Enhanced Key Usage for key recovery agent certificate
#define szOID_KP_KEY_RECOVERY_AGENT     "1.3.6.1.4.1.311.21.6"
// Certificate template extension (v2)
#define szOID_CERTIFICATE_TEMPLATE      "1.3.6.1.4.1.311.21.7"
// The root oid for all enterprise specific oids
#define szOID_ENTERPRISE_OID_ROOT       "1.3.6.1.4.1.311.21.8"
// Dummy signing Subject RDN
#define szOID_RDN_DUMMY_SIGNER          "1.3.6.1.4.1.311.21.9"

#define szOID_ARCHIVED_KEY_ATTR                "1.3.6.1.4.1.311.21.13"
#define szOID_CRL_SELF_CDP                     "1.3.6.1.4.1.311.21.14"

// Requires all certificates below the root to have a non-empty intersecting
// issuance certificate policy usage.
#define szOID_REQUIRE_CERT_CHAIN_POLICY        "1.3.6.1.4.1.311.21.15"
//#define szOID_ARCHIVED_KEY_CERT_HASH           "1.3.6.1.4.1.311.21.16"
//#define szOID_ISSUED_CERT_HASH                 "1.3.6.1.4.1.311.21.17"

// Consistent key usage bits: DIGITAL_SIGNATURE, KEY_ENCIPHERMENT
// or KEY_AGREEMENT
#define szOID_PKIX_KP_SERVER_AUTH       "1.3.6.1.5.5.7.3.1"
// Consistent key usage bits: DIGITAL_SIGNATURE
#define szOID_PKIX_KP_CLIENT_AUTH       "1.3.6.1.5.5.7.3.2"
// Consistent key usage bits: DIGITAL_SIGNATURE
#define szOID_PKIX_KP_CODE_SIGNING      "1.3.6.1.5.5.7.3.3"
// Consistent key usage bits: DIGITAL_SIGNATURE, NON_REPUDIATION and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)
#define szOID_PKIX_KP_EMAIL_PROTECTION  "1.3.6.1.5.5.7.3.4"
// Consistent key usage bits: DIGITAL_SIGNATURE and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)
#define szOID_PKIX_KP_IPSEC_END_SYSTEM  "1.3.6.1.5.5.7.3.5"
// Consistent key usage bits: DIGITAL_SIGNATURE and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)
#define szOID_PKIX_KP_IPSEC_TUNNEL      "1.3.6.1.5.5.7.3.6"
// Consistent key usage bits: DIGITAL_SIGNATURE and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)
#define szOID_PKIX_KP_IPSEC_USER        "1.3.6.1.5.5.7.3.7"
// Consistent key usage bits: DIGITAL_SIGNATURE or NON_REPUDIATION
#define szOID_PKIX_KP_TIMESTAMP_SIGNING "1.3.6.1.5.5.7.3.8"

//  Signer of CTLs
#define szOID_KP_CTL_USAGE_SIGNING      "1.3.6.1.4.1.311.10.3.1"
//  Signer of TimeStamps
#define szOID_KP_TIME_STAMP_SIGNING     "1.3.6.1.4.1.311.10.3.2"

#define szOID_KP_EFS                    "1.3.6.1.4.1.311.10.3.4"
#define szOID_EFS_RECOVERY              "1.3.6.1.4.1.311.10.3.4.1"

// Can use Windows Hardware Compatible (WHQL)
#define szOID_WHQL_CRYPTO               "1.3.6.1.4.1.311.10.3.5"
// Signed by the NT5 build lab
#define szOID_NT5_CRYPTO                "1.3.6.1.4.1.311.10.3.6"
// Signed by and OEM of WHQL
#define szOID_OEM_WHQL_CRYPTO           "1.3.6.1.4.1.311.10.3.7"
// Signed by the Embedded NT
#define szOID_EMBEDDED_NT_CRYPTO        "1.3.6.1.4.1.311.10.3.8"
// Signer of a CTL containing trusted roots
#define szOID_ROOT_LIST_SIGNER      "1.3.6.1.4.1.311.10.3.9"
// Can sign cross-cert and subordinate CA requests with qualified
// subordination (name constraints, policy mapping, etc.)
#define szOID_KP_QUALIFIED_SUBORDINATION    "1.3.6.1.4.1.311.10.3.10"
// Can be used to encrypt/recover escrowed keys
#define szOID_KP_KEY_RECOVERY               "1.3.6.1.4.1.311.10.3.11"
// Signer of documents
#define szOID_KP_DOCUMENT_SIGNING           "1.3.6.1.4.1.311.10.3.12"
// IKE (Internet Key Exchange) Intermediate KP for an IPsec end entity.
// Defined in draft-ietf-ipsec-pki-req-04.txt, December 14, 1999.
#define szOID_IPSEC_KP_IKE_INTERMEDIATE "1.3.6.1.5.5.8.2.2"

// Enhanced key usage for DS email replication
#define szOID_DS_EMAIL_REPLICATION             "1.3.6.1.4.1.311.21.19"
//
// Extension contain certificate type
#define szOID_ENROLLMENT_AGENT              "1.3.6.1.4.1.311.20.2.1"
// The default WinVerifyTrust Authenticode policy is to treat all time stamped
// signatures as being valid forever. This OID limits the valid lifetime of the
// signature to the lifetime of the certificate. This allows timestamped
// signatures to expire. Normally this OID will be used in conjunction with
// szOID_PKIX_KP_CODE_SIGNING to indicate new time stamp semantics should be
// used. Support for this OID was added in WXP.
#define szOID_KP_LIFETIME_SIGNING           "1.3.6.1.4.1.311.10.3.13"

#ifndef szOID_DRM
#define szOID_DRM                       "1.3.6.1.4.1.311.10.5.1"
#endif

#ifndef szOID_LICENSES
#define szOID_LICENSES                  "1.3.6.1.4.1.311.10.6.1"
#endif

#ifndef szOID_LICENSE_SERVER
#define szOID_LICENSE_SERVER            "1.3.6.1.4.1.311.10.6.2"
#endif

#ifndef szOID_KP_SMARTCARD_LOGON
#define szOID_KP_SMARTCARD_LOGON        "1.3.6.1.4.1.311.20.2.2"
#endif


// Content Type (request)
#define szOID_CT_PKI_DATA               "1.3.6.1.5.5.7.12.2"
// Content Type (response)
#define szOID_CT_PKI_RESPONSE           "1.3.6.1.5.5.7.12.3"

#define szOID_CMC                       "1.3.6.1.5.5.7.7"
#define szOID_CMC_STATUS_INFO           "1.3.6.1.5.5.7.7.1"
#define szOID_CMC_IDENTIFICATION        "1.3.6.1.5.5.7.7.2"
#define szOID_CMC_IDENTITY_PROOF        "1.3.6.1.5.5.7.7.3"
#define szOID_CMC_DATA_RETURN           "1.3.6.1.5.5.7.7.4"
#define szOID_CMC_ADD_EXTENSIONS        "1.3.6.1.5.5.7.7.8"
#define szOID_CMC_ADD_ATTRIBUTES        "1.3.6.1.4.1.311.10.10.1"

#define szOID_PKCS_7_DATA               "1.2.840.113549.1.7.1"
#define szOID_PKCS_7_SIGNED             "1.2.840.113549.1.7.2"
#define szOID_PKCS_7_ENVELOPED          "1.2.840.113549.1.7.3"
#define szOID_PKCS_7_SIGNEDANDENVELOPED "1.2.840.113549.1.7.4"
#define szOID_PKCS_7_DIGESTED           "1.2.840.113549.1.7.5"
#define szOID_PKCS_7_ENCRYPTED          "1.2.840.113549.1.7.6"

#define SPC_SP_AGENCY_INFO_OBJID            "1.3.6.1.4.1.311.2.1.10"
#define SPC_MINIMAL_CRITERIA_OBJID          "1.3.6.1.4.1.311.2.1.26"
#define SPC_FINANCIAL_CRITERIA_OBJID        "1.3.6.1.4.1.311.2.1.27"

//+-------------------------------------------------------------------------
//  CERT_RDN Attribute Value Types
//
//  For RDN_ENCODED_BLOB, the Value's CERT_RDN_VALUE_BLOB is in its encoded
//  representation. Otherwise, its an array of bytes.
//
//  For all CERT_RDN types, Value.cbData is always the number of bytes, not
//  necessarily the number of elements in the string. For instance,
//  RDN_UNIVERSAL_STRING is an array of ints (cbData == intCnt * 4) and
//  RDN_BMP_STRING is an array of unsigned shorts (cbData == ushortCnt * 2).
//
//  For CertDecodeName, two 0 bytes are always appended to the end of the
//  string (ensures a CHAR or WCHAR string is null terminated).
//  These added 0 bytes are't included in the BLOB.cbData.
//--------------------------------------------------------------------------
#define CERT_RDN_ANY_TYPE                0
#define CERT_RDN_NUMERIC_STRING          3
#define CERT_RDN_PRINTABLE_STRING        4
#define CERT_RDN_IA5_STRING              7
#define CERT_RDN_UNICODE_STRING          12
#define CERT_RDN_UTF8_STRING             13

// exported key blob definitions
#define SIMPLEBLOB              0x1
#define PUBLICKEYBLOB           0x6
#define PRIVATEKEYBLOB          0x7
#define PLAINTEXTKEYBLOB        0x8

/* Key Specs*/
#define AT_KEYEXCHANGE          1
#define AT_SIGNATURE            2

#define CRYPT_USERDATA          1

// dwFlags definitions for CryptAcquireContext
#define CRYPT_VERIFYCONTEXT     0xF0000000 // Временный контйнер
#define CRYPT_NEWKEYSET         0x00000008 // Создать контейнер
#define CRYPT_MACHINE_KEYSET    0x00000020
#define CRYPT_DELETEKEYSET      0x00000010 // Удалить контейнер
#define CRYPT_SILENT            0x00000040 // Silent режим

#define CRYPT_FIRST             1
#define CRYPT_NEXT              2

// dwFlag definitions for CryptGenKey
#define CRYPT_EXPORTABLE        0x00000001
#define CRYPT_USER_PROTECTED    0x00000002
#define CRYPT_CREATE_SALT       0x00000004
#define CRYPT_UPDATE_KEY        0x00000008
#define CRYPT_NO_SALT           0x00000010
#define CRYPT_PREGEN            0x00000040
#define CRYPT_RECIPIENT         0x00000010
#define CRYPT_INITIATOR         0x00000040
#define CRYPT_ONLINE            0x00000080
#define CRYPT_SF                0x00000100
#define CRYPT_CREATE_IV         0x00000200
#define CRYPT_KEK               0x00000400
#define CRYPT_DATA_KEY          0x00000800


// dwParam
#define KP_IV                   1       // Initialization vector
#define KP_SALT                 2       // Salt value
#define KP_PADDING              3       // Padding values
#define KP_MODE                 4       // Mode of the cipher
#define KP_MODE_BITS            5       // Number of bits to feedback
#define KP_PERMISSIONS          6       // Key permissions DWORD
#define KP_ALGID                7       // Key algorithm
#define KP_BLOCKLEN             8       // Block size of the cipher
#define KP_KEYLEN               9       // Length of key in bits
#define KP_SALT_EX              10      // Length of salt in bytes
#define KP_P                    11      // DSS/Diffie-Hellman P value
#define KP_G                    12      // DSS/Diffie-Hellman G value
#define KP_Q                    13      // DSS Q value
#define KP_X                    14      // Diffie-Hellman X value
#define KP_Y                    15      // Y value
#define KP_RA                   16      // Fortezza RA value
#define KP_RB                   17      // Fortezza RB value
#define KP_INFO                 18      // for putting information into an RSA envelope
#define KP_EFFECTIVE_KEYLEN     19      // setting and getting RC2 effective key length
#define KP_SCHANNEL_ALG	        20      // for setting the Secure Channel algorithms
#define KP_CLIENT_RANDOM		21      // for setting the Secure Channel client random data
#define KP_SERVER_RANDOM		22      // for setting the Secure Channel server random data
#define	KP_RP					23
#define	KP_PRECOMP_MD5			24
#define	KP_PRECOMP_SHA			25
#define KP_CERTIFICATE          26      // for setting Secure Channel certificate data (PCT1)
#define KP_CLEAR_KEY            27      // for setting Secure Channel clear key data (PCT1)
#define KP_PUB_EX_LEN           28
#define KP_PUB_EX_VAL           29

// KP_PERMISSIONS
#define CRYPT_ENCRYPT           0x0001  // Allow encryption
#define CRYPT_DECRYPT           0x0002  // Allow decryption
#define CRYPT_EXPORT            0x0004  // Allow key to be exported
#define CRYPT_READ              0x0008  // Allow parameters to be read
#define CRYPT_WRITE             0x0010  // Allow parameters to be set
#define CRYPT_MAC               0x0020  // Allow MACs to be used with key
#define CRYPT_EXPORT_KEY        0x0040  // Allow key to be used for exporting keys
#define CRYPT_IMPORT_KEY        0x0080  // Allow key to be used for importing keys
#define CRYPT_ARCHIVE           0x0100  // Allow key to be exported at creation only



#define HP_ALGID                0x0001  // Hash algorithm
#define HP_HASHVAL              0x0002  // Hash value
#define HP_HASHSIZE             0x0004  // Hash value size
#define HP_HMAC_INFO            0x0005  // information for creating an HMAC
#define HP_TLS1PRF_LABEL        0x0006  // label for TLS1 PRF
#define HP_TLS1PRF_SEED         0x0007  // seed for TLS1 PRF

// CryptGetProvParam
//
#define PP_CLIENT_HWND          1
#define PP_ENUMALGS             1
#define PP_ENUMCONTAINERS       2
#define PP_NAME                 4
#define PP_VERSION              5
#define PP_CONTAINER            6
#define PP_CHANGE_PASSWORD      7


#define PP_PROVTYPE             16
#define PP_KEYSTORAGE           17

#define PP_ENUMALGS_EX          22

#define PP_KEYEXCHANGE_PIN      32
#define PP_SIGNATURE_PIN        33
#define PP_UNIQUE_CONTAINER     36
#define PP_USE_HARDWARE_RNG     38

typedef int (__stdcall *FARPROC)();

#ifndef __KERNEL__

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

//+-------------------------------------------------------------------------
//  Type used for any algorithm
//
//  Where the Parameters CRYPT_OBJID_BLOB is in its encoded representation. For most
//  algorithm types, the Parameters CRYPT_OBJID_BLOB is NULL (Parameters.cbData = 0).
//--------------------------------------------------------------------------
typedef struct _CRYPT_ALGORITHM_IDENTIFIER {
    LPSTR               pszObjId;
    CRYPT_OBJID_BLOB    Parameters;
} CRYPT_ALGORITHM_IDENTIFIER, *PCRYPT_ALGORITHM_IDENTIFIER;


//+-------------------------------------------------------------------------
//  Public Key Info
//
//  The PublicKey is the encoded representation of the information as it is
//  stored in the bit string
//--------------------------------------------------------------------------
typedef struct _CERT_PUBLIC_KEY_INFO {
    CRYPT_ALGORITHM_IDENTIFIER    Algorithm;
    CRYPT_BIT_BLOB                PublicKey;
} CERT_PUBLIC_KEY_INFO, *PCERT_PUBLIC_KEY_INFO;


//+-------------------------------------------------------------------------
//  OID Information
//--------------------------------------------------------------------------
typedef struct _CRYPT_OID_INFO {
    DWORD               cbSize;
    LPCSTR              pszOID;
    LPCWSTR             pwszName;
    DWORD               dwGroupId;
    union {
        DWORD               dwValue;
        ALG_ID              Algid;
        DWORD               dwLength;
    };
    CRYPT_DATA_BLOB     ExtraInfo;
} CRYPT_OID_INFO, *PCRYPT_OID_INFO;

typedef const CRYPT_OID_INFO CCRYPT_OID_INFO, *PCCRYPT_OID_INFO;

/* CSP Structs */

typedef struct _PROV_ENUMALGS {
  ALG_ID aiAlgid;
  DWORD  dwBitLen;
  DWORD  dwNameLen;
  CHAR   szName[20];
} PROV_ENUMALGS;

typedef struct _PROV_ENUMALGS_EX {
    ALG_ID    aiAlgid;
    DWORD     dwDefaultLen;
    DWORD     dwMinLen;
    DWORD     dwMaxLen;
    DWORD     dwProtocols;
    DWORD     dwNameLen;
    CHAR      szName[20];
    DWORD     dwLongNameLen;
    CHAR      szLongName[40];
} PROV_ENUMALGS_EX;


//+-------------------------------------------------------------------------
//  CryptMsg OID installable functions
//--------------------------------------------------------------------------

typedef void * (WINAPI *PFN_CMSG_ALLOC) (
  IN size_t cb
  );

typedef void (WINAPI *PFN_CMSG_FREE)(
  IN void *pv
  );

//+-------------------------------------------------------------------------
//  Certificate Issuer and SerialNumber
//--------------------------------------------------------------------------
typedef struct _CERT_ISSUER_SERIAL_NUMBER {
  CERT_NAME_BLOB      Issuer;
  CRYPT_INTEGER_BLOB  SerialNumber;
} CERT_ISSUER_SERIAL_NUMBER, *PCERT_ISSUER_SERIAL_NUMBER;

//+-------------------------------------------------------------------------
//  Certificate Identifier
//--------------------------------------------------------------------------
typedef struct _CERT_ID {
  DWORD   dwIdChoice;
  union {
    // CERT_ID_ISSUER_SERIAL_NUMBER
    CERT_ISSUER_SERIAL_NUMBER   IssuerSerialNumber;
    // CERT_ID_KEY_IDENTIFIER
    CRYPT_HASH_BLOB             KeyId;
    // CERT_ID_SHA1_HASH
    CRYPT_HASH_BLOB             HashId;
  };
} CERT_ID, *PCERT_ID;

#define CERT_ID_ISSUER_SERIAL_NUMBER    1
#define CERT_ID_KEY_IDENTIFIER          2
#define CERT_ID_SHA1_HASH               3


//+-------------------------------------------------------------------------
//  CMSG_CMS_RECIPIENT_INFO_PARAM
//
//  To get all the CMS recipients, repetitively call CryptMsgGetParam, with
//  dwIndex set to 0 .. CmsRecipientCount - 1.
//
//  pvData points to a CMSG_CMS_RECIPIENT_INFO struct.
//--------------------------------------------------------------------------

typedef struct _CMSG_KEY_TRANS_RECIPIENT_INFO {
  DWORD                       dwVersion;
  
  // Currently, only ISSUER_SERIAL_NUMBER or KEYID choices
  CERT_ID                     RecipientId;
  
  CRYPT_ALGORITHM_IDENTIFIER  KeyEncryptionAlgorithm;
  CRYPT_DATA_BLOB             EncryptedKey;
} CMSG_KEY_TRANS_RECIPIENT_INFO, *PCMSG_KEY_TRANS_RECIPIENT_INFO;


//+-------------------------------------------------------------------------
//  Key Transport Recipient Encode Info
//
//  hCryptProv is used to do the recipient key encryption
//  and export. The hCryptProv's private keys aren't used.
//
//  If hCryptProv is NULL, then, the hCryptProv specified in
//  CMSG_ENVELOPED_ENCODE_INFO is used.
//
//  Note, even if CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags
//  passed to CryptMsgOpenToEncode(), this hCryptProv isn't released.
//
//  CMS supports the KEY_IDENTIFIER and ISSUER_SERIAL_NUMBER CERT_IDs. PKCS #7
//  version 1.5 only supports the ISSUER_SERIAL_NUMBER CERT_ID choice.
//--------------------------------------------------------------------------
typedef struct _CMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO {
    DWORD                       cbSize;
    CRYPT_ALGORITHM_IDENTIFIER  KeyEncryptionAlgorithm;
    void                        *pvKeyEncryptionAuxInfo;
    HCRYPTPROV                  hCryptProv;
    CRYPT_BIT_BLOB              RecipientPublicKey;
    CERT_ID                     RecipientId;
} CMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO, *PCMSG_KEY_TRANS_RECIPIENT_ENCODE_INFO;

typedef struct _CMSG_RECIPIENT_ENCODE_INFO CMSG_RECIPIENT_ENCODE_INFO,
  *PCMSG_RECIPIENT_ENCODE_INFO;

//+-------------------------------------------------------------------------
//  Key Transport Encrypt Info
//
//  The following data structure contains the information updated by the
//  ExportKeyTrans installable function.
//--------------------------------------------------------------------------
typedef struct _CMSG_KEY_TRANS_ENCRYPT_INFO {
    DWORD                       cbSize;
    DWORD                       dwRecipientIndex;
    CRYPT_ALGORITHM_IDENTIFIER  KeyEncryptionAlgorithm;
    CRYPT_DATA_BLOB             EncryptedKey;
    DWORD                       dwFlags;
} CMSG_KEY_TRANS_ENCRYPT_INFO, *PCMSG_KEY_TRANS_ENCRYPT_INFO;

//+-------------------------------------------------------------------------
//  Content Encrypt Info
//
//  The following data structure contains the information shared between
//  the GenContentEncryptKey and the ExportKeyTrans, ExportKeyAgree and
//  ExportMailList installable functions.
//--------------------------------------------------------------------------
typedef struct _CMSG_CONTENT_ENCRYPT_INFO {
    DWORD                       cbSize;
    HCRYPTPROV                  hCryptProv;
    CRYPT_ALGORITHM_IDENTIFIER  ContentEncryptionAlgorithm;
    void                        *pvEncryptionAuxInfo;
    DWORD                       cRecipients;
    PCMSG_RECIPIENT_ENCODE_INFO rgCmsRecipients;
    PFN_CMSG_ALLOC              pfnAlloc;
    PFN_CMSG_FREE               pfnFree;
    DWORD                       dwEncryptFlags;
    HCRYPTKEY                   hContentEncryptKey;
    DWORD                       dwFlags;
} CMSG_CONTENT_ENCRYPT_INFO, *PCMSG_CONTENT_ENCRYPT_INFO;

#define CMSG_CONTENT_ENCRYPT_PAD_ENCODED_LEN_FLAG   0x00000001

#define CMSG_CONTENT_ENCRYPT_FREE_PARA_FLAG         0x00000001
#define CMSG_CONTENT_ENCRYPT_RELEASE_CONTEXT_FLAG   0x00008000


//+-------------------------------------------------------------------------
//  CMSG_CTRL_KEY_TRANS_DECRYPT
//
//  Decrypt an ENVELOPED message after it has been decoded for a key
//  transport recipient.
//
//  hCryptProv and dwKeySpec specify the private key to use. For dwKeySpec ==
//  0, defaults to AT_KEYEXCHANGE.
//
//  If CMSG_CRYPT_RELEASE_CONTEXT_FLAG is set in the dwFlags passed
//  to CryptMsgControl, then, the hCryptProv is released on the final
//  CryptMsgClose. Not released if CryptMsgControl fails.
//
//  pKeyTrans points to the CMSG_KEY_TRANS_RECIPIENT_INFO obtained via
//  CryptMsgGetParam(CMSG_CMS_RECIPIENT_INFO_PARAM)
//
//  dwRecipientIndex is the index of the recipient in the message associated
//  with the hCryptProv's private key.
//
//  Note, the message can only be decrypted once.
//--------------------------------------------------------------------------
typedef struct _CMSG_CTRL_KEY_TRANS_DECRYPT_PARA {
  DWORD                           cbSize;
  HCRYPTPROV                      hCryptProv;
  DWORD                           dwKeySpec;
  PCMSG_KEY_TRANS_RECIPIENT_INFO  pKeyTrans;
  DWORD                           dwRecipientIndex;
} CMSG_CTRL_KEY_TRANS_DECRYPT_PARA, *PCMSG_CTRL_KEY_TRANS_DECRYPT_PARA;

#endif //ifndef( __KERNEL__ )

#define CRYPT_OID_INFO_OID_KEY           1
#define CRYPT_OID_INFO_NAME_KEY          2
#define CRYPT_OID_INFO_ALGID_KEY         3
#define CRYPT_OID_INFO_SIGN_KEY          4

//+-------------------------------------------------------------------------
//  OID Group IDs
//--------------------------------------------------------------------------
#define CRYPT_HASH_ALG_OID_GROUP_ID             1
#define CRYPT_ENCRYPT_ALG_OID_GROUP_ID          2
#define CRYPT_PUBKEY_ALG_OID_GROUP_ID           3
#define CRYPT_SIGN_ALG_OID_GROUP_ID             4
#define CRYPT_RDN_ATTR_OID_GROUP_ID             5
#define CRYPT_EXT_OR_ATTR_OID_GROUP_ID          6
#define CRYPT_ENHKEY_USAGE_OID_GROUP_ID         7
#define CRYPT_POLICY_OID_GROUP_ID               8
#define CRYPT_LAST_OID_GROUP_ID                 8

#define CRYPT_FIRST_ALG_OID_GROUP_ID            CRYPT_HASH_ALG_OID_GROUP_ID
#define CRYPT_LAST_ALG_OID_GROUP_ID             CRYPT_SIGN_ALG_OID_GROUP_ID

#define CRYPT_OID_INHIBIT_SIGNATURE_FORMAT_FLAG     0x1
#define CRYPT_OID_USE_PUBKEY_PARA_FOR_PKCS7_FLAG    0x2
#define CRYPT_OID_NO_NULL_ALGORITHM_PARA_FLAG       0x4

#endif //__unix__


#ifdef _WIN32
#define ITC_ROULETTE_DLL_NAME      _T("roulett2.dll")
#define ITC_ROULETTE_VPN_NAME      _T("roulett2.vpn")
#else
#define ITC_ROULETTE_DLL_NAME      _T("libroulett2.so")
#endif

#define RND_NAME_RECORD_MAX_FUNC_NAME   100
#define RND_NAME_RECORD_MAX_SHORT_NAME  20

typedef struct _rndname
{
     char szFuncName[RND_NAME_RECORD_MAX_FUNC_NAME];
     char szShortName[RND_NAME_RECORD_MAX_SHORT_NAME];
     char szGetDllFuncName[RND_NAME_RECORD_MAX_FUNC_NAME];
} RndNameRecord;

const RndNameRecord CSPRndRecords[] = { {"BioRandom", "bio", "GetBioRandomModuleNameA"}, 
                                        {"AccordRandom","accord", "GetAccordRandomModuleNameA"}, 
                                        {"SobolRandom","sobol", "GetSobolRandomModuleNameA"},
                                        {"eTokenJavaRandom", "tokenJava", "" },
                                        {"",""}};

#ifndef __KERNEL__

class ITCSSimpleBlobStruct : public ITCS_SIMPLEBLOB
{
public:
   ITCSSimpleBlobStruct()
   {
          m_SimpleBlobHeader.m_EncryptKeyAlgId = DOMAIN_ENCRYPT_ID; 
          m_SimpleBlobHeader.m_BlobHeader.bType = SIMPLEBLOB;
          m_SimpleBlobHeader.m_BlobHeader.bVersion = ITCS_BLOB_VER;
          m_SimpleBlobHeader.m_BlobHeader.aiKeyAlg = DOMAIN_ENCRYPT_ID;//Алгоритм ключа
          m_SimpleBlobHeader.m_BlobHeader.reserved = 0;
   }
};

#endif //__KERNEL__
//+-------------------------------------------------------------------------
//  Synchronization CSP defines
//--------------------------------------------------------------------------
#define ITC_CSP_INIT_SYNCHRO_NAME  _T("itcs_provider_init_synchro_name")
#define CRYPT_DIGIT_2_8    0x2A2A2A2AUL //Часть стартового вектора имитозащиты версии 2.8

#endif
