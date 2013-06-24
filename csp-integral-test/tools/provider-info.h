/// @file
/// @brief Файл содержит определение класса, содержащего информации, необходимую для работы с криптопровайдером.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef provider_info_h__
#define provider_info_h__



class ProviderInfo
{
public:
     LPCTSTR Name() const { return name_.c_str(); }
     void Name( LPCTSTR _val) { name_ = _val; }

     DWORD Type() const { return type_; }
     void Type( DWORD _val) { type_ = _val; }

     ALG_ID SessionKeyAlgId() const { return sessionKeyAlgId_; }
     void SessionKeyAlgId( ALG_ID _val) { sessionKeyAlgId_ = _val; }

private:
     tstring name_;
     DWORD type_;
     ALG_ID sessionKeyAlgId_;
};


#endif // provider_info_h__
