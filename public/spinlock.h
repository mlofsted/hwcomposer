/*
// Copyright (c) 2016 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#ifndef SPIN_LOCK_H_
#define SPIN_LOCK_H_

#include <atomic>

namespace hwcomposer {

class SpinLock {
 public:
  void lock() {
    while (atomic_lock_.test_and_set(std::memory_order_acquire)) {
    }
  }

  void unlock() {
    atomic_lock_.clear(std::memory_order_release);
  }

 private:
  std::atomic_flag atomic_lock_ = ATOMIC_FLAG_INIT;
};

class ScopedSpinLock {
 public:
  ScopedSpinLock(SpinLock& lock) : lock_(lock) {
    lock_.lock();
  }

  ~ScopedSpinLock() {
    lock_.unlock();
  }

 private:
  SpinLock& lock_;
};

}  // namespace hwcomposer
#endif  // SPIN_LOCK_H_
