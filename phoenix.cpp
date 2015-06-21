#include <iostream>

template <class T>
class Phoenix 
{
   public:
      static T* instance() 
      {
         if (!myInstance) 
         {
            if (destroyed) 
            {
               OnDeadReference();
            }
            else 
            {
               Create();
            } 
         }
         return myInstance;
      }
      
   private:
      static void Create() 
      {
         static T newInstance;
         myInstance = &newInstance;
      }
      virtual ~Phoenix() 
      {
         myInstance = 0;
         destroyed = true;
      }
      static void OnDeadReference() 
      {
         Create();
         new(myInstance) T;
         atexit(KillPhoenixSingleton);
         destroyed=false;
      }
      
      static void KillPhoenixSingleton() 
      {
         myInstance->~T();
      }
      
   private:
      static T* myInstance;
      static bool destroyed;
};

template <class T>
T* Phoenix<T>::myInstance = 0;
template <class T>
bool Phoenix<T>::destroyed = false;

typedef Phoenix<int> IntPhoenix;

template <class T>
class Tester
{
   public:
      ~Tester()
      {
         T* pObj = Phoenix<T>::instance();
         if (!pObj)
            std::cout << "Указатель не действительный";
      }
};

int main()
{
   static Tester<int> test;
   int* pObj = IntPhoenix::instance();
   if (!pObj)
      std::cout << "Указатель не действительный";
   return 0;
}