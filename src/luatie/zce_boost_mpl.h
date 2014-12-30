#ifndef ZCE_LIB_BOOST_MPL_H_
#define ZCE_LIB_BOOST_MPL_H_

//���쿴��һ�Σ��׷���ǧ�ɣ�����д���У���֪������δ���������

namespace ZCE_LIB
{

//==================================================================

//�����������boost ��
//JiangweiSun  �������blog �� http://www.suninf.net/SFINAE-and-enable_if/ �ܺõ�����
template<typename T>
struct helper
{
    typedef void type;
};


// �������T�Ƿ�����ڲ�����Ϊtype��typedef

// ��Ĭ��ģ�����ָʾĬ�����
template<typename T, typename U = void>
struct has_def_type_impl
{
    static const bool value = false;
};

//ƫ�ػ�������ȥ�����T��ȡ���ͣ� T�����õ�typeʱѡ��
template<typename T>
struct has_def_type_impl < T, typename helper<typename T::type>::type >
{
    static const bool value = true;
};

// �������T�Ƿ�����ڲ�����Ϊtype��typedef
template<typename T>
struct has_def_type : has_def_type_impl < T >
{
};


//==================================================================
//��ͼ��ȡ�����ĵ���������
template <class container_type>
struct container_traits
{
    typedef typename container_type::iterator   iterator;
    typedef typename container_type::value_type   value_type;
};

//���������������ػ�
template <typename T>
struct container_traits< T *>
{
    typedef typename T  *iterator;
    typedef typename T   value_type;
};

//==================================================================

// type trait
template<bool bool_vale, typename type_a, typename type_b>
struct if_
{
};
template<typename type_a, typename type_b>
struct if_ < true, type_a, type_b >
{
    typedef type_a type;
};
template<typename type_a, typename type_b>
struct if_ < false, type_a, type_b >
{
    typedef type_b type;
};

//==================================================================


template<typename input_iter>
struct is_random_access_iterator
{
    static const bool value = typeid(std::iterator_traits<input_iter>::iterator_category) == typeid(std::random_access_iterator_tag);
};


};

//==================================================================



#endif //ZCE_LIB_BOOST_MPL_H_
