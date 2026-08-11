#pragma once
#include <concepts>
#include <print>
#include "alt/ini_list.hpp"
#include "defs.hpp"
// modules
#include "core/math.hpp"
#include "core/colors.hpp"
#include "core/shapes.hpp"
#include "core/vec.hpp"
#include "core/log.hpp"
#include "core/Flags.hpp"
NAMESPACE_BEGIN(monako)


inline consteval usize cstr_len(const char* cstr) {
    usize n = 0;
    while (*cstr++ != '\0') ++n;
    return n;
}

// a value with default value storage
template<typename T>
class ConfigValue {
    T m_default;
public:
    T value;

    constexpr ConfigValue (T default_and_initial_value)
        : m_default(default_and_initial_value), value(m_default)
    {}

    constexpr bool operator=(const T& new_value) {
        value = new_value;
        return *this;
    }

    constexpr operator T() const { return value; }
    constexpr T& operator-> () const { return value; }
    const T& defaultVal() const { return m_default; }
};



template<class T>
class OwnPtr {
    T* m_ptr;
public:
    OwnPtr(T* ptr): m_ptr(ptr) {}
    ~OwnPtr() {}

    // delete copy ctor/operator
    explicit OwnPtr(const T& copy_ctor) = delete;
    OwnPtr& operator= (const T& copy_operator) = delete;

    // define move ctor/operator
    explicit OwnPtr(T&& other) {
        m_ptr = other.mptr;
    }
    OwnPtr& operator= (T&& other) {
        m_ptr = other.m_ptr;
        return *this;
    }

    T* get() { return m_ptr; }

    static T* Alloc() {
        return OwnPtr<T>(new T{});
    }
};



template<class T>
struct Ref {
private:
    const T* const m_data = nullptr;
public:
    Ref (const T& object): m_data(object) {}

    const T& get() const {
        return m_data;
    }
};



template <class T>
struct RefMut {
private:
    T* const m_data = nullptr;
public:
    RefMut (const T& object): m_data(&object) {}

    const T& get() const {
        return *m_data;
    }
};


NAMESPACE_END(monako)
