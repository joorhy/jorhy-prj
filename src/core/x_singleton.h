#ifndef __SINGLETON_H_
#define __SINGLETON_H_

template <typename CBase>
class SingletonTmpl
{
private:
	struct object_creator  
	{  
		object_creator()   
		{  
			SingletonTmpl<CBase>::Instance();   
		}  
		inline void do_nothing() const {}  
	};  
	//利用类的静态对象object_creator的构造初始化,在进入main之前已经调用了instance  
	//从而避免了多次初始化的问题  
	static object_creator create_object_;
public:
	static CBase *Instance()
	{
		static CBase obj;  
		//do_nothing 是必要的，do_nothing的作用有点意思，  
		//如果不加create_object_.do_nothing();这句话，在main函数前面  
		//create_object_的构造函数都不会被调用，instance当然也不会被调用，  
		//我的估计是模版的延迟实现的特效导致，如果没有这句话，编译器也不会实现  
		// SingletonTmpl<CBase>::object_creator,所以就会导致这个问题  
		create_object_.do_nothing();  
		return &obj; 
	}
};

template <typename CBase>
typename SingletonTmpl<CBase>::object_creator SingletonTmpl<CBase>::create_object_;

#endif //~__SINGLETON_H_
