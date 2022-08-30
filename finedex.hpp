#pragma once

#include "include/function.h"

#include "include/aidel.h"
#include "include/aidel_impl.h"

namespace finedex {
template <class key_t, class val_t>
using FINEdex = aidel::AIDEL<key_t, val_t>;
}