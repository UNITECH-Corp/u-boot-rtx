/*
 * Copyright (c) 2016, NVIDIA CORPORATION.
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <common.h>
#include <dm.h>
#include <dm/test.h>
#include <asm/reset.h>
#include <test/ut.h>

/* This must match the specifier for mbox-names="test" in the DT node */
#define TEST_RESET_ID 2

static int dm_test_reset(struct unit_test_state *uts)
{
	struct udevice *dev_reset;
	struct udevice *dev_test;

	ut_assertok(uclass_get_device_by_name(UCLASS_RESET, "reset-ctl",
					      &dev_reset));
	ut_asserteq(0, sandbox_reset_query(dev_reset, TEST_RESET_ID));

	ut_assertok(uclass_get_device_by_name(UCLASS_MISC, "reset-ctl-test",
					      &dev_test));
	ut_assertok(sandbox_reset_test_get(dev_test));

	ut_assertok(sandbox_reset_test_assert(dev_test));
	ut_asserteq(1, sandbox_reset_query(dev_reset, TEST_RESET_ID));

	ut_assertok(sandbox_reset_test_deassert(dev_test));
	ut_asserteq(0, sandbox_reset_query(dev_reset, TEST_RESET_ID));

	ut_assertok(sandbox_reset_test_free(dev_test));

	return 0;
}
DM_TEST(dm_test_reset, DM_TESTF_SCAN_FDT);
