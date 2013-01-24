#include <Elementary.h>
#include <boost/bind.hpp>

#include <vector>

#include "window.h"
#include "elmtestharness.h"

using std::vector;

class WindowResizeTest : public ElmTestHarness
{
public:

	WindowResizeTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowResizeTest", "Window Resize Test")
	{
		return;
	}

	void setup()
	{
		window_.show();

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::setSize, boost::ref(window_), 400, 200),
				boost::bind(&Window::checkSize, boost::ref(window_), 400, 200)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::setSize, boost::ref(window_), 100, 120),
				boost::bind(&Window::checkSize, boost::ref(window_), 100, 120)
			)
		);
	}

private:
	Window		window_;
};

class WindowMoveTest : public ElmTestHarness
{
public:
	WindowMoveTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowMoveTest", "Window Move Test")
	{
		return;
	}

	void setup()
	{
		window_.show();

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::setPosition, boost::ref(window_), 10, 20),
				boost::bind(&Window::checkPosition, boost::ref(window_), 10, 20)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::setPosition, boost::ref(window_), 15, 25),
				boost::bind(&Window::checkPosition, boost::ref(window_), 15, 25)
			)
		);
	}

private:
	Window		window_;
};

class WindowIconifyTest : public ElmTestHarness
{
public:
	WindowIconifyTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowIconifyTest", "Window Iconify/Minimize Test")
	{
		return;
	}

	void setup()
	{
		window_.show();

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::iconify, boost::ref(window_), EINA_TRUE),
				boost::bind(&Window::checkIconified, boost::ref(window_), EINA_TRUE)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::iconify, boost::ref(window_), EINA_FALSE),
				boost::bind(&Window::checkIconified, boost::ref(window_), EINA_FALSE)
			)
		);
	}

private:
	Window		window_;
};

class WindowMaximizeTest : public ElmTestHarness
{
public:
	WindowMaximizeTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowMaximizeTest", "Window Maximize Test")
	{
		return;
	}

	void setup()
	{
		window_.show();

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::maximize, boost::ref(window_), EINA_TRUE),
				boost::bind(&Window::checkMaximized, boost::ref(window_), EINA_TRUE)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::maximize, boost::ref(window_), EINA_FALSE),
				boost::bind(&Window::checkMaximized, boost::ref(window_), EINA_FALSE)
			)
		);
	}

private:
	Window		window_;
};

class WindowFullscreenTest : public ElmTestHarness
{
public:
	WindowFullscreenTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowFullscreenTest", "Window Fullscreen Test")
	{
		return;
	}

	void setup()
	{
		window_.show();

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::fullscreen, boost::ref(window_), EINA_TRUE),
				boost::bind(&Window::checkFullscreen, boost::ref(window_), EINA_TRUE)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::fullscreen, boost::ref(window_), EINA_FALSE),
				boost::bind(&Window::checkFullscreen, boost::ref(window_), EINA_FALSE)
			)
		);
	}

private:
	Window		window_;
};

class WindowStickyTest : public ElmTestHarness
{
public:
	WindowStickyTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowStickyTest", "Window Sticky Test")
	{
		return;
	}

	void setup()
	{
		window_.show();

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::sticky, boost::ref(window_), EINA_TRUE),
				boost::bind(&Window::checkSticky, boost::ref(window_), EINA_TRUE)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::sticky, boost::ref(window_), EINA_FALSE),
				boost::bind(&Window::checkSticky, boost::ref(window_), EINA_FALSE)
			)
		);
	}

private:
	Window		window_;
};

class WindowWithdrawnTest : public ElmTestHarness
{
public:
	WindowWithdrawnTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowWithdrawnTest", "Window Withdrawn Test")
	{
		return;
	}

	void setup()
	{
		window_.show();

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::withdrawn, boost::ref(window_), EINA_TRUE),
				boost::bind(&Window::checkWithdrawn, boost::ref(window_), EINA_TRUE)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&Window::withdrawn, boost::ref(window_), EINA_FALSE),
				boost::bind(&Window::checkWithdrawn, boost::ref(window_), EINA_FALSE)
			)
		);
	}

private:
	Window		window_;
};

class WindowRotationTest : public ElmTestHarness
{
public:
	WindowRotationTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowRotationTest", "Window Rotation Test")
	{
		degrees_.push_back(90);
		degrees_.push_back(180);
		degrees_.push_back(270);
		degrees_.push_back(360);
		degrees_.push_back(0);
		degrees_.push_back(90);
		degrees_.push_back(0);
		degrees_.push_back(180);
		degrees_.push_back(0);
		degrees_.push_back(270);
		degrees_.push_back(0);
		degrees_.push_back(360);

		return;
	}

	void setup()
	{
		window_.show();

		foreach (const int degree, degrees_)
		{
			queueCallback(
				ModifyCheckCallback(
					boost::bind(&Window::rotate, boost::ref(window_), degree),
					boost::bind(&Window::checkRotation, boost::ref(window_), degree)
				)
			);
		}
	}

private:
	Window		window_;
	vector<int>	degrees_;
};

class WindowAlphaTest : public ElmTestHarness
{
public:
	WindowAlphaTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowAlphaTest", "Window Alpha Test")
	{
		return;
	}

