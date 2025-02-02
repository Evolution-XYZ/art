/*
 * Copyright (C) 2023 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "NativeBridge7CriticalNative_lib.h"
#include "NativeBridgeTest.h"

namespace android {

TEST_F(NativeBridgeTest, V7_CriticalNative) {
  // Init
  ASSERT_TRUE(LoadNativeBridge(kNativeBridgeLibrary7, nullptr));
  ASSERT_TRUE(NativeBridgeAvailable());
  ASSERT_TRUE(PreInitializeNativeBridge(AppDataDir(), "isa"));
  ASSERT_TRUE(NativeBridgeAvailable());
  ASSERT_TRUE(InitializeNativeBridge(nullptr, nullptr));
  ASSERT_TRUE(NativeBridgeAvailable());

  ASSERT_EQ(NativeBridgeGetVersion(), 7U);

  ASSERT_FALSE(IsGetTrampoline2Called());
  ASSERT_FALSE(IsLegacyGetTrampolineCalled());

  EXPECT_EQ(NativeBridgeGetTrampoline(nullptr, "symbol", "shorty", 6), nullptr);
  ASSERT_FALSE(IsLegacyGetTrampolineCalled());
  ASSERT_TRUE(IsGetTrampoline2Called());
  EXPECT_EQ(GetTrampoline2JNICallType(), kJNICallTypeRegular);

  ResetTrampolineCalledState();

  ASSERT_FALSE(IsGetTrampoline2Called());
  ASSERT_FALSE(IsLegacyGetTrampolineCalled());

  EXPECT_EQ(NativeBridgeGetTrampoline2(nullptr, "symbol", "shorty", 6, kJNICallTypeCriticalNative),
            nullptr);
  ASSERT_FALSE(IsLegacyGetTrampolineCalled());
  ASSERT_TRUE(IsGetTrampoline2Called());
  EXPECT_EQ(GetTrampoline2JNICallType(), kJNICallTypeCriticalNative);

  ASSERT_FALSE(IsGetTrampolineFnPtrCalled());

  EXPECT_EQ(
      NativeBridgeGetTrampolineForFunctionPointer(nullptr, "shorty", 6, kJNICallTypeCriticalNative),
      nullptr);
  ASSERT_FALSE(IsLegacyGetTrampolineCalled());
  ASSERT_TRUE(IsGetTrampolineFnPtrCalled());
  EXPECT_EQ(GetTrampolineFnPtrJNICallType(), kJNICallTypeCriticalNative);
}

}  // namespace android
