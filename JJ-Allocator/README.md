#部分源码
```C++
namespace JJ
{
	template <class T>
	inline T* _allocate(ptrdiff_t size, T*) 
	{
		std::set_new_handler(0);
		T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
		if (tmp == 0)
		{
			std::cerr << "out of memory" << std::endl;
			exit(1);
		}
		return tmp;
	}
	template<class T>
	inline void _deallocate(T* buffer)
	{
		::operator delete(buffer);
	}
	template<class T1,class T2>
	inline void _construct(T1* p, const T2& value)
	{
		new(p) T1(value);  
	}
	template <class T>
	inline void _destroy(T* ptr)
	{
		ptr->~T(); 
	}
```
`set_new_handler(0)` 处理函数重置为默认值（即内存分配失败抛出bad_alloc异常）
* set_new_handler 定义:
```
  typedef void(*new_handler) ();
  new_handler set_new_handler(new_handler new_p) noexcept;
```
* 参数：new_p表示空参数且返回值为void类型函数的指针，new_p指向new或new[]分配内存失败时调用的函数
* 返回值：返回先前被设置的处理函数指针；如果尚未被设置或已被重置则返回空指针
* new_p为空指针时，表示处理函数重置为默认值（即内存分配失败抛出bad_alloc异常）

  