	void setup()
	{
		window_.show();

		queueCallback(
			ModifyCheckCallback(
				boost::bind(elm_win_alpha_set, boost::ref(window_), EINA_TRUE),
				boost::bind(&WindowAlphaTest::checkAlpha, boost::ref(*this), EINA_TRUE)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(elm_win_alpha_set, boost::ref(window_), EINA_FALSE),
				boost::bind(&WindowAlphaTest::checkAlpha, boost::ref(*this), EINA_FALSE)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(elm_win_alpha_set, boost::ref(window_), EINA_TRUE),
				boost::bind(&WindowAlphaTest::checkAlpha, boost::ref(*this), EINA_TRUE)
			)
		);

	}

	void checkAlpha(const Eina_Bool expected)
	{
		FAIL_UNLESS_EQUAL(elm_win_alpha_get(window_), expected);
	}

private:
	Window		window_;
};

class WindowIndicatorTest : public ElmTestHarness
{
public:
	WindowIndicatorTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowIndicatorTest", "Window Indicator Test")
	{
		return;
	}

	void setup()
	{
		window_.show();

		queueCallback(
			ModifyCheckCallback(
				boost::bind(elm_win_indicator_mode_set, boost::ref(window_), ELM_WIN_INDICATOR_SHOW),
				boost::bind(&WindowIndicatorTest::checkIndicator, boost::ref(*this), ELM_WIN_INDICATOR_SHOW)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(elm_win_indicator_mode_set, boost::ref(window_), ELM_WIN_INDICATOR_HIDE),
				boost::bind(&WindowIndicatorTest::checkIndicator, boost::ref(*this), ELM_WIN_INDICATOR_HIDE)
			)
		);

		queueCallback(
			ModifyCheckCallback(
				boost::bind(elm_win_indicator_mode_set, boost::ref(window_), ELM_WIN_INDICATOR_SHOW),
				boost::bind(&WindowIndicatorTest::checkIndicator, boost::ref(*this), ELM_WIN_INDICATOR_SHOW)
			)
		);
	}

	void checkIndicator(const Elm_Win_Indicator_Mode expected)
	{
		FAIL_UNLESS_EQUAL(elm_win_indicator_mode_get(window_), expected);
	}

private:
	Window		window_;
};

class WindowIndicatorOpacityTest : public ElmTestHarness
{
public:
	WindowIndicatorOpacityTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("WindowIndicatorOpacityTest", "Window Indicator Opacity Test")
	{
		modes_.push_back(ELM_WIN_INDICATOR_OPAQUE);
		modes_.push_back(ELM_WIN_INDICATOR_TRANSLUCENT);
		modes_.push_back(ELM_WIN_INDICATOR_TRANSPARENT);

		return;
	}

	void setup()
	{
		window_.show();

		vector<Elm_Win_Indicator_Opacity_Mode>::iterator it;
		for (it = modes_.begin(); it != modes_.end(); it++)
		{
			queueCallback(
				ModifyCheckCallback(
					boost::bind(elm_win_indicator_opacity_set, boost::ref(window_), *it),
					boost::bind(&WindowIndicatorOpacityTest::checkOpacity, boost::ref(*this), *it)
				)
			);

			queueCallback(
				ModifyCheckCallback(
					boost::bind(elm_win_indicator_opacity_set, boost::ref(window_), ELM_WIN_INDICATOR_OPAQUE),
					boost::bind(&WindowIndicatorOpacityTest::checkOpacity, boost::ref(*this), ELM_WIN_INDICATOR_OPAQUE)
				)
			);
		}
	}

	void checkOpacity(const Elm_Win_Indicator_Opacity_Mode expected)
	{
		FAIL_UNLESS_EQUAL(elm_win_indicator_opacity_get(window_), expected);
	}

private:
	Window					window_;
	vector<Elm_Win_Indicator_Opacity_Mode>	modes_;
};

class EcoreWlWindowTest : public ElmTestHarness
{
public:
	EcoreWlWindowTest()
		: ElmTestHarness::ElmTestHarness()
		, window_("EcoreWlWindowTest", "EcoreWlWindowTest")
	{
		return;
	}

	void setup()
	{
		window_.show();

		queueCallback(
			ModifyCheckCallback(
				boost::bind(&EcoreWlWindowTest::noop, boost::ref(*this)),
				boost::bind(&EcoreWlWindowTest::check, boost::ref(*this))
			)
		);
	}

	void check()
	{
		ASSERT(elm_win_wl_window_get(window_) != NULL);
	}

private:
	Window	window_;
};

WAYLAND_ELM_HARNESS_TEST_CASE(WindowResizeTest, "Window")
WAYLAND_ELM_HARNESS_TEST_CASE(WindowMoveTest, "Window")
WAYLAND_ELM_HARNESS_TEST_CASE(WindowIconifyTest, "Window")
WAYLAND_ELM_HARNESS_TEST_CASE(WindowMaximizeTest, "Window")
WAYLAND_ELM_HARNESS_TEST_CASE(WindowFullscreenTest, "Window")
WAYLAND_ELM_HARNESS_TEST_CASE(WindowStickyTest, "Window")
WAYLAND_ELM_HARNESS_TEST_CASE(WindowWithdrawnTest, "Window")
WAYLAND_ELM_HARNESS_TEST_CASE(WindowRotationTest, "Window")
//TODO: These three below need work still
WAYLAND_ELM_HARNESS_TEST_CASE(WindowAlphaTest, "Window")
WAYLAND_ELM_HARNESS_TEST_CASE(WindowIndicatorTest, "Window")
WAYLAND_ELM_HARNESS_TEST_CASE(WindowIndicatorOpacityTest, "Window")
WAYLAND_ELM_HARNESS_TEST_CASE(EcoreWlWindowTest, "Window")
