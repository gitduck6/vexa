#pragma once
#include "types.hpp"

#define NAMESPACE_BEGIN(_name) namespace _name {
#define NAMESPACE_END(_name) }
#define TODO(_msg) auto _monako_todo = _msg
#define IF_THEN(_cond, _stmt) if((_cond)) {DEFINE_STMT(_stmt)}


#define DEBUG_LN() (void)(monako::log::debug("{}:{} -> {}()", __FILE__, __LINE__, __func__), "")
#define DEBUG_FUNC_MODE __func__
#define DEBUG_FUNC_TEMPLATE(_mode) DEFINE_STMT(monako::log::debug("{}()", _mode);)
#define DEBUG_FUNC() DEBUG_FUNC_TEMPLATE(DEBUG_FUNC_MODE)


#define DO_PRAGMA(_x) _Pragma(#_x)
#define DEFINE_STMT(_stmt) do {_stmt} while(false);
#define DIAGNOSTIC_IGNORE_BEGIN(_diag) \
    DO_PRAGMA(GCC diagnostic push) \
    DO_PRAGMA(GCC diagnostic ignored _diag)
#define DIAGNOSTIC_IGNORE_END() \
    DO_PRAGMA(GCC diagnostic pop)
