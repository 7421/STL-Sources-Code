#ifndef __JJALLOC__
#define __JJALLOC__

#include <new>		//for palcement new 
#include <cstdlib>  //for ptrdiff_t,size_t
#include <climits>  //for UINT_MAX
#include <iostream> //for cerr


namespace JJ
{
	//分配size个T类型大小的空间
	template <class T>
	inline T* _allocate(ptrdiff_t size, T*) // ptrdiff_t 类型变量，用来保存两个指针减法操作的结果
	{
		//set_new_handler(0) 处理函数被重置为默认值（即抛出bad_alloc异常）
		std::set_new_handler(0);
		T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
		if (tmp == 0)
		{
			//分配内存失败的情况
			std::cerr << "out of memory" << std::endl;
			exit(1);
		}
		return tmp;
	}

	//释放内存
	template<class T>
	inline void _deallocate(T* buffer)
	{
		::operator delete(buffer);
	}

	//调用构造函数
	template<class T1,class T2>
	inline void _construct(T1* p, const T2& value)
	{
		new(p) T1(value);  //palcement new 不分配内存只调用对象的构造函数
	}
	//调用析构函数
	template <class T>
	inline void _destroy(T* ptr)
	{
		ptr->~T(); 
	}

	template <class T>
	class allocator
	{
	public:
		typedef T  value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		//重新绑定类型U的分配器
		template <class U>
		struct rebind 
		{
			typedef allocator<U> other;
		};

		template<class U>
		allocator(const allocator<U>&) { }

		allocator() {};

		pointer allocate(size_type n, const void* hint = 0)
		{
			return _allocate((difference_type)n, (pointer)0);
		}

		void deallocate(pointer p, size_type n)
		{
			_deallocate(p);
		}

		void construct(pointer p, const T& value)
		{
			_construct(p, value);
		}

		void destroy(pointer p)
		{
			_destroy(p);
		}

		pointer address(reference x)
		{
			return (pointer)&x;
		}

		const_pointer const_address(const_reference x)
		{
			return (const_pointer)&x;
		}

		size_type max_size() const
		{
			return size_type(UINT_MAX / sizeof(T));
		}
	};
}



#endif 