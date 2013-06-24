/// @file
/// @brief Файл содержит определения интерфейса и класса отображение прогресса.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef PROGRESS_H__
#define PROGRESS_H__

/*
Прогресс для тестов. Когда строил IProgress пронализировал CProgressCtrl и JProgressBar.
Для дальнейшего развития. Пока нигде не применяется.
*/

class IProgress
{
public:
     virtual ~IProgress(){}
     virtual void setRange( int _min, int _max ) = 0;
     virtual void getRange( int& _min, int& _max ) const = 0;
     virtual void setProgress( int _val ) = 0;
     virtual int getProgress() const = 0;
};


class ConsoleProgress: public IProgress
{
public:
     ConsoleProgress( std::ostream& _outStream );
     virtual void setRange( int _min, int _max );
     virtual void getRange( int& _min, int& _max ) const;
     virtual void setProgress( int _val );
     virtual int getProgress() const;

     static bool test(){
          ConsoleProgress prog( std::cout );
          
          const int lowBound = 0, hiBound = 1000;
          prog.setRange( lowBound, hiBound );

          int low = 0, hi = 0;
          prog.getRange( low, hi );
          if( low != lowBound || hi != hiBound )
               return false;

          for( int i = lowBound; i < hiBound; ++i )
          {
               prog.setProgress( i );
               if( prog.getProgress() != i )
                    return false;
          }
          return true;
     }

private:
     static const int PROGRESS_STEPS_NUM;
     static const char PROGRESS_CHAR;
     std::ostream& outStream_;
     int min_;
     int max_;
     int current_;
};


#endif // PROGRESS_H__
