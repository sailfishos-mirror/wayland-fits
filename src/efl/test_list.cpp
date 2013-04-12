#include <string>
#include <linux/input.h>
#include <boost/lexical_cast.hpp>
#include <boost/concept_check.hpp>

#include "window.h"
#include "elmtestharness.h"
#include "templates.h"

class List : public EvasObject
{
public:
	List(EvasObject &parent)
		: EvasObject::EvasObject(elm_list_add(parent))
	{
		return;
	}
};

//TODO: Add mouse wheel tests
class ListTestHarness : public ElmTestHarness
{
public:
	ListTestHarness()
		: ElmTestHarness::ElmTestHarness()
		, window_("UserListInteractionTest", "User List Interaction Test")
		, list_(elm_list_add(window_))
		, firstItemSelected_(false)
		, secondItemSelected_(false)
		, unselected_(false)
		, edgeTop_(false)
		, edgeBottom_(false)
		, edgeLeft_(false)
		, edgeRight_(false)
		, activated_(false)
		, doubleClicked_(false)
		, longPressed_(false)
	{
		for (unsigned i(0); i <= 13; ++i) {
			const std::string si = boost::lexical_cast<std::string>(i);
			elm_list_item_append(list_, si.c_str(), NULL, NULL, onSelected, this);
		}

		evas_object_size_hint_weight_set(list_, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_size_hint_align_set(list_, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_resize(list_, window_.getWidth(), window_.getHeight());

		evas_object_smart_callback_add(list_, "unselected", onUnselected, this);
		evas_object_smart_callback_add(list_, "edge,top", onEdgeTop, this);
		evas_object_smart_callback_add(list_, "edge,bottom", onEdgeBottom, this);
		evas_object_smart_callback_add(list_, "edge,left", onEdgeLeft, this);
		evas_object_smart_callback_add(list_, "edge,right", onEdgeRight, this);
		evas_object_smart_callback_add(list_, "clicked,double", onDoubleClick, this);
		evas_object_smart_callback_add(list_, "activated", onActivated, this);
		evas_object_smart_callback_add(list_, "longpressed", onLongpressed, this);
	}

	void setup()
	{
		list_.setPosition(0, 0);
		elm_list_go(list_);
		list_.show();
		window_.show();

		Application::yield(0.01*1e6);
		Geometry geo = getSurfaceGeometry(window_.get_wl_surface());
		Geometry geoListItem;
		Geometry geoFS = window_.getFramespaceGeometry();

		Elm_Object_Item *it = elm_list_first_item_get(list_);
		Evas_Object *eo = elm_list_item_object_get(it);
		evas_object_geometry_get(eo, &geoListItem.x, &geoListItem.y, &geoListItem.width, &geoListItem.height);

		//Place pointer at center of top item of list
		queueStep(
			boost::bind(
				&ElmTestHarness::setGlobalPointerPosition, boost::ref(*this),
				geoFS.x + geo.x + geoListItem.x + geoListItem.width / 2,
				geoFS.y + geo.y + geoListItem.y + geoListItem.height / 2
			)
		);

		queueStep(boost::bind(&ListTestHarness::runTest, boost::ref(*this)));
	}

	virtual void runTest() = 0;

	static void onSelected(void* data, Evas_Object* li, void*)
	{
		ListTestHarness *test = static_cast<ListTestHarness*>(data);
		Elm_Object_Item *lit = elm_list_selected_item_get(li);
		const std::string strItem(elm_object_item_text_get(lit));

		std::cout << "...received selected event: " << strItem << std::endl;

		if (strItem == "0") {
			test->firstItemSelected_ = true;
		} else if (strItem == "1") {
			test->secondItemSelected_ = true;
		}
	}

	static void onUnselected(void* data, Evas_Object*, void*)
	{
		ListTestHarness *test = static_cast<ListTestHarness*>(data);
		test->unselected_ = true;
		std::cout << "...received unselected event" << std::endl;
	}

	static void onEdgeTop(void* data, Evas_Object*, void*)
	{
		ListTestHarness *test = static_cast<ListTestHarness*>(data);
		test->edgeTop_ = true;
		std::cout << "...received edge,top event" << std::endl;
	}

	static void onEdgeBottom(void* data, Evas_Object*, void*)
	{
		ListTestHarness *test = static_cast<ListTestHarness*>(data);
		test->edgeBottom_ = true;
		std::cout << "...received edge,bottom event" << std::endl;
	}

	static void onEdgeLeft(void* data, Evas_Object*, void*)
	{
		ListTestHarness *test = static_cast<ListTestHarness*>(data);
		test->edgeLeft_ = true;
		std::cout << "...received edge,left event" << std::endl;
	}

	static void onEdgeRight(void* data, Evas_Object*, void*)
	{
		ListTestHarness *test = static_cast<ListTestHarness*>(data);
		test->edgeRight_ = true;
		std::cout << "...received edge,right event" << std::endl;
	}

	static void onDoubleClick(void* data, Evas_Object*, void*)
	{
		ListTestHarness *test = static_cast<ListTestHarness*>(data);
		test->doubleClicked_ = true;
		std::cout << "...received clicked,double event" << std::endl;
	}

	static void onActivated(void* data, Evas_Object*, void*)
	{
		ListTestHarness *test = static_cast<ListTestHarness*>(data);
		test->activated_ = true;
		std::cout << "...received activated event" << std::endl;
	}

	static void onLongpressed(void* data, Evas_Object*, void*)
	{
		ListTestHarness *test = static_cast<ListTestHarness*>(data);
		test->longPressed_= true;
		std::cout << "...received longpressed event" << std::endl;
	}

protected:
	Window		window_;
	EvasObject	list_;

	bool		firstItemSelected_;
	bool		secondItemSelected_;
	bool		unselected_;
	bool		edgeTop_;
	bool		edgeBottom_;
	bool		edgeLeft_;
	bool		edgeRight_;
	bool		activated_;
	bool		doubleClicked_;
	bool		longPressed_;
};

class ListUserSelectTest : public ListTestHarness
{
public:
	void runTest()
	{
		ASSERT(not firstItemSelected_);
		inputKeySend(BTN_LEFT, 1);
		inputKeySend(BTN_LEFT, 0);
		std::cout << "...checking for firstSelected callback" << std::endl;
		while (not firstItemSelected_) {
			Application::yield();
		}

		std::cout << "...checking for unselected and secondSelected callback" << std::endl;
		ASSERT(not unselected_);
		ASSERT(not secondItemSelected_);
		while (not unselected_ and not secondItemSelected_) {
			inputKeySend(KEY_DOWN, 1);
			inputKeySend(KEY_DOWN, 0);
			Application::yield();
		}
	}
};

class ListUserLongpressTest : public ListTestHarness
{
public:
	void runTest()
	{
		ASSERT(longPressed_ == false);
		inputKeySend(BTN_LEFT, 1);

		std::cout << "...checking for longpressed callback" << std::endl;
		while (not longPressed_) {
			Application::yield();
		}
		inputKeySend(BTN_LEFT, 0);
	}
};

class ListUserActivatedTest : public ListTestHarness
{
public:
	void runTest()
	{
		ASSERT(not activated_);
		inputKeySend(BTN_LEFT, 1);
		inputKeySend(BTN_LEFT, 0);
		inputKeySend(KEY_ENTER, 1);
		inputKeySend(KEY_ENTER, 0);

		std::cout << "...checking for activated callback" << std::endl;
		while (not activated_) {
			Application::yield();
		}
	}
};

class ListUserDoubleClickTest : public ListTestHarness
{
public:
	void runTest()
	{
		ASSERT(not doubleClicked_);
		inputKeySend(BTN_LEFT, 1);
		inputKeySend(BTN_LEFT, 0);
		inputKeySend(BTN_LEFT, 1);
		inputKeySend(BTN_LEFT, 0);

		std::cout << "...checking for clicked,double callback" << std::endl;
		while (not doubleClicked_) {
			Application::yield();
		}
	}
};

class ListUserKeyScrollTest : public ListTestHarness
{
public:
	void runTest()
	{
		/*
		 * FIXME: On some systems, it doesn't appear that the scroller
		 * bounce animation works.  This test is strictly dependent on
		 * that feature and thus should be refactored so it's not
		 * dependent on it.
		 */
		inputKeySend(BTN_LEFT, 1);
		inputKeySend(BTN_LEFT, 0);

		std::cout << "...checking for edge,top callback" << std::endl;
		ASSERT(not edgeTop_);
		while (not edgeTop_) {
			inputKeySend(KEY_UP, 1);
			inputKeySend(KEY_UP, 0);
			Application::yield();
		}

		std::cout << "...checking for edge,bottom callback" << std::endl;
		ASSERT(not edgeBottom_);
		while (not edgeBottom_) {
			inputKeySend(KEY_DOWN, 1);
			inputKeySend(KEY_DOWN, 0);
			Application::yield();
		}

		elm_list_horizontal_set(list_, EINA_TRUE);

		std::cout << "...checking for edge,left callback" << std::endl;
		ASSERT(not edgeLeft_);
		while (not edgeLeft_) {
			inputKeySend(KEY_LEFT, 1);
			inputKeySend(KEY_LEFT, 0);
			Application::yield();
		}

		std::cout << "...checking for edge,right callback" << std::endl;
		ASSERT(not edgeRight_);
		while (not edgeRight_) {
			inputKeySend(KEY_RIGHT, 1);
			inputKeySend(KEY_RIGHT, 0);
			Application::yield();
		}

		elm_list_horizontal_set(list_, EINA_FALSE);
	}
};

class ListUserMouseScrollTest : public ListTestHarness
{
public:
	void runTest()
	{
		/*
		 * FIXME: On some systems, it doesn't appear that you can
		 * scroll the list with a mouse left-button down and move
		 * action.  Investigate why to determine if it's an actual
		 * system-related thing or some toolkit config is missing.
		 * If it's system-dependent, then we don't want this test.
		 * Also, appears to depend on the bounce animation which
		 * may not be available on some setups.
		 */
		int delta(40);

		Position center;
		Geometry geo = getSurfaceGeometry(window_.get_wl_surface());
		center.x = geo.x + window_.getWidth() / 2;
		center.y = geo.y + window_.getHeight() / 2;

		std::cout << "...checking for edge,top callback" << std::endl;
		setGlobalPointerPosition(center);
		ASSERT(not edgeTop_);
		while (not edgeTop_) {
			inputKeySend(BTN_LEFT, 1);
			setGlobalPointerPosition(center.x, center.y + delta);
			inputKeySend(BTN_LEFT, 0);
			setGlobalPointerPosition(center);
			Application::yield(500000); //animation has to be displayed before callback is made :-/
		}

		std::cout << "...checking for edge,bottom callback" << std::endl;
		ASSERT(not edgeBottom_);
		while (not edgeBottom_) {
			inputKeySend(BTN_LEFT, 1);
			setGlobalPointerPosition(center.x, center.y - delta);
			inputKeySend(BTN_LEFT, 0);
			setGlobalPointerPosition(center);
			Application::yield(500000);
		}

		elm_list_horizontal_set(list_, EINA_TRUE);

		std::cout << "...checking for edge,left callback" << std::endl;
		ASSERT(not edgeLeft_);
		while (not edgeLeft_) {
			inputKeySend(BTN_LEFT, 1);
			setGlobalPointerPosition(center.x + delta, center.y);
			inputKeySend(BTN_LEFT, 0);
			setGlobalPointerPosition(center);
			Application::yield(500000);
		}

		std::cout << "...checking for edge,right callback" << std::endl;
		ASSERT(not edgeRight_);
		while (not edgeRight_) {
			inputKeySend(BTN_LEFT, 1);
			setGlobalPointerPosition(center.x - delta, center.y);
			inputKeySend(BTN_LEFT, 0);
			setGlobalPointerPosition(center);
			Application::yield(500000);
		}

		elm_list_horizontal_set(list_, EINA_FALSE);
	}
};


typedef ResizeObjectTest<List> ListResizeTest;
typedef PositionObjectTest<List> ListPositionTest;
typedef VisibleObjectTest<List> ListVisibilityTest;

WAYLAND_ELM_HARNESS_TEST_CASE(ListResizeTest, "List")
WAYLAND_ELM_HARNESS_TEST_CASE(ListPositionTest, "List")
WAYLAND_ELM_HARNESS_TEST_CASE(ListVisibilityTest, "List")

WAYLAND_ELM_HARNESS_TEST_CASE(ListUserSelectTest, "List")
WAYLAND_ELM_HARNESS_TEST_CASE(ListUserLongpressTest, "List")
WAYLAND_ELM_HARNESS_TEST_CASE(ListUserActivatedTest, "List")
WAYLAND_ELM_HARNESS_TEST_CASE(ListUserDoubleClickTest, "List")
WAYLAND_ELM_HARNESS_TEST_CASE(ListUserKeyScrollTest, "List")
WAYLAND_ELM_HARNESS_TEST_CASE(ListUserMouseScrollTest, "List")
